#pragma once

#include "visitor.h"
#include "ast_node.h"
#include <string>

namespace compiler {
class AssemblerCompiler final : public Visitor {
public:
    AssemblerCompiler();

    std::string do_declaration(const Declaration *declaration) override;

    std::string do_assignment(const Assignment *assignment) override;

    std::string do_loop(const Loop *loop) override;

    std::string do_block(const Block *block) override;

    std::string do_conditional(const Conditional *conditional) override;

    std::string do_var(const Var *variable) override;

    std::string do_const(const Const *constant) override;

    std::string do_sum(const Sum *sum) override;

    std::string do_prod(const Prod *prod) override;

    std::string do_less(const Less *less) override;

    std::string do_and(const And *logical_and) override;

    std::string do_or(const Or *logical_or) override;

    std::string do_not(const Not *logical_not) override;

private:
    std::size_t label_counter_;
};
} // namespace compiler
