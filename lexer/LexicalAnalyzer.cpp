#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

    std::vector<int> lex_lens = std::vector<int>();
    std::vector<int> type_lens = std::vector<int>();
    
    int max_length_lex = 0;
    int max_length_type = 0;
    for (int i = 0; i < tokenized.size(); i++) {
        lex_lens.push_back((int)tokenized.at(i).lexeme.length());
        max_length_lex = std::max(max_length_lex, lex_lens.at(i));
        type_lens.push_back((int)enumToString(tokenized.at(i).type).length());
        max_length_type = std::max(max_length_type, type_lens.at(i));
    }

    std::string lex_bar = std::string(max_length_lex + 2, '=');
    std::string type_bar = std::string(max_length_type + 2, '=');
    std::cout << "+" << lex_bar << "+" << type_bar << "+" << std::endl;
    int len = 0;
    for (int i = 0; i < tokenized.size(); i++) {
        std::cout << "| ";
        len = lex_lens.at(i);
        for (int j = 0; j < max_length_lex - len; j++) {
            std::cout << " ";
        }       
        std::cout << tokenized.at(i).lexeme << " | ";
        len = type_lens.at(i);
        for (int j = 0; j < max_length_type - len; j++) {
            std::cout << " ";
        }
        std::cout << enumToString(tokenized.at(i).type) << " |" << std::endl;
    }
    std::cout << "+" << lex_bar << "+" << type_bar << "+" << std::endl;
}
