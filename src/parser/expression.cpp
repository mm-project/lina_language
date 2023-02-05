#include "expression.hpp"

namespace parser
{

IExpression::~IExpression()
{}

CUnaryExpression::CUnaryExpression( IExpressionPtr pLeft, const SToken& op )
                : m_pLeft( pLeft )
                , m_Operator( op )
{}

CBinaryExpression::CBinaryExpression( IExpressionPtr pLeft, const SToken& op, IExpressionPtr pRight )
                : m_pLeft( pLeft )
                , m_Operator ( op )
                , m_pRight( pRight )
{}

CLiteralExpression::CLiteralExpression( const IValue& value )
                : m_Value( value )
{}

}