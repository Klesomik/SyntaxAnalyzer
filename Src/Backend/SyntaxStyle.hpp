#ifndef SYNTAXSTYLE_HPP

#define SYNTAXSTYLE_HPP

/*
This class contains all information about lexemes
Now it has number of spaces before lexeme (prefix) and after lexeme (suffix)
Also you count result by some methods
*/

class SyntaxStyle
{
    public:
    	SyntaxStyle ();

        void mediana_prefix ();
        void mediana_suffix ();
        void maximum_prefix ();
        void maximum_suffix ();

        //Every std::pair <int, int> contains prefix and suffix of spaces
        std::vector <std::pair <int, int>> data;

        std::pair <int, int> result;
};

SyntaxStyle::SyntaxStyle ():
	data (),
	result ()
{
}

void SyntaxStyle::mediana_prefix ()
{
    if (data.empty ())
        return;

    int size = data[0].first;

    for (int i = 1; i < (int) data.size (); i++)
        size = std::max (size, data[i].first);

    std::vector <int> counter (size + 1);

    for (auto& it : data)
        counter[it.first]++;

    int index = 0;

    for (int i = 1; i < (int) counter.size (); i++)
        if (counter[i] > counter[index])
            index = i;

    result.first = index;
}

void SyntaxStyle::mediana_suffix ()
{
    if (data.empty ())
        return;
    
    int size = data[0].second;

    for (int i = 1; i < (int) data.size (); i++)
        size = std::max (size, data[i].second);

    std::vector <int> counter (size + 1);

    for (auto& it : data)
        counter[it.second]++;

    int index = 0;

    for (int i = 1; i < (int) counter.size (); i++)
        if (counter[i] > counter[index])
            index = i;

    result.second = index;
}

void SyntaxStyle::maximum_prefix ()
{
    result.first = data[0].first;

    for (int i = 1; i < (int) data.size (); i++)
        result.first = std::max (result.first, data[i].first);

    result.first /= data.size ();
}

void SyntaxStyle::maximum_suffix ()
{
    result.second = data[0].second;

    for (int i = 1; i < (int) data.size (); i++)
        result.second = std::max (result.second, data[i].second);

    result.second /= data.size ();
}

#endif /* SYNTAXSTYLE_HPP */
