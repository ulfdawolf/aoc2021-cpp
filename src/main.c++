#include <iostream>
#include "TestInput.h"
#include "Parser.h"
using namespace std;

int main()
{
    cout << endl
         << "Puzzle https://adventofcode.com/2021/day/10 ©ulf@famkarlsson.org" << endl
         << endl;

    // Example input
    ParseResult exampleResult = Parser::parse(exampleInput);

    cout << "Example Input Result Part1: " << exampleResult.totalErrorScore << endl;
    cout << "Example Input Result Part2: " << exampleResult.middleAutoCompleteScore << endl;

    cout << endl
         << endl;

    // Test input
    ParseResult testResult = Parser::parse(input);

    cout << "Test Input Result Part1: " << testResult.totalErrorScore << endl;
    cout << "Test Input Result Part2: " << testResult.middleAutoCompleteScore << endl;

    cout << endl
         << "End of Program 😄"
         << endl;
    return 0;
}