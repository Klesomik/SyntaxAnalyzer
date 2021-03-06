#ifndef INFORMATION_HPP

#define INFORMATION_HPP

#include "SyntaxStyle.hpp"
#include "NameStyle.hpp"

class Information
{
	public:
		Information ();

		void prepare_data ();

		enum
		{
			If,
			For,
			While,
			Return
		};

		enum
		{
			Class,
			Method,
			Function,
			LocalVar,
			GlobalVar,
			Param
		};

		std::vector <SyntaxStyle> data;

		std::vector <NameStyle> result;

		std::map <int, std::string> table;
};

// TODO: delete global object
Information information;

Information::Information ():
	data   (4),
	result (6),
	table  ({ {     If,     "if" },
			  {    For,    "for" },
			  {  While,  "while" },
			  { Return, "return" } })
{
}

void Information::prepare_data ()
{
	for (auto& it : data)
    {
        it.mediana_prefix ();
        it.mediana_suffix ();
    }
}

#endif /* INFORMATION_HPP */