#pragma once
#include <vector>
#include <optional>
#include <initializer_list>
#include <sstream>

// Might not actually be a HKT idk
enum class Kind {
    BASE,
    FUNCTION
};

// TODO add more types
enum class BaseType {
    INT
};

struct Type {
    Type(Kind kind, std::vector<BaseType> subtypes) : kind(kind), subtypes(std::move(subtypes)) {}
    Type(Kind kind, std::initializer_list<BaseType> subtypes) : kind(kind), subtypes(std::move(subtypes)) {}

    inline bool operator==(const Type& rhs) { 
        return this->kind == rhs.kind && this->subtypes == rhs.subtypes;   
    }

    inline bool operator!=(const Type& rhs) { return !(*this == rhs); }

    std::string to_string() const {
        std::stringstream stream;

        switch (kind) {
        case Kind::BASE:
            if (subtypes.size() == 1) {
                return base_type_to_string(subtypes[0]);
            }
            //TODO implement for multitype case (aka tuples)
        case Kind::FUNCTION:
            std::stringstream stream;
            stream << base_type_to_string(subtypes[0]) << " func";
            char hack = '(';
            for (auto type : subtypes) {
                stream << hack << base_type_to_string(type);
                hack = ' ';
            }
            stream << ')';
            return stream.str();
        }

        return "ERROR";
    }

    // Helper functions
    static Type Int() {
        return Type(Kind::BASE, {BaseType::INT});
    }

    Kind kind;
    std::vector<BaseType> subtypes; // TODO: make this work for function pointers etc?

private:
    std::string base_type_to_string(BaseType type) const {
        switch (type) {
        case BaseType::INT:
            return "int";
        }

        return "ERROR";
    }
};

struct Location {
    Location() : loc(std::nullopt) {}
    Location(std::string str) : loc(str) {}

    std::string to_string() const {
        return loc.value_or("stack");
    }

private:
    std::optional<std::string> loc;
};
