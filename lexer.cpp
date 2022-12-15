#include "lexer.h"
#include <iostream>

const std::string delims = " \n\t\v\f\r)";

std::unique_ptr<Atom> lex_atom(std::istream& stream) {
    char first = stream.peek();
    bool is_escaped = (first == '\"' || first == '\'');
    
    std::string str;
    if (is_escaped) {
        stream.get();
        std::getline(stream, str, first);

        //Check if the string is closed
        if (stream.eof()) {
            throw std::runtime_error("Open string still exists");
        }

        str.insert(str.begin(), first);
        str.push_back(first);
    } else {
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
    }
    return std::make_unique<Atom>(str);
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
