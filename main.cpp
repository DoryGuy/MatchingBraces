//
//  main.cpp
//  MatchingBraces
//
//  Created by Gary Powell on 6/13/19.
//  Copyright © 2019 Guest User. All rights reserved.
//


#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <utility>

class missMatched : public std::exception
{
    std::string outputMsg;
public:
    missMatched(std::string const &typeOfMissMatch, std::string const &inputString)
    {
        std::ostringstream msg;
        msg << "miss matched " << typeOfMissMatch << " for \"" << inputString << "\"";
        outputMsg.assign(msg.str());
    }
    virtual const char * what() const throw()  {
        return outputMsg.c_str();}
};

void parse(std::string const &input)
{
    int countParens = 0;
    int countSquareBrackets = 0;
    int countCurlyBraces = 0;
    
    for (auto c: input ){
        switch(c){
            case '(':
                ++countParens;
                break;
            case ')':
                if (countSquareBrackets && countParens > countSquareBrackets)
                    throw missMatched("SquareBrackets", input);
                if (countCurlyBraces && countParens > countCurlyBraces)
                    throw missMatched("CurlyBraces", input);
                --countParens;
                if (countParens < 0)
                    throw missMatched("Parens", input);
                break;
            case '[':
                ++countSquareBrackets;
                break;
            case ']':
                if (countParens && countParens <= countSquareBrackets)
                    throw missMatched("Parens", input);
                if (countCurlyBraces && countCurlyBraces <= countSquareBrackets)
                    throw missMatched("CurlyBraces", input);
                --countSquareBrackets;
                if (countSquareBrackets < 0)
                    throw missMatched("SquareBrackets", input);
                break;
            case '{':
                ++countCurlyBraces;
                break;
            case '}':
                if (countParens && countParens <= countCurlyBraces)
                    throw missMatched("Parens", input);
                if (countSquareBrackets && countSquareBrackets <= countCurlyBraces)
                    throw missMatched("SquareBrackets", input);
                --countCurlyBraces;
                if (countCurlyBraces < 0)
                    throw missMatched("CurlyBraces", input);
                break;
        }
    }
    if (countParens) throw missMatched("Parans",input);
    if (countSquareBrackets) throw missMatched("SquareBrackets",input);
    if (countCurlyBraces) throw missMatched("CurlyBraces", input);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    using std::string;
    using std::cout;
    using std::endl;
    using std::pair;
    using std::make_pair;
    enum RESULT { PASS, FAIL };
    pair<string, RESULT> input[] = {
                       make_pair("(abc)", PASS),
                       make_pair("((", FAIL),
                       make_pair("({[]})", PASS),
                       make_pair("", PASS),
                       make_pair(")", FAIL),
                       make_pair("]", FAIL),
                       make_pair("}", FAIL),
                       make_pair("({)", FAIL),
                       make_pair("(})", FAIL),
                       make_pair("([)", FAIL),
                       make_pair("(])", FAIL),
                       make_pair("({)", FAIL),
                       make_pair("[(]", FAIL),
                       make_pair("[)]", FAIL),
                       make_pair("[{]", FAIL),
                       make_pair("[{]}", FAIL),
                       make_pair("{(}", FAIL),
                       make_pair("{[}", FAIL),
                       make_pair("()(", FAIL),
                       make_pair("][", FAIL),
                       make_pair("}{", FAIL),
                       make_pair("()", PASS),
                       make_pair("[]", PASS),
                       make_pair("{}", PASS),
                       make_pair("()[]", PASS),
                       make_pair("(){}", PASS),
                       make_pair("[]{}", PASS),
                       make_pair("()[]{}", PASS)
    };
    for (auto i : input){
        try {
            parse(i.first);
            if (i.second == PASS)
                cout << "input = \"" << i.first << "\" ok\n";
            else
                cout << "input passed \"" << i.first << "\" should should have failed.\n";
        }
        catch(std::exception const &e) {
            if (i.second == FAIL)
                cout << "e.what() = " << e.what() << endl;
            else
                cout << "input passed = \"" << i.first << "\" should have failed." << endl;
        }
    }
    cout << "Hello, World!\n";
    return 0;
}
