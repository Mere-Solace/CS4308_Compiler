#include "RDP.h"

// 

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

