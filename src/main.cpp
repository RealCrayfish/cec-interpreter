#include "cec.hpp"

#include <vector>

using namespace std;

// Globals
string path;
bool cowsay;


/*
    Command Usage:
        cec <file> [-cs] [--cowsay]
*/

enum TokenType {
  // Single-character tokens.
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, F_SLASH, B_SLASH, STAR,
  LEFT_ABRACE, RIGHT_ABRACE, LEFT_SBRACE, RIGHT_SBRACE,
  RETURNS,

  // One or two character tokens.
  NOT, NOT_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  // Literals.
  INTEGER, FLOAT, CHAR, STRING,
  BOOL, ARRAY,

  // Keywords.
  DICT, STRUCT, LIST,
  IF, ELIF, ELSE, 
  TRUE, FALSE, NIL,
  LET, VAR,
  FUN, RETURNS,
  LOOP, BARK,
  AND, OR,
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
        int start = 0;
        int current = 0;
        int line = 1;

        void addToken(TokenType type) {
            tokens.push_back(Token(type, source.substr(start, current-start), line));
        }

        bool isAtEnd() { return current >= source.length(); }
        char advance() { return source[current++]; }
        bool match(char expected, bool incr) {
            if (isAtEnd()) return false;
            if (source[current] != expected) return false;
            if (incr) current++;
            return true;
        }

        void scanToken() {
            char c = advance();
            switch (c) {
                case '(': addToken(LEFT_PAREN); break; case ')': addToken(RIGHT_PAREN); break; // ()
                case '{': addToken(LEFT_BRACE); break; case '}': addToken(RIGHT_BRACE); break; // {}
                case '[': addToken(LEFT_SBRACE); break; case ']': addToken(RIGHT_SBRACE); break; // []
                case ',': addToken(COMMA); break;                               // ,
                case '.': addToken(DOT); break;                                 // .
                case '-': addToken(MINUS); break;                               // -
                case '+': addToken(PLUS); break;                                // +
                case ';': addToken(SEMICOLON); break;                           // ;
                case '*': addToken(STAR); break;                                // *
                case '/': addToken(F_SLASH); break;                             // /

                case '=':
                    if (match('>', false)) { addToken(RETURNS); current++; break; }    // =>
                    addToken(match('=', true) ? EQUAL_EQUAL : EQUAL);           // ==
                    break;
                case '!':
                    if (match('=', true)) { addToken(NOT_EQUAL); break; }       // !=
                    cout << "Error: Unexpected character.\n"; break;
                case '<':
                    addToken(match('=', true) ? LESS_EQUAL : LESS);             // <=
                    break;
                case '>':
                    addToken(match('=', true) ? GREATER_EQUAL : GREATER);       // >=
                    break;

                case ' ':                                                       // Whitespace
                case '\r':                                                      //
                case '\t':                                                      //
                    // Ignore whitespace.                                       //
                    break;                                                      //

                case '\n':                                                      // \n
                    line++;
                    break;

                case '`':                                                       // `Comments`
                    while (!match('`', true)) { continue; }
                    break;

                default:
                    cout << "Error: Unexpected character.\n";
                    break;
            }
        }
    public:
        Tokeniser(string source) {
            this->source = source;
        }

        vector<Token> scanTokens() {
            while (!isAtEnd()) {
                start = current;
                scanToken();
                cout << start << ", " << current << endl;
            }

            for (int i = 0; i < tokens.size(); i++) {
                cout << (tokens[i].lexeme) << endl;
            }

            return tokens;
        }
};

static void runFile() {
    string fileContents = cray::stringFromFile(path);

    Tokeniser tokeniser(fileContents);
    tokeniser.scanTokens();
}

// Entry Point
int main(int argc, char *argv[]) {
    // Parse Arguments
    {
    if (argc <= 1) {
        printf("Error: Incorrect number of arguments.\nCommand Usage:\n\tcec <input_file> [-cs] [--cowsay]\n");
        return -1;
    }
    path = argv[1];
    if (argc > 2) {
        for (int i = 1; i < argc; i++) {
            if (argv[i] == "-cs" | argv[i] == "--cowsay") cowsay = true;
            // If an argument is not recognised:
            else { printf("Error: Invalid arguments.\nCommand Usage:\n\tcec <input_file> [-cs] [--cowsay]\n"); return -1; }
        }
    }
    }

    // Everything else
    runFile();
}
