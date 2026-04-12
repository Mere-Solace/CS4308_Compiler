#include <iostream>

#include "../lexer/Token.h"
#include "RDP.h"

const std::vector<std::string> RDP::key_word_list = {
    "if", "elif", "else"
};

// if_stmt:
//     | 'if' named_expression ':' block elif_stmt 
//     | 'if' named_expression ':' block [else_block] 
// elif_stmt:
//     | 'elif' named_expression ':' block elif_stmt 
//     | 'elif' named_expression ':' block [else_block] 
// else_block:
//     | 'else' ':' block 


// test with:

// x = 10
// if x < 0:
//     print("x is negative")
// elif x == 0:
//     print("x is zero")
// else:
//     print("x is positive")

// RDP algorithm:
// S()
// {     Choose any S production, S ->X1X2…..Xk;
//       for (i = 1 to k)
//       {
//           If ( Xi is a non-terminal)
//           Call procedure Xi();
//           else if ( Xi equals the current input, increment input)
//           Else /* error has occurred, backtrack and try another possibility */
//       }
// }

void RDP::parse() {
    parseTree = ParseTree();
    parseTree.setRoot(new ParseTreeNode("Start"));
    start();
    std::cout << "Parse successful!" << std::endl;
}

bool RDP::consume(std::string expected_lex, TokenType expected_type) {
    if (tokenized.at(current).type == expected_type && tokenized.at(current).lexeme == expected_lex) {
        parseTree.root->addChild(new ParseTreeNode(tokenized.at(current).lexeme));
        current++;
    }
    else {
        std::cerr << "Error at line " << tokenized.at(current).line << ": " 
        << "Expected " << expected_lex << " but found " 
        << tokenized.at(current).lexeme << std::endl;
        exit(1);
    }
    return true;
}

bool RDP::consume(TokenType expected) {
    if (tokenized.at(current).type == expected) {
        parseTree.root->addChild(new ParseTreeNode(tokenized.at(current).lexeme));
        current++;
    }
    else {
        std::cerr << "Error at line " << tokenized.at(current).line << ": " 
        << "Expected " << Token::enumToString(expected) << " but found " 
        << tokenized.at(current).lexeme << std::endl;
        exit(1);
    }
    return true;
}

bool check_token(Token token, std::string expected_lex, TokenType expected_type) {
    return token.type == expected_type && token.lexeme == expected_lex;
}

void RDP::start() {
    block();
    if_stmt();
}

void RDP::if_stmt() {
    consume("if", TokenType::KEYWORD);
    named_expression();
    consume(TokenType::COLON);
    block();
    if (check_token(tokenized.at(current), "else", TokenType::KEYWORD)) {
        else_block();
    }
    else {
        elif_stmt();
    }
}

void RDP::elif_stmt() {
    consume("elif", TokenType::KEYWORD);
    named_expression();
    consume(TokenType::COLON);
    block();
    if (check_token(tokenized.at(current), "else", TokenType::KEYWORD)) {
        else_block();
    }
    else {
        elif_stmt();
    }
}

void RDP::else_block() {
    consume("else", TokenType::KEYWORD);
    consume(TokenType::COLON);
    block();
}

void RDP::named_expression() {
    while (tokenized.at(current).type != TokenType::COLON
        && tokenized.at(current).type != TokenType::END_OF_FILE
        && tokenized.at(current).type != TokenType::KEYWORD) {
        current++;
    }
}

void RDP::block() {
    // for now, just consume tokens until we hit a keyword or end of file
    while (tokenized.at(current).type != TokenType::KEYWORD
        && tokenized.at(current).type != TokenType::END_OF_FILE) {
        current++;
    }
}
