#include <iostream>
#include <fstream>
#include "FrontEnd//Viewer.hpp"
//#include "FrontEnd//CodeInformation.hpp"
#include "BackEnd//Formatter.hpp"

void FillBuffer (const std::string &name, std::string& buffer);

int main (int argc, const char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Few arguments";

		return 0;
	}

	std::string buffer;
	FillBuffer (argv[1], buffer);

	//const bool ret = clang::tooling::runToolOnCode (new MyAction, buffer.c_str ());

	Viewer viewer;
           viewer.parsing (buffer);

    Formatter formatter;

    /*CodeInformation code_information (buffer);
                    code_information.compiler_instance_init ();
                    code_information.lexer_init ();
                    code_information.fill_raw_tokens ();
                    code_information.parsing (formatter.data);*/

    formatter.parsing (buffer);

	return 0;
}

void FillBuffer (const std::string &name, std::string& buffer)
{
	std::ifstream in (name);

	std::getline (in, buffer, '\0');
}
