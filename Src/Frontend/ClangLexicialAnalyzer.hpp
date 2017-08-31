#ifndef CLANGLEXICIALANALYZER_HPP

#define CLANGLEXICIALANALYZER_HPP

#include "Clang.hpp"
#include "InformationCollector.hpp"

/*
This class makes all work with Clang API
Now we give buffer and get information about formatting
*/

#define ci information_collector.ci

class ClangLexicialAnalyzer
{
    public:
        ClangLexicialAnalyzer ();

        void compiler_instance_init ();

        void fill_raw_tokens ();
        void fill_preprocessed_tokens ();
        void fill_table ();

        bool is_token (Token &from, const std::string &to);

    //private:
};

ClangLexicialAnalyzer::ClangLexicialAnalyzer ()
{
    compiler_instance_init ();
}

void ClangLexicialAnalyzer::compiler_instance_init ()
{
    ci.createDiagnostics(); // create DiagnosticsEngine

    // create TargetOptions
    TargetOptions to;
    to.Triple = llvm::sys::getDefaultTargetTriple();
    // create TargetInfo
    std::shared_ptr<clang::TargetOptions> tmp (new clang::TargetOptions (to));
    TargetInfo *pti = TargetInfo::CreateTargetInfo (ci.getDiagnostics(), tmp);
    ci.setTarget (pti);

    ci.createFileManager   ();                     // create FileManager
    ci.createSourceManager (ci.getFileManager ()); // create SourceManager
    ci.createPreprocessor  (TU_Complete);          // create Preprocessor

    const clang::FileEntry *file = ci.getFileManager ().getFile (file_snapshot.name.c_str ());
    if (!file)
    {
        llvm::errs () << "File not found: " << file_snapshot.name << '\n';
        return;
    }

    clang::FileID mainFileID = ci.getSourceManager ().createFileID (file, clang::SourceLocation (), clang::SrcMgr::C_User);
    ci.getSourceManager ().setMainFileID (mainFileID);

    ci.getPreprocessor ().EnterMainSourceFile ();
    ci.getDiagnosticClient ().BeginSourceFile (ci.getLangOpts (), &ci.getPreprocessor ());
}

void ClangLexicialAnalyzer::fill_raw_tokens ()
{
    const llvm::MemoryBuffer *from_file = ci.getSourceManager ().getBuffer (ci.getSourceManager ().getMainFileID ());
    Lexer raw (ci.getSourceManager ().getMainFileID (), from_file, ci.getSourceManager (), ci.getPreprocessor ().getLangOpts ());
    raw.SetKeepWhitespaceMode (true);

    for (Token tok; !tok.is (clang::tok::eof);)
    {
        raw.LexFromRawLexer (tok);

        information_collector.data.push_back (tok);
    }
}

void ClangLexicialAnalyzer::fill_preprocessed_tokens ()
{
    for (Token tok; !tok.is (clang::tok::eof);)
    {
        ci.getPreprocessor ().Lex (tok);

        if (ci.getDiagnostics ().hasErrorOccurred ())
            break;

        information_collector.data.push_back (tok);
    }
}

void ClangLexicialAnalyzer::fill_table ()
{
    for (int i = 0; i < (int) information_collector.data.size (); i++) 
        information_collector.table[information_collector.data[i].getLocation ()] = i;
}

#endif /* CLANGLEXICIALANALYZER_HPP */