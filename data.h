#ifndef DATA_H
#define DATA_H
#define NPOS "-1"
#include <string>
#include <iostream>

class info {
public:
    std::string lexem;
    std::string type;
    friend std::ostream& operator<<(std::ostream&, const info&);
    friend std::istream& operator>>(std::istream&, info&);
    bool operator ==(const info& data);
    void operator =(const info& data);
    std::string lex_plus_typ();
    info();
    info(int npos);
    info(std::string lex, std::string typ);
};

#endif