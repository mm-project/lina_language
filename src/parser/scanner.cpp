#include "scanner.hpp"

#include <cctype>
#include <unordered_map>

namespace parser
{
static std::unordered_map<std::string, CTokenType> mapKeywords = {
    { "and", CTokenType::AND },
    { "or", CTokenType::OR },
    { "return", CTokenType::RETURN },
    { "var", CTokenType::VAR },
    { "fun", CTokenType::FUN },
    { "if", CTokenType::IF },
    { "else", CTokenType::ELSE },
    { "true", CTokenType::TRUE },
    { "false", CTokenType::FALSE },
    { "nil", CTokenType::NIL },
    { "class", CTokenType::CLASS },
    { "for", CTokenType::FOR },
    { "while", CTokenType::WHILE }
};


std::vector<SToken> CScanner::execute( const std::string& sStream )
{
    // while is end of line 
    // advance to the next token 
    // clear previous info
    m_arrTokens.clear();
    m_nIdxCurrent = 0;
    m_nIdxTokenStart = 0;

    while ( !isEndOfLine() )
    {
        m_nIdxTokenStart = m_nIdxCurrent;
        scanToken();
    }
    // add token EOF
    addToken( CTokenType::_EOF ); // TODO: will this work?
    ++m_nLine;

    return m_arrTokens;
}

void CScanner::scanToken()
{
    auto charachter = next();
    switch( charachter )
    {
        case ';':
            addToken( CTokenType::SEMICOLON );
            break;
        case '+':
            addToken( CTokenType::PLUS );
            break;
        case '-':
            addToken( CTokenType::MINUS );
            break;
        case '/':
            if ( match( '/') ) // comment
            {
                while ( peek() != '\n' && !isEndOfLine() )
                    next();
            }
            else
                addToken( CTokenType::DIVISION );
            break;
        case '*':
            addToken( CTokenType::MULTIPLICATION );
            break;
        case '(':
            addToken( CTokenType::LEFT_PAREN );
            break;
        case ')':
            addToken( CTokenType::RIGHT_PAREN );
            break;
        case '{':
            addToken( CTokenType::LEFT_BRACE );
            break;
        case '}':
            addToken( CTokenType::RIGHT_BRACE );
            break;
        case '.':
            addToken( CTokenType::DOT );
            break;
        case '=':
            ( match('=') ) ? addToken( CTokenType::EQUAL_EQUAL) : addToken( CTokenType::EQUAL );
            break;
        case '>':
            ( match('=') ) ? addToken( CTokenType::GRATHER_EQUAL) : addToken( CTokenType::GRATHER );
            break;
        case '<':
            ( match('=') ) ? addToken( CTokenType::LESS_EQUAL) : addToken( CTokenType::LESS );
            break;
        case '!':
            ( match('=') ) ? addToken( CTokenType::BANG_EQUAL) : addToken( CTokenType::BANG );
            break;
        case ' ':
        case '\t':
        case '\r':
            break;
        case '\n':
            ++m_nLine;
            break;
        case '"':
            takeString();
            break;
        default:
            if ( isdigit( static_cast<unsigned char>( charachter ) ) )
            {
                takeNumber();
            }
            if ( std::isalpha( static_cast<unsigned char> (charachter ) ) )
            {
                takeIdentifier();
            }
            else
            {
                // TODO: throw an exception?
            }
            break;
    }
} 

void CScanner::addToken( CTokenType eType )
{
    std::string sToken;
    if ( eType == CTokenType::STRING )
    {
        // trim the ""
        sToken = m_sStream.substr( m_nIdxTokenStart + 1, m_nIdxCurrent - 1 );
    }
    else if ( eType  != CTokenType::_EOF )
    {
        sToken = m_sStream.substr( m_nIdxTokenStart, m_nIdxCurrent - m_nIdxTokenStart );
    }
    m_arrTokens.emplace_back( SToken { eType, sToken } );
}

bool CScanner::isEndOfLine() const
{
    return m_nIdxCurrent >= m_sStream.size();
}

char CScanner::next()
{
    ++m_nIdxCurrent;
    return peek();
}

char CScanner::peek() const
{
    if ( isEndOfLine() )
        return '\0';
    return m_sStream[m_nIdxCurrent];
}

char CScanner::peekNext() const
{
    if ( isEndOfLine() )
        return '\0';
    return m_sStream[m_nIdxCurrent + 1];
}

bool CScanner::match( char charachter )
{
    if ( isEndOfLine() )
        return false;

    if ( peek() != charachter )
        return false;

    ++m_nIdxCurrent;
    return true;
}

void CScanner::takeNumber()
{
    // The first part of the number 
    while( isdigit( static_cast<unsigned char>( next() ) ) )
        next();
    
    // Then can be "." and the next should be as well the number
    if ( peek() == '.' && isdigit( static_cast<unsigned char>( peekNext() ) ) )
        next();

    // Read the number after the .
    while( isdigit( static_cast<unsigned char>( next() ) ) )
        next();

    addToken( CTokenType::NUMBER ); // TODO: this might not work
}

void CScanner::takeString()
{
    while( peek() != '"' && !isEndOfLine() )
    {
        if ( peek() == '\n')
            ++m_nLine;
        next();
    }

    if ( isEndOfLine() )
    {
        // TODO: Error not terminated string
        return;
    }

    // The closing "
    next();
    addToken( CTokenType::STRING );
}

void CScanner::takeIdentifier()
{
    while ( std::isalpha( static_cast<unsigned char >( peek() ) ) 
            || isdigit( static_cast<unsigned char >( peek() ) ) )
        next();

    CTokenType eType;
    auto sToken = m_sStream.substr( m_nIdxTokenStart, m_nIdxCurrent );
    ( mapKeywords.find( sToken ) != mapKeywords.end() ) 
        ? eType = mapKeywords[sToken]
        : eType = CTokenType::IDENTIFIER;

    addToken( eType );
}

}