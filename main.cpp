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
    //std::ifstream fin("input.txt");
    std::ofstream fout("result.txt");
    std::string str = "";
    std::cout << anal.analys(anal.tree);
    //table.print(fout);
    anal.print_tree(fout);
    fout.close();
	return 0;
}

/*
int main() {
int a,b,c,d,e1,1rfefc;
int digit = 5;
int i;
for (i; i <=10; i+1) {
    digit = digit - 1;
    5 == 2;
}

return 0;
}*/