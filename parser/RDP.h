#pragma once

#include <string>
#include <vector>
#include <malloc.h>

#include "Token.h"
#include "ParseTree.h"

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

// Recursive Descent Parser
class RDP {
public:
    RDP(const std::string& source, Language lang = Java) :
    source(source), language(lang) {};

private:
    std::string source;
    Language language;

    ParseTree parseTree; // define a ParseTree class to represent the parse tree

    // create subprograms for each non-terminal
    void if_stmt();
    void elif_stmt();
    void else_block();

    int matchToken(TokenType expected);
};