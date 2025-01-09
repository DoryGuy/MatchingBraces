//
//  main.cpp
//  MatchingBraces
//
//  Created by Gary Powell on 6/13/19.
//  Copyright © 2019 Guest User. All rights reserved.
//


#include <format>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>

#include <boost/unordered/unordered_flat_map.hpp>

class missMatched : public std::runtime_error
{
    typedef std::runtime_error inherited;
public:
    explicit missMatched(std::string const &typeOfMissMatch, std::string const &inputString)
    : inherited(std::format( "miss matched {} for \"{}\"", typeOfMissMatch, inputString))
    {}

    virtual ~missMatched() noexcept {}

    virtual const char * what() const noexcept  {
        return inherited::what();}
};

enum RESULT_t { PASS, FAIL };
boost::unordered_flat_map<RESULT_t, const char *> enumText = {{PASS, "PASS"}, {FAIL, "FAIL"}};

constexpr std::pair<RESULT_t, std::unique_ptr<std::exception>> parse(std::string const &input)
{
    int countParens{0};
    int countSquareBrackets{0};
    int countCurlyBraces{0};
    
    for (auto c: input ){
        switch(c){
            case '(':
                ++countParens;
                break;
            case ')':
//                if (countSquareBrackets && countParens >= countSquareBrackets)
//                    return {FAIL, std::unique_ptr<missMatched>(new missMatched("SquareBrackets", input))};
//                if (countCurlyBraces && countParens >= countCurlyBraces)
//                    return {FAIL,std::unique_ptr<missMatched>(new missMatched("CurlyBraces", input))};
                --countParens;
                if (countParens < 0)
                    return {FAIL,std::unique_ptr<missMatched>(new missMatched("Parens", input))};
                break;
            case '[':
                ++countSquareBrackets;
                break;
            case ']':
//                if (countParens && countSquareBrackets >= countParens)
//                    return {FAIL,std::unique_ptr<missMatched>(new missMatched("Parens", input))};
//                if (countCurlyBraces && countSquareBrackets >= countCurlyBraces)
//                    return {FAIL, std::unique_ptr<missMatched>(new missMatched("CurlyBraces", input))};
                --countSquareBrackets;
                if (countSquareBrackets < 0)
                    return {FAIL,std::unique_ptr<missMatched>(new missMatched("SquareBrackets", input))};
                break;
            case '{':
                ++countCurlyBraces;
                break;
            case '}':
//                if (countParens && countParens <= countCurlyBraces)
//                    return {FAIL,std::unique_ptr<missMatched>(new missMatched("Parens", input))};
//                if (countSquareBrackets && countSquareBrackets <= countCurlyBraces)
//                    return {FAIL,std::unique_ptr<missMatched>(new missMatched("SquareBrackets", input))};
                --countCurlyBraces;
                if (countCurlyBraces < 0)
                    return {FAIL,std::unique_ptr<missMatched>(new missMatched("CurlyBraces", input))};
                break;
        }
    }
    if (countParens) return {FAIL,std::unique_ptr<missMatched>(new missMatched("Parans",input))};
    if (countSquareBrackets) return {FAIL,std::unique_ptr<missMatched>(new missMatched("SquareBrackets",input))};
    if (countCurlyBraces) return {FAIL,std::unique_ptr<missMatched>(new missMatched("CurlyBraces", input))};

    return {PASS, std::unique_ptr<std::exception>(new std::exception())};
}

int main() {
    // insert code here...
    using std::string;
    using std::cout;
    using std::cerr;
    using std::endl;
    using std::pair;
    using std::make_pair;
    pair<string, RESULT_t> input[] = {
                       make_pair("(abc)", PASS),
                       make_pair("((", FAIL),
                       make_pair("({[]})", PASS),
                       make_pair("([{}])", PASS),
                       make_pair("{[()]}", PASS),
                       make_pair("{([])}", PASS),
                       make_pair("[({})]", PASS),
                       make_pair("[{()}]", PASS),
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
                       make_pair("({])", FAIL),
                       make_pair("([})", FAIL),
                       make_pair("((]}", FAIL),
                       make_pair("([)]", FAIL),
                       make_pair("({)}", FAIL),
                       make_pair("[{]}", FAIL),
                       make_pair("[(])", FAIL),
                       make_pair("{(})", FAIL),
                       make_pair("{[}]", FAIL),
                       make_pair("(([))]", FAIL),
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
    for (auto i : input) {
        auto result = parse(i.first);
        if (result.first == i.second) {
            cout << "input = \"" << i.first << "\" correctly " << enumText[result.first] << "\n";
        }
        else {
            cout << "input " << enumText[result.first] <<  " \"" << i.first
                 << "\" should should have " << enumText[i.second] << ".\n";
        }
    }
    return 0;
}
