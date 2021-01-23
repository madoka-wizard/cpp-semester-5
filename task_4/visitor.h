#pragma once

#include <string>

namespace compiler {
class Declaration;

class Assignment;

class Block;

class Conditional;

class Loop;

class Var;

class Const;

class Sum;

class Prod;

class Less;

class And;

class Or;

class Not;

class Sum;

class Visitor {
public:
    virtual std::string do_declaration(const Declaration *declaration) = 0;

    virtual std::string do_assignment(const Assignment *assignment) = 0;

    virtual std::string do_block(const Block *block) = 0;

    virtual std::string do_conditional(const Conditional *conditional) = 0;

    virtual std::string do_loop(const Loop *loop) = 0;

    virtual std::string do_var(const Var *variable) = 0;

    virtual std::string do_const(const Const *constant) = 0;

    virtual std::string do_sum(const Sum *sum) = 0;

    virtual std::string do_prod(const Prod *prod) = 0;

    virtual std::string do_less(const Less *less) = 0;

    virtual std::string do_and(const And *logical_and) = 0;

    virtual std::string do_or(const Or *logical_or) = 0;

    virtual std::string do_not(const Not *logical_not) = 0;
};
} // namespace compiler
