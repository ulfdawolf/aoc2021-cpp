#include <cstdint>

typedef struct
{
    int64_t autoCompleteScore;
    int64_t errorScore;
} ParseLineResult;

typedef struct
{
    int64_t totalErrorScore;         // Part 1 result
    int64_t middleAutoCompleteScore; // Part 2 result
} ParseResult;

class Parser
{
public:
    static ParseResult parse(const char *program);

private:
    Parser() {}
    static ParseLineResult parseLine(std::string line);
    static bool isEndSymbol(char symbol);
    static int64_t getErrorScore(char endSymbol, char startSymbol);
    static int64_t getAutoCompleteScore(const char *topOfStack, int stackLength);
};