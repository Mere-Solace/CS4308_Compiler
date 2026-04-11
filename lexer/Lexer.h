#pragma once

#include <string>
#include <vector>
#include <malloc.h>
#include <map>

#include "Token.h"

class Lexer {
public:
    Lexer(const std::string& source, Language lang = Java) : 
    source(source), language(lang) {};
    std::vector<Token> scanTokens();
    static std::map<char, std::map<char, TokenType>> match_pairs;

private:
    void scanToken();
    void advance();
    char peek();
    bool match();
    void addMatch(TokenType type);
    void addToken(TokenType type);
    void string();
    void number();
    void identifier();

    std::string source;
    Language language;

    std::vector<Token> tokens;
    std::string lexeme = "";
    char c = ' ';
    int start = 0;
    int current = 0;
    int line = 1;
};
