#include "assembler.h"

namespace compiler {
AssemblerCompiler::AssemblerCompiler() : label_counter_{1} {}

std::string AssemblerCompiler::do_declaration(const Declaration *declaration) {
    std::string temp;
    for (auto i : declaration->variables) {
        temp += "DECL " + i->accept(this) + ";";
    }
    return temp;
}

std::string AssemblerCompiler::do_assignment(const Assignment *assignment) {
    auto common_prefix = [&] {
        if (assignment->expression->describe() == "Const") {
            return "MOVC ";
        } else {
            return "MOV ";
        }
    };
    return common_prefix() + assignment->variable->accept(this) + " " + assignment->expression->accept(this) + ";";
}

std::string AssemblerCompiler::do_loop(const Loop *loop) {
    auto temp = "LABEL " + std::to_string(label_counter_) + ";" + loop->body->accept(this) + "GOTOIF " +
                loop->expression->accept(this) + " " + std::to_string(label_counter_) + ";";
    ++label_counter_;
    return temp;
}

std::string AssemblerCompiler::do_block(const Block *block) {
    std::string temp;
    for (auto i : block->statements) {
        temp += i->accept(this);
    }
    return temp;
}

std::string AssemblerCompiler::do_var(const Var *variable) {
    return variable->name;
}

std::string AssemblerCompiler::do_const(const Const *constant) {
    return std::to_string(constant->value);
}

std::string AssemblerCompiler::do_less(const Less *less) {
    return "LESS " + less->left->accept(this) + " " + less->right->accept(this) + ";";
}

std::string AssemblerCompiler::do_sum(const Sum *sum) {
    return "ADD " + sum->left->accept(this) + " " + sum->right->accept(this) + ";";
}

std::string AssemblerCompiler::do_prod(const Prod *prod) {
    return "MUL " + prod->left->accept(this) + " " + prod->right->accept(this) + ";";
}

std::string AssemblerCompiler::do_and(const And *logical_and) {
    return "AND " + logical_and->left->accept(this) + ", " + logical_and->right->accept(this) + ";";
}

std::string AssemblerCompiler::do_or(const Or *logical_or) {
    return "OR " + logical_or->left->accept(this) + ", " + logical_or->right->accept(this) + ";";
}

std::string AssemblerCompiler::do_not(const Not *logical_not) {
    return "NOT " + logical_not->expression->accept(this) + ";";
}

std::string AssemblerCompiler::do_conditional(const Conditional *conditional) {
    auto label_true = label_counter_++;
    auto label_false = label_counter_++;

    return "GOTOIF " + conditional->expression->accept(this) + ", " + std::to_string(label_true) + ";" +
           conditional->right->accept(this) +
           "GOTOIF 1, " + std::to_string(label_false) + ";" +
           "LABEL " + std::to_string(label_true) + ";" +
           conditional->left->accept(this) +
           "LABEL " + std::to_string(label_false) + ";";
}
} // namespace compiler
