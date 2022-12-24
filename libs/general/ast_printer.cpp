#include <general/printer.h>

void ASTPrinter::visit(const ConstExpr* node) {
    std::string val_str;

    if (node->type == Type::Int()) {
        val_str = std::to_string(std::get<int>(node->val));
    }

    stream << "(ConstExpr " << node->type.to_string() << ' ' << val_str << ')';
}

void ASTPrinter::visit(const MultiStmt* node) {
    stream << "(MultiStmt";
    indents++;
    for (auto& stmt : node->stmts) {
        stream << std::endl;
        print_indents();
        stmt->accept(*this);
    }
    indents--;
    stream << std::endl;
    print_indents();
    stream << ")" << std::endl;
}

void ASTPrinter::visit(const ReturnStmt* node) {
    stream << "(ReturnStmt ";
    node->rval->accept(*this);
    stream << ')';
}

void ASTPrinter::visit(const FunctionDef* node) {
    stream << "(FunctionDef " << node->return_type.to_string() << ' ' << node->name << ' ';

    std::string hack = "(";
    for (auto& arg : node->args) {
        stream << hack;
        arg->accept(*this);
        hack = ", ";
    }
    if (node->args.size() == 0) {
        stream << '(';
    }

    stream << ") " << node->arena.to_string() << std::endl;;

    indents++;
    print_indents();
    node->body->accept(*this);
    indents--;
    print_indents();
    stream << ')';
}

void ASTPrinter::visit(const Variable* node) {
    stream << '(' << node->type.to_string() << ' ' << node->name << ' ' << node->location.to_string() << ')';
}
