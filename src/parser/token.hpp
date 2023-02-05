#pragma once

#include <string>

namespace parser
{

enum class CTokenType
{
     _EOF,

    // Single-charachter tokens
    SEMICOLON, DOT, 
    PLUS, MINUS, DIVISION, MULTIPLICATION,
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,

    // One or two charachter tokens
    EQUAL, EQUAL_EQUAL,
    GRATHER, GRATHER_EQUAL,
    LESS, LESS_EQUAL,
    BANG, BANG_EQUAL,

    // Literals
    NUMBER, STRING, IDENTIFIER,

    // Keywords
    AND, CLASS, IF, ELSE, FOR, WHILE, NIL, OR, RETURN,
    FUN, FALSE, TRUE, PRINT, VAR
};

struct SToken
{
    SToken( CTokenType eType, const std::string& sData ) 
    : m_eType( eType ), m_sData( sData )
    {}

    SToken( const SToken& other ) = default;

    SToken( SToken&& other ) = default;
    
    // operators

    CTokenType      m_eType;
    std::string     m_sData; 
    size_t          m_nLine {0};
};

}