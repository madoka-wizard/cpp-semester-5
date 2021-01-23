#pragma once

#include "visitor.h"
#include <string>
#include <vector>

namespace compiler {
class Object {
public:
    virtual std::string accept(Visitor *visitor) const = 0;

    virtual std::string describe() const;
};

class Statement : public Object {
public:
    std::string describe() const override;
};

class Expression : public Object {
public:
    std::string describe() const override;
};

class Declaration final : public Statement {
public:
    std::vector<Var *> variables;

    std::string describe() const override;

    std::string accept(Visitor *visitor) const override;
};

class Assignment final : public Statement {
public:
    Var *variable;
    Expression *expression;

    std::string describe() const override;

    std::string accept(Visitor *visitor) const override;
};

class Block final : public Statement {
public:
    std::vector<Statement *> statements;

    std::string describe() const override;

    std::string accept(Visitor *visitor) const override;
};

class Conditional final : public Statement {
public:
    Var *expression;
    Statement *left, *right;

    std::string describe() const override;

    std::string accept(Visitor *visitor) const override;
};

class Loop final : public Statement {
public:
    Expression *expression;
    Statement *body;

    std::string describe() const override;

    std::string accept(Visitor *visitor) const override;
};

class Const final : public Expression {
public:
    std::string describe() const override;

    std::string accept(Visitor *visitor) const override;

    int value{0};
};

class Var final : public Expression {
public:
    std::string describe() const override;

    std::string accept(Visitor *visitor) const override;

    std::string name;
};

class BinaryOp : public Expression {
public:
    Var *left, *right;

    std::string describe() const override;
};

class Sum final : public BinaryOp {
public:
    std::string describe() const override;

    std::string accept(Visitor *visitor) const override;
};

class Prod final : public BinaryOp {
public:
    std::string describe() const override;

    std::string accept(Visitor *visitor) const override;
};

class Less final : public BinaryOp {
public:
    std::string describe() const override;

    std::string accept(Visitor *visitor) const override;
};

class And final : public BinaryOp {
public:
    std::string describe() const override;

    std::string accept(Visitor *visitor) const override;
};

class Or final : public BinaryOp {
public:
    std::string describe() const override;

    std::string accept(Visitor *visitor) const override;
};

class Not final : public Expression {
public:
    Expression *expression;

    std::string describe() const override;

    std::string accept(Visitor *visitor) const override;
};
} // namespace compiler
