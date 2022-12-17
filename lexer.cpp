#include "lexer.h"
#include <iostream>

const std::string delims = " \n\t\v\f\r)";

std::unique_ptr<Atom> lex_quoted(std::istream& stream) {
    char quote_char = stream.get();
    std::string str;
    std::getline(stream, str, quote_char);

    if (stream.eof()) {
        throw std::runtime_error("Missing quote");
    }

    // Add the quotes
    str.insert(str.begin(), quote_char);
    str.push_back(quote_char);

    return std::make_unique<Atom>(str);
}

std::unique_ptr<Atom> lex_atom(std::istream& stream) {
    char first = stream.peek();
    bool is_escaped = (first == '\"' || first == '\'');
    
    if (is_escaped) {
        return lex_quoted(stream);
    } else {
        std::string str;
        while (true) {
            char c = stream.get();

            if (delims.find(c) != std::string::npos) {
                if (c == ')') {
                    stream.unget();
                }
                break;
            }
            str.push_back(c);
        }
        return std::make_unique<Atom>(str);
    }
}

std::unique_ptr<List> lex(std::istream& stream) {
    if (stream.get() != '(') {
        throw std::runtime_error("Malformed s-expression");
    }

    std::vector<EitherAtomOrList> vec;

    char c = stream.peek();
    while (!stream.eof() && c != ')') {
        if (c != '(') {
            auto atom = lex_atom(stream);
            if (!atom->is_empty()) {
                vec.emplace_back(std::move(atom));
            }
        } else {
            auto list = lex(stream);
            vec.emplace_back(std::move(list));
        }
        c = stream.peek();
    }
    stream.get();
    
    return std::make_unique<List>(std::move(vec));
}
