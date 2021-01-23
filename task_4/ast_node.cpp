#include "ast_node.h"

namespace compiler {
// Object
std::string Object::describe() const { return "Object"; }

// Statement
std::string Statement::describe() const { return "Statement"; }

// Expression
std::string Expression::describe() const { return "Expression"; }

// Declaration
std::string Declaration::describe() const { return "Declaration"; }

std::string Declaration::accept(Visitor *visitor) const {
    return visitor->do_declaration(this);
}

// Assignment
std::string Assignment::describe() const { return "Assignment"; }

std::string Assignment::accept(Visitor *visitor) const {
    return visitor->do_assignment(this);
}

// Block
std::string Block::describe() const { return "Block"; }

std::string Block::accept(Visitor *visitor) const {
    return visitor->do_block(this);
}

// Conditional
std::string Conditional::describe() const { return "Conditional"; }

std::string Conditional::accept(Visitor *visitor) const {
    return visitor->do_conditional(this);
}

// Loop
std::string Loop::describe() const { return "Loop"; }

std::string Loop::accept(Visitor *visitor) const {
    return visitor->do_loop(this);
}

// Const
std::string Const::describe() const { return "Const"; }

std::string Const::accept(Visitor *visitor) const {
    return visitor->do_const(this);
}

// Var
std::string Var::describe() const { return "Var"; }

std::string Var::accept(Visitor *visitor) const {
    return visitor->do_var(this);
}

// BinaryOp
std::string BinaryOp::describe() const { return "BinaryOp"; }

// Sum
std::string Sum::describe() const { return "Sum"; }

std::string Sum::accept(Visitor *visitor) const {
    return visitor->do_sum(this);
}

// Prod
std::string Prod::describe() const { return "Prod"; }

std::string Prod::accept(Visitor *visitor) const {
    return visitor->do_prod(this);
}

// Less
std::string Less::describe() const { return "Less"; }

std::string Less::accept(Visitor *visitor) const {
    return visitor->do_less(this);
}

// And
std::string And::describe() const { return "And"; }

std::string And::accept(Visitor *visitor) const {
    return visitor->do_and(this);
}

// Or
std::string Or::describe() const { return "Or"; }

std::string Or::accept(Visitor *visitor) const {
    return visitor->do_or(this);
}

// Not
std::string Not::describe() const { return "Not"; }

std::string Not::accept(Visitor *visitor) const {
    return visitor->do_not(this);
}
} // namespace compiler
