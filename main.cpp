#include <iostream>
#include <fstream>
#include "hash_table.h"
#include "lex_analys.h"
#include "syntax_analys.h"

int main() {
    setlocale(0, "RUS");
    hash_table table;
    lex_analysator lex;
    synt_analysator anal("input.txt");
    std::ofstream fout("result.txt");
    std::string str = "";
    if (anal.analys(anal.tree)) {
        std::cout << "Программа завершила работу с кодом 0.";
        anal.print_tree(fout);
    }
    fout.close();
	return 0;
}