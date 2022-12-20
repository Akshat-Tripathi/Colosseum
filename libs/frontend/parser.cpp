#include <stdexcept>
#include "parser.h"
#include "idents.h"

Type parse_type(const Atom& atom);
std::unique_ptr<Stmt> parse_statement(const List& list);
std::unique_ptr<Expr> parse_expression(const EitherAtomOrList& either);

std::unique_ptr<Variable> parse_variable(const List& list);
std::unique_ptr<MultiStmt> parse_multistmt(const List& list);
std::unique_ptr<ConstExpr> parse_constexpr(const Atom& atom);
std::unique_ptr<ReturnStmt> parse_returnstmt(const List& list);
std::unique_ptr<FunctionDef> parse_function(const List& list);


void fail_parse(std::string message, const List& list) {
    throw std::runtime_error(message + ": " + list.to_string());
}

void fail_parse(std::string message, const Atom& atom) {
    throw std::runtime_error(message + ": " + atom.to_string());
}

std::unique_ptr<MultiStmt> parse(const List& list) {
    return parse_multistmt(list);
}

std::unique_ptr<Stmt> parse_statement(const List& list) {
    auto& items = list.get_items();
    auto& first = std::get<std::unique_ptr<Atom>>(items[0]); //TODO - better error handling for noops
    std::string token = first->to_string();

    if (token == "return") {
        return parse_returnstmt(list);
    } else if (token == "defun") {
        return parse_function(list);
    }

    fail_parse("Invalid statement", *first);
    return std::unique_ptr<Stmt>(nullptr);
}

std::unique_ptr<Expr> parse_expression(const EitherAtomOrList& either) {
    //TODO fill out the non constexpr case
    auto& atom = std::get<std::unique_ptr<Atom>>(either);
    return parse_constexpr(*atom);
}

std::unique_ptr<ConstExpr> parse_constexpr(const Atom& atom) {
    return std::make_unique<ConstExpr>(atom.to_string());
}

Type parse_type(const Atom& atom) {
    if (atom.to_string() == "int") {
        return Type::Int();
    }
    fail_parse("Unknown type", atom);
    return Type::Int(); // Get the compiler to shut up
}

Location parse_location(const Atom& atom) {
    return Location{atom.to_string()};
}

//TODO: do
std::unique_ptr<Variable> parse_variable(const List& list) {
    return std::make_unique<Variable>("todo", Type::Int(), Location());
}

std::unique_ptr<ReturnStmt> parse_returnstmt(const List& list) {
    auto& items = list.get_items();
    auto expr = parse_expression(items[1]);
    return std::make_unique<ReturnStmt>(expr); //Surely this doesn't work
}

std::unique_ptr<MultiStmt> parse_multistmt(const List& list) {
    auto& items = list.get_items();
    std::vector<std::unique_ptr<Stmt>> stmts(items.size());

    std::transform(items.begin(), items.end(), stmts.begin(),
    [](const EitherAtomOrList& either) -> std::unique_ptr<Stmt> {
        auto& list = std::get<std::unique_ptr<List>>(either);
        return parse_statement(*list);
    });

    return std::make_unique<MultiStmt>(stmts);
}

std::unique_ptr<FunctionDef> parse_function(const List& list) {
    auto& items = list.get_items();

    if (items.size() != 6 && items.size() != 5) {
        fail_parse("Incorrect function length", list);
    }

    bool arena_present = items.size() == 6;

    Type return_type = parse_type(*std::get<std::unique_ptr<Atom>>(items[1]));
    std::string name = std::get<std::unique_ptr<Atom>>(items[2])->to_string();

    std::vector<std::unique_ptr<Variable>> args;
    auto& args_iter = std::get<std::unique_ptr<List>>(items[3])->get_items();
    std::transform(args_iter.begin(), args_iter.end(), args.begin(),
                   [](const EitherAtomOrList& either) {
                        return parse_variable(*std::get<std::unique_ptr<List>>(either));
                   });
    
    Location arena;
    std::unique_ptr<MultiStmt> body;

    if (arena_present) {
        arena = parse_location(*std::get<std::unique_ptr<Atom>>(items[4]));
        body = parse_multistmt(*std::get<std::unique_ptr<List>>(items[5]));
    } else {
        body = parse_multistmt(*std::get<std::unique_ptr<List>>(items[4]));
    }
    
    return std::make_unique<FunctionDef>(return_type, name, args, arena, body);
}

