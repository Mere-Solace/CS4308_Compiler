#include "Lexer.h"


bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

std::vector<Token> Lexer::scanTokens() {
    while (current < source.length()) {
        scanToken();
    }
    return tokens;
}

void Lexer::advance() {
    Lexer::c = source.at(current++);
}

void Lexer::scanToken() {
    advance();

    std::cout << c; 

    // Not handling overloaded assignment ops (+=, -=, etc.)
    // Also not handling ++ or --
    switch (c) {
        case '+': addToken(TokenType::PLUS); break;
        case '-': addToken(TokenType::MINUS); break;
        case '*':
            if (language == Python && match()) { // if there's a second *, it's an exponentiation operator
                addToken(TokenType::EXP);
                advance();
            }
            else {
                addToken(TokenType::MULTIPLY);
            }
            addToken(TokenType::MULTIPLY); 
            break;
        
        case '=': 
            if (match()) { // if there's a second =, it's an equality check
                addToken(TokenType::EQUALS);
                advance(); // consume the second =
            }
            else {
                addToken(TokenType::ASSIGN);
            }
            addToken(TokenType::ASSIGN); 
            break;

        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        
        case '/': 
            if (language == Java && match()) { // if there's a second / or *, it's a comment
                // Skip comments until end of line
                while (peek() != '\n' && current < source.length()) advance();
                break;
            }
            addToken(TokenType::DIVIDE); 
            break;

        case ' ':
        case '\r':
        case '\t':
            // Ignore whitespace
            break;

        case '\n':
            line++;
            break;

        case '"':
            string();
            break;

        case '#':
            if (language == Java) {
                break;
            }
            // Skip comments until end of line
            while (peek() != '\n' && current < source.length()) advance();
            break;
        
        default:
            if (isDigit(c)) {
                number();
            }
            else if (isAlpha(c)) {
                identifier();
            }
            else {
                std::cout << "unexpected: " << c;
                // unexpected stuff ?
                break;
            }
        
    }

    lexeme = ""; // reset (flush) word
}

bool Lexer::match() {
    switch (c) {
        case '=':
        case '!':
        case '<':
        case '>':
            return peek() == '=';
        case '&':
            return peek() == '&';
        case '|':
            return peek() == '|';
        case '/':
        case '*':
            return peek() == '/' || peek() == '*';
        default:
            return false;
    }
}

void Lexer::string() {
    advance();
    while (c != '"') {
        lexeme += c;
        advance();
    }
    addToken(TokenType::STRING_LITERAL);
}

void Lexer::identifier() {
    lexeme += c;
    while (isAlpha(peek()) || isDigit(peek())) {
        lexeme += peek();
        advance();
    }

    // Check if the identifier is a keyword
    if (language == Python && python_keywords.count(lexeme)) {
        addToken(TokenType::KEYWORD);
    }
    else if (language == Java && java_keywords.count(lexeme)) {
        addToken(TokenType::KEYWORD);
    }
    else {
        addToken(TokenType::IDENTIFIER);
    }
}

void Lexer::number() {
    lexeme += c;
    while (isDigit(peek())) {
        lexeme += peek();
        advance();
    }
}

void Lexer::addToken(TokenType type) {
    if (lexeme == "") {
        tokens.push_back(Token { type, std::string{c}, line});
    }
    else {
        tokens.push_back(Token { type, lexeme, line});
    }
}
