#pragma once

#include <regex>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>

enum class TokenType {
    PLUS,
    MINUS,
    MULTIPLY,
    EXP,
    DIVIDE,
    ASSIGN,
    EQUALS,
    NOT_EQUAL,
    LESS_THAN,
    GREATER_THAN,
    LESS_THAN_OR_EQUAL,
    GREATER_THAN_OR_EQUAL,
    AND,
    OR,
    NOT,
    LEFT_SHIFT,
    RIGHT_SHIFT,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    LEFT_SQUARE_BRACKET,
    RIGHT_SQUARE_BRACKET,
    SEMICOLON,
    COLON,
    COMMA,
    IDENTIFIER,
    INTEGER_LITERAL,
    FLOAT_LITERAL,
    STRING_LITERAL,
    KEYWORD,
    DOT,
    END_OF_FILE,
    COMMENT,
    BLOCK_COMMENT
};






struct Token {
    TokenType type;
    std::string lexeme;
    int line;
public:
    static std::string enumToString(TokenType type);
};

enum Language 
{
    Python,
    Java
};

// Define the keywords for both Python and Java
inline const std::unordered_set<std::string> python_keywords = {
    "False",    "None",     "True", "and",      "as",   "assert",   "break",    "class",
    "continue", "def",      "del",  "elif",     "else", "except",   "finally",  "for",
    "from",     "global",   "if",   "import",   "in",   "is",
    "lambda",   "nonlocal", "not",  "or",       "pass"
};
inline const std::unordered_set<std::string> java_keywords = {
    "abstract", "assert",       "boolean",  "break",    "byte",     "case",     "catch",    "char",
    "class",    "const",        "continue", "default",  "do",       "double",   "else",     "enum",
    "extends",  "final",        "finally",  "float",    "for",      "goto",     "if",       "implements",
    "import",   "instanceof",   "int",      "interface","long",     "native",   "new",      "package",
    "private",  "protected",    "public",   "return",   "short",    "static",   "strictfp", "super",
    "switch",   "synchronized", "this",     "throw",    "throws",   "transient","try",      "void",
    "volatile", "while",        "true",      "false",    "null"
};

