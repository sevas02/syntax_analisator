#ifndef SYNTAX_ANALYS_H
#define SYNTAX_ANALYS_H
#include <fstream>
#include "lex_analys.h"
#include "hash_table.h"
#include "syntax_tree.h"

//синтаксический анализатор
class synt_analysator {
private:
	lex_analysator lexemes;
	hash_table table;
	pos_error err;
	bool Function(syntax_tree&);
	bool Begin(syntax_tree&);
	bool Descriptions(syntax_tree&);
	bool Descr(syntax_tree&);
	bool Varlist(syntax_tree&);
	bool Operators(syntax_tree&);
	bool Op(syntax_tree&);
	bool Expr(syntax_tree&);
	bool Condition(syntax_tree&);
	bool S1mpleExpr(syntax_tree&);
	bool End(syntax_tree&);
public:
	syntax_tree tree;
	std::ifstream fin;
	synt_analysator(std::string filename): fin(filename) {};
	bool analys(syntax_tree&);
	void print_tree(std::ofstream& fout) { tree.print(fout); }
	~synt_analysator() {
		fin.close();
	}
};


#endif // ! SYNTAX_ANALYS_H
