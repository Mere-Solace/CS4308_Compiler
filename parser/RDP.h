#pragma once

#include <string>
#include <vector>
#include <malloc.h>

#include "ParseTree.h"

// Need a larger grammer to test the RDP...

// start:
//    | if_stmt
//    | block if_stmt:

// if_stmt:
//     | 'if' named_expression ':' block elif_stmt 
//     | 'if' named_expression ':' block [else_block] 
// elif_stmt:
//     | 'elif' named_expression ':' block elif_stmt 
//     | 'elif' named_expression ':' block [else_block] 
// else_block:
//     | 'else' ':' block 

// Recursive Descent Parser
class RDP {
public:
    RDP(std::vector<Token> tokenized, Language lang = Java) :
    tokenized(tokenized), language(lang) {};

    void parse();

    void printParseTree() {
        parseTree.printTree(parseTree.root);
    }

    const static std::vector<std::string> key_word_list;

private:
    std::vector<Token> tokenized;
    Language language;
    int current = 0; // index of the current token being processed
    ParseTreeNode* currentNode; // pointer to the current node in the parse tree

    ParseTree parseTree; // define a ParseTree class to represent the parse tree

    bool consume(TokenType expected);
    bool consume(std::string expected_lex, TokenType expected_type);

    // create subprograms for each non-terminal
    void start();
    void if_stmt();
    void elif_stmt();
    void else_block();
    void named_expression();
    void block();
};