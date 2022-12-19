#pragma once
#include <iostream>
#include <istream>
#include <vector>
#include <memory>
#include <variant>
#include <stdexcept>
#include <functional>

class Atom;
class List;

using EitherAtomOrList = std::variant<std::unique_ptr<Atom>, std::unique_ptr<List>>;

class Atom {
public:
    Atom(std::string token) : token(token) {}

    bool is_empty() const {
        return token.length() == 0;
    }

    std::string to_string() const {
        return token;
    }

private:
    std::string token;
};

class List {
public:
    List(std::vector<EitherAtomOrList> items) : items(std::move(items)) {}

    std::string to_string() const;

    const std::vector<EitherAtomOrList>& get_items() const {
        return items;
    }

private:
    std::vector<EitherAtomOrList> items;
};

// Can throw (really bad) exceptions
std::unique_ptr<List> lex(std::istream&);

void print(const std::unique_ptr<Atom>& atom);
void print(const std::unique_ptr<List>& list);
