#pragma once

#include "token.hpp"

// Stl
#include <vector>

namespace parser
{
class CScanner
{
public:
    CScanner() = default;
    ~CScanner() = default;

public:
    // Scans of line and create tokens from it
    std::vector<SToken> execute( const std::string& sStream );

private:
    void scanToken();
    bool isEndOfLine() const;
    char next();
    void addToken( CTokenType sType );
    char peek() const;
    char peekNext() const;
    bool match( char charachter );
    void takeNumber();
    void takeString();
    void takeIdentifier();

private:
    std::string             m_sStream;
    std::vector<SToken>     m_arrTokens;
    size_t                  m_nIdxCurrent {0};
    size_t                  m_nIdxTokenStart {0};
    size_t                  m_nLine {0};
};

}