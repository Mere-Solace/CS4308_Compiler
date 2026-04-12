#include <iostream>
#include <fstream>

#include "../lexer/Lexer.h"
#include "RDP.h" // Recursive Descent Parser

// to compile:
// g++ -std=c++17 parser/ParserDriver.cpp parser/RDP.cpp lexer/Lexer.cpp -o parser.exe

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    std::string extension = filename.substr(filename.find_last_of(".") + 1);
    Language lang;
    if (extension == "py") {
        lang = Python;
    }
    else if (extension == "java") {
        lang = Java;
    }
    else {
        std::cout << "Unsupported file type: " << extension << std::endl;
        return 1;
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open file: " << filename << std::endl;
        return 1;
    }

    std::string source = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()).append("\0"); // add null terminator to the end of the source string

    Lexer lexer(source, lang);
    std::vector<Token> tokenized = lexer.scanTokens();

    printLexTable(tokenized);

    RDP parser(tokenized, lang);
    parser.parse();

    parser.printParseTree();

    return 0;
}