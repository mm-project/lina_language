#pragma once

#include "token.hpp"
#include "expression.hpp"

// Stl
#include <vector>

namespace parser
{
class CParser
{
public:
    CParser() = default;
    ~CParser() = default;

public:
    std::vector<IExpressionPtr> execute( const std::vector<SToken>& arrTokens );

protected:
    IExpressionPtr equality();
    IExpressionPtr comparison();
    IExpressionPtr addition();
    IExpressionPtr multiplication();
    IExpressionPtr unary();

private:
    bool isEndOfLine() const;
    SToken next();
    SToken peek() const;
    SToken previous() const;

private:
    std::vector<SToken>     m_arrTokens;
    int                     m_nIdxCurrent {0};
};
}