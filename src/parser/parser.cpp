#include "parser.hpp"

namespace parser
{
std::vector<IExpressionPtr> CParser::execute( const std::vector<SToken>& arrTokens )
{
    // while end of line
    // traverse tru every token and construct an expression
}

bool CParser::isEndOfLine() const
{
    return m_arrTokens[m_nIdxCurrent].m_eType == CTokenType::_EOF;
}

SToken CParser::next()
{
    if ( !isEndOfLine() )
        ++m_nIdxCurrent;
    
    return previous();
}

SToken CParser::peek() const
{
    return m_arrTokens[m_nIdxCurrent];   
}

SToken CParser::previous() const
{
    return m_arrTokens[m_nIdxCurrent - 1];
} 

IExpressionPtr CParser::equality()
{
    return comparison();
}

IExpressionPtr CParser::comparison()
{
    return addition();
}

IExpressionPtr CParser::addition()
{
    return multiplication();
}

IExpressionPtr CParser::multiplication()
{
    return unary();
}

IExpressionPtr CParser::unary()
{
    
}

} 