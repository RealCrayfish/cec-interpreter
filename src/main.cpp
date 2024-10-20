#include "cec.hpp"
#include <vector>

using namespace std;

enum TokenType {
    LEFT_PAREN, RIGHT_PAREN,
    STRING,
    SAY
};

struct Token {
    TokenType type;
    string lexeme;
    int line;

    Token(TokenType type, string lexeme, int line) {
        this->type = type;
        this->lexeme = lexeme;
        this->line = line;
    }
};

class Tokeniser {
    private:

    string source;
    vector<Token> tokens;
    int start;
    int current;
    int line;

    bool isAtEnd() { return current >= (source.length()-1); }
    char advance() { return source[current++]; }
    bool match(char expected, bool incr) {
        bool success = true;
        if (isAtEnd()) return false; // If no more characters left.
        if (source[current+1] != expected) success = false; // Check next character.
        if (incr) current++; // Increment.
        return success;
    }

    public:

    Tokeniser(string source) {
        this->source = source;
        this->start = 0;
        this->current = 0;
        this->line = 1;
    }
};

static void runFile(string path) {
    try {
        string fileContents = eiririn::stringFromFile(path);

    } catch (exception& e) {
        throw runtime_error(e.what());
    }
}

int main(int argc, char *argv[]) {
    string path;
    printf("Enter the input file path (relative): ");
    getline(cin, path); // Sets the input file path.

    runFile(path);
}
