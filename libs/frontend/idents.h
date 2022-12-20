#pragma once
#include <vector>
#include <optional>
#include <initializer_list>

// Might not actually be a HKT idk
enum class Kind {
    BASE,
    FUNCTION
};

// TODO add more types
enum class BaseType {
    INT
};

class Type {
public:
    Type(Kind kind, std::vector<BaseType> subtypes) : kind(kind), subtypes(std::move(subtypes)) {}
    Type(Kind kind, std::initializer_list<BaseType> subtypes) : kind(kind), subtypes(std::move(subtypes)) {}

    inline bool operator==(const Type& rhs) { 
        return this->kind == rhs.kind && this->subtypes == rhs.subtypes;   
    }

    inline bool operator!=(const Type& rhs) { return !(*this == rhs); }

    // Helper functions
    static Type Int() {
        return Type(Kind::BASE, {BaseType::INT});
    }

private:
    Kind kind;
    std::vector<BaseType> subtypes; // TODO: make this work for function pointers etc?
};

using Location = std::optional<std::string>;