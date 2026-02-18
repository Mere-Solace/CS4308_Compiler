#include <iostream>
#include <fstream>

#include "Lexer.h"

int main() {
    std::cout << "Enter name of file to lex: " << std::endl;
    std::string filename;
    std::cin >> filename;

    // strip whitespace and check extension to determine language
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

    std::string source = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    Lexer lexer(source, lang);
    std::vector<Token> tokenized = lexer.scanTokens();
    for (const auto& token : tokenized) {
        std::cout << "Token [Line " << token.line << "]\n  Lexeme: " << token.lexeme << ", Type: " << enumToString(token.type) << std::endl;
    }
}