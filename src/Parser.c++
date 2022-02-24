#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Parser.h"

using namespace std;

enum CodeSymbol
{
    START_PAR = '(',
    END_PAR = ')',

    START_BRACKET = '[',
    END_BRACKET = ']',

    START_CURLY = '{',
    END_CURLY = '}',

    START_ARROW = '<',
    END_ARROW = '>'
};

#define MAX_STACK_LENGTH 1024

bool Parser::isEndSymbol(char symbol)
{
    return (symbol == END_PAR || symbol == END_BRACKET || symbol == END_CURLY || symbol == END_ARROW);
}

int64_t Parser::getErrorScore(char endSymbol, char startSymbol)
{
    switch (endSymbol)
    {
    case END_PAR:
        return startSymbol == START_PAR ? 0 : 3;

    case END_BRACKET:
        return startSymbol == START_BRACKET ? 0 : 57;

    case END_CURLY:
        return startSymbol == START_CURLY ? 0 : 1197;

    case END_ARROW:
        return startSymbol == START_ARROW ? 0 : 25137;

    default:
        cout << "Invalid end symbol in program: " << endSymbol << endl;
        exit(-1);
    }
}

int64_t Parser::getAutoCompleteScore(const char *stack, int stackIndex)
{
    int64_t result = 0;

    while (stackIndex >= 0)
    {
        result *= 5;
        char symbol = stack[stackIndex--];
        switch (symbol)
        {
        case START_PAR:
            result += 1;
            break;

        case START_BRACKET:
            result += 2;
            break;

        case START_CURLY:
            result += 3;
            break;

        case START_ARROW:
            result += 4;
            break;

        default:
            cout << "Invalid symbol in stack: " << symbol << endl;
            exit(-2);
            break;
        }
    }
    return result;
}

ParseResult Parser::parse(const char *program)
{
    ParseResult result = {0, 0};
    stringstream ss(program);
    string line;
    vector<int64_t> acs;

    if (program != NULL)
    {
        while (getline(ss, line, '\n'))
        {
            ParseLineResult lineResult = parseLine(line);
            result.totalErrorScore += lineResult.errorScore;
            if (lineResult.autoCompleteScore > 0)
            {
                acs.push_back(lineResult.autoCompleteScore);
            }
        }
    }

    sort(acs.begin(), acs.end());
    result.middleAutoCompleteScore = acs.at(acs.size() / 2);

    return result;
}

ParseLineResult Parser::parseLine(string line)
{
    ParseLineResult result = {0, 0};
    char stack[MAX_STACK_LENGTH];
    int stackIndex = 0;

    for (int i = 0; i < line.length(); i++)
    {
        char current = line.at(i);
        if (isEndSymbol(current))
        {
            if (stackIndex == 0)
            {
                cout << "Invalid starting symbol: " << current << endl;
                exit(-3);
            }
            result.errorScore += getErrorScore(current, stack[stackIndex - 1]);
            if (result.errorScore == 0)
            {
                stackIndex--;
            }
            else
            {
                i = line.length();
            }
        }
        else
        {
            stack[stackIndex++] = current;
            if (stackIndex >= MAX_STACK_LENGTH)
            {
                cout << "Out of stack memory!!" << endl;
                exit(-4);
            }
        }
    }

    if (result.errorScore == 0 && stackIndex > 0)
    {
        stack[stackIndex--] = '\0';
        result.autoCompleteScore = getAutoCompleteScore(stack, stackIndex);
    }

    return result;
}