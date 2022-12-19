#include "lexer.h"
#include <type_traits>
#include <sstream>

const std::string delims = " \n\t\v\f\r)";

std::string _to_string(const EitherAtomOrList& either);

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

std::string List::to_string() const {
    if (items.size() == 0) {
        return "()";
    }
    std::stringstream stream;
    char hack = '(';
    for (auto& item : items) {
        stream << hack << _to_string(item);
        hack = ' ';
    }
    stream << ')';
    return stream.str();
}

void print(std::unique_ptr<Atom>& atom) {
    std::cout << atom->to_string() << std::endl;
}

void print(std::unique_ptr<List>& list) {
    std::cout << list->to_string() << std::endl;
}

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

std::string _to_string(const EitherAtomOrList& either) {
    return std::visit(overloaded {
        [](const std::unique_ptr<Atom>& atom) {return atom->to_string();},
        [](const std::unique_ptr<List>& list) {return list->to_string();}
    }, either);
}
