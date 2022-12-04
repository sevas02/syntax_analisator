#include "data.h"
#include <string>
#include <iostream>
#define NPOS "-1"

info::info() {
    lexem = "";
    type = "";
}

info::info(int npos) {
    if (npos == -1) {
        this->lexem = NPOS;
        this->type = NPOS;
    }
    if (npos == 0) {
        this->lexem = "0";
        this->type = "0";
    }
}

info::info(std::string lex, std::string typ) {
    this->lexem = lex;
    this->type = typ;
}

std::string info::lex_plus_typ() {
    return this->lexem + " " + this->type;
}

std::ostream& operator<<(std::ostream& output, const info& d) {
    output << d.type << " " << "'" << d.lexem << "'";
    return output;
}

std::istream& operator>>(std::istream& input, info& d) {
    input >> d.lexem;
    input >> d.type;
    return input;
}

bool info::operator ==(const info& d) {
    return (lexem == d.lexem);
}

void info::operator =(const info& data) {
    lexem = data.lexem;
    type = data.type;
}