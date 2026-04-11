#include <map>
#include <algorithm>

#include "Lexer.h"

// map of each initial char with possible next char
std::map<char, std::map<char, TokenType>> Lexer::match_pairs = {
    {'=', std::map<char, TokenType>{{'=', TokenType::EQUALS}}},
    {'!', std::map<char, TokenType>{{'!', TokenType::NOT_EQUAL}}},
    {'<', std::map<char, TokenType>{{'=', TokenType::LESS_THAN_OR_EQUAL}, {'<', TokenType::LEFT_SHIFT}}},
    {'>', std::map<char, TokenType>{{'>', TokenType::RIGHT_SHIFT}, {'=', TokenType::GREATER_THAN_OR_EQUAL}}},
    {'&', std::map<char, TokenType>{{'&', TokenType::AND}}},
    {'|', std::map<char, TokenType>{{'|', TokenType::OR}}},
    {'/', std::map<char, TokenType>{{'/', TokenType::COMMENT}, {'*', TokenType::BLOCK_COMMENT}}},
    {'*', std::map<char, TokenType>{{'*', TokenType::EXP}, {'/', TokenType::BLOCK_COMMENT}}}
};

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

char Lexer::peek() {
    // not using current + 1 since we do current++ in advance()
    if (current >= source.length()) return '\0';
    return source.at(current);
}

void Lexer::advance() {
    Lexer::c = source.at(current++);
}

bool in_map(char c) {
    return Lexer::match_pairs.find(c) != Lexer::match_pairs.end();
}

void Lexer::scanToken() {
    advance();

    // Handle multi-char tokens that exist within the 
    // match_pairs map.
    if (in_map(c)) {
        if (match()) {
            return;
        }
    }
    // not handling everything perfectly here...
    // just working towards the parser implementation
    switch (c) {
        case '+': addToken(TokenType::PLUS); break;
        case '-': addToken(TokenType::MINUS); break;
        case '<': 
            addToken(TokenType::LESS_THAN);
            break;
        case '*':
            if (language == Python && match()) { // if there's a second *, it's an exponentiation operator
                addMatch(TokenType::EXP);
            }
            else {
                addToken(TokenType::MULTIPLY);
            }
            addToken(TokenType::MULTIPLY); 
            break;
        
        // we should actually be adding the second 'matched' char to the lexeme.
        case '=': 
            if (match()) { // if there's a second =, it's an equality check
                addMatch(TokenType::EQUALS);
            }
            else {
                addToken(TokenType::ASSIGN);
            }
            break;

        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case '[': addToken(TokenType::LEFT_SQUARE_BRACKET); break;
        case ']': addToken(TokenType::RIGHT_SQUARE_BRACKET); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case ':': addToken(TokenType::COLON); break;
        
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
        case '\'':
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
                // handle member access, method calls, and array access here
                switch(c) {
                    case '.': addToken(TokenType::DOT); break;
                    case ',': addToken(TokenType::COMMA); break;
                    case '[': addToken(TokenType::LEFT_SQUARE_BRACKET); break;
                    case ']': addToken(TokenType::RIGHT_SQUARE_BRACKET); break;
                    case '(': addToken(TokenType::LEFT_PAREN); break;
                    case ')': addToken(TokenType::RIGHT_PAREN); break;
                    default:
                        std::cout << "unexpected: " << c;
                }
                break;
            }
        
    }

    lexeme = ""; // reset (flush) word
}

void Lexer::addMatch(TokenType type) {
    lexeme += c; // add the first char to the lexeme
    advance();
    lexeme += c;
    addToken(type);
}

bool Lexer::match() {
    for (const auto& pair : match_pairs[c]) {
        if (peek() == pair.first) {
            addMatch(pair.second);
            return true;
        }
    }
    return false;
}

void Lexer::string() {
    start = c;
    lexeme += start;
    advance();
    while (c != start) {
        lexeme += c;
        advance();
    }
    lexeme += start;
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
    if (peek() == '.' && isDigit(source.at(current + 1))) {
        lexeme += peek(); // add the dot
        advance();
        while (isDigit(peek())) {
            lexeme += peek();
            advance();
        }
        addToken(TokenType::FLOAT_LITERAL);
    }
    else {
        addToken(TokenType::INTEGER_LITERAL);
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
