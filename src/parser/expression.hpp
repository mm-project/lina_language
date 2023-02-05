#pragma once

#include "token.hpp"

// Stl
#include <memory>
#include <variant>

namespace parser
{
class IExpression
{
public:
    virtual ~IExpression() = 0;
};

using IExpressionPtr = std::shared_ptr<IExpression>;
using IValue = std::variant<int, double>;

class CUnaryExpression : IExpression
{
public:
    CUnaryExpression( IExpressionPtr pLeft, const SToken& op );
    virtual ~CUnaryExpression() = default;

private:
    IExpressionPtr      m_pLeft;
    SToken              m_Operator;
};

class CBinaryExpression : IExpression
{
public:
    CBinaryExpression( IExpressionPtr pLeft, const SToken& op, IExpressionPtr pRight );
    virtual ~CBinaryExpression() = default;

private:
    IExpressionPtr      m_pLeft;
    SToken              m_Operator;
    IExpressionPtr      m_pRight;
};

class CLiteralExpression : IExpression
{
public:
    CLiteralExpression( const IValue& value );
    virtual ~CLiteralExpression() = default;

private:
    IValue  m_Value;
};

}