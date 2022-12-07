#include "syntax_analys.h"
#include <iostream>

bool synt_analysator::Function(syntax_tree& t) {
	syntax_tree temp("BEGIN");
	if (!Begin(temp))
		return 0;
	t.insert_sons(temp, "FUNCTION");
	temp.uborshica();
	temp.set_root("DESCRIPTIONS");
	if (!Descriptions(temp))
		return 0;
	t.add_node_tree("DESCRIPTIONS", "FUNCTION");
	t.insert_tree(temp, "DESCRIPTIONS");
	temp.uborshica();
	temp.set_root("OPERATORS");
	if (!Operators(temp))
		return 0;
	t.add_node_tree("OPERATORS", "FUNCTION");
	t.insert_tree(temp, "OPERATORS");
	temp.uborshica();
	temp.set_root("END");
	if (!End(temp))
		return 0;
	t.add_node_tree("END", "FUNCTION");
	t.insert_tree(temp, "END");
	return (lexemes.parse(fin, table).type == "NOT_DEFINED");
}

bool synt_analysator::Begin(syntax_tree &t) {
	info elem = lexemes.parse(fin, table);
	if (elem.type != "INT") {
		err = lexemes.pos;
		std::cout << "\nОшибка! Ожидался тип метода.\n" << " строка " << err.str_number
			<< "позиция " << err.position - elem.lexem.size() << "\n";
		return 0;
	}
	t.add_node_tree(elem.lex_plus_typ(), "BEGIN");
	elem = lexemes.parse(fin, table);
	if (elem.type != "IDENTIF") {
		err = lexemes.pos;
		std::cout << "\nОшибка! Ожидалось имя метода.\n" << " строка " << err.str_number
			<< "\ позиция" << err.position - elem.lexem.size() << "\n";
		return 0;
	}
	t.add_node_tree(elem.lex_plus_typ(), "BEGIN");
	elem = lexemes.parse(fin, table);
	if (elem.type != "LBRACKET") {
		err = lexemes.pos;
		std::cout << "\nОшибка! Ожидался символ '('.\n" << " строка " << err.str_number
			<< "\ позиция" << err.position - elem.lexem.size() << "\n";
		return 0;
	}
	t.add_node_tree(elem.lex_plus_typ(), "BEGIN");
	elem = lexemes.parse(fin, table);
	if (elem.type != "RBRACKET") {
		err = lexemes.pos;
		std::cout << "\nОшибка! Ожидался символ ')'.\n" << " строка " << err.str_number
			<< "\ позиция" << err.position - elem.lexem.size() << "\n";
		return 0;
	}
	t.add_node_tree(elem.lex_plus_typ(), "BEGIN");
	elem = lexemes.parse(fin, table);
	if (elem.type != "LBRACE") {
		err = lexemes.pos;
		std::cout << "\nОшибка! Ожидался символ '{'.\n" << " строка " << err.str_number
			<< "\ позиция" << err.position - elem.lexem.size() << "\n";
		return 0;
	}
	t.add_node_tree(elem.lex_plus_typ(), "BEGIN");
	return 1;
}

bool synt_analysator::Descriptions(syntax_tree& t) {
	syntax_tree temp("DESCR");
	if (!Descr(temp))
		return 0;
	t.insert_sons(temp, "DESCRIPTIONS");
	temp.uborshica();
	while (true) {
		info elem = lexemes.parse(fin, table);
		if (elem.type != "INT") {
			lexemes.comeback_pos(fin, elem.lexem);
			return 1;
		}
		lexemes.comeback_pos(fin, elem.lexem);
		temp.set_root("DESCR");
		if (!Descr(temp))
			return 0;
		t.add_node_tree("DESCR", "DESCRIPTIONS");
		t.insert_tree(temp, "DESCR");
		temp.uborshica();
	}
	return 1;
}

bool synt_analysator::Descr(syntax_tree& t) {
	info elem = lexemes.parse(fin, table);
	if (elem.type != "INT") {
		err = lexemes.pos;
		std::cout << "\nОшибка! Ожидался тип переменной.\n" << " строка " << err.str_number
			<< "\ позиция" << err.position - elem.lexem.size() << "\n";
		return 0;
	}
	t.add_node_tree(elem.lex_plus_typ(), "DESCR");
	syntax_tree temp("VARLIST");
	if (!Varlist(temp))
		return 0;
	t.add_node_tree("VARLIST", "DESCR");
	t.insert_tree(temp, "VARLIST");
	temp.uborshica();
	elem = lexemes.parse(fin, table);
	if (elem.type != "END_SYMBOL") {
		err = lexemes.pos;
		std::cout << "\nОшибка! Ожидался символ ';'.\n" << " строка " << err.str_number
			<< "\ позиция" << err.position - elem.lexem.size() << "\n";
		return 0;
	}
	t.add_node_tree(elem.lex_plus_typ(), "DESCR");
	return 1;
}

bool synt_analysator::Varlist(syntax_tree& t) {
	info elem = lexemes.parse(fin, table);
	if (elem.type != "IDENTIF") {
		err = lexemes.pos;
		std::cout << "\nОшибка! Ожидалось название переменной.\n" << " строка " << err.str_number
			<< "\ позиция" << err.position - elem.lexem.size() << "\n";
		return 0;
	}
	t.add_node_tree(elem.lex_plus_typ(), "VARLIST");
	while (true) {
		elem = lexemes.parse(fin, table);
		if (elem.type != "COMMA") {
			lexemes.comeback_pos(fin, elem.lexem);
			return 1;
		}
		t.add_node_tree(elem.lex_plus_typ(), "VARLIST");
		if (!Varlist(t))
			return 0;
	}
	return 1;
}

bool synt_analysator::Operators(syntax_tree& t) {
	syntax_tree temp("OP");
	if (!Op(temp))
		return 0;
	t.insert_sons(temp, "OPERATORS");
	temp.uborshica();
	while (true) {
		info elem = lexemes.parse(fin, table);
		if (elem.type != "IDENTIF" && elem.type != "FOR") {
			lexemes.comeback_pos(fin, elem.lexem);
			return 1;
		}
		lexemes.comeback_pos(fin, elem.lexem);
		temp.set_root("OP");
		if (!Op(temp))
			return 0;
		t.add_node_tree("OP", "OPERATORS");
		t.insert_tree(temp, "OP");
		temp.uborshica();
	}
	return 1;
}

bool synt_analysator::Op(syntax_tree& t) {
	syntax_tree temp;
	info elem = lexemes.parse(fin, table);
	if (elem.type == "IDENTIF") {
		t.add_node_tree(elem.lex_plus_typ(), "OP");
		elem = lexemes.parse(fin, table);
		if (elem.type != "ASSIGN") {
			err = lexemes.pos;
			std::cout << "\nОшибка! Ожидался символ '='.\n" << " строка " << err.str_number
				<< "\ позиция" << err.position - elem.lexem.size() << "\n";
			return 0;
		}
		t.add_node_tree(elem.lex_plus_typ(), "OP");
		temp.uborshica();
		temp.set_root("EXPR");
		if (!Expr(temp))
			return 0;
		t.add_node_tree("EXPR", "OP");
		t.insert_tree(temp, "EXPR");
		temp.uborshica();
		elem = lexemes.parse(fin, table);
		if (elem.type != "END_SYMBOL") {
			err = lexemes.pos;
			std::cout << "\nОшибка! Ожидался символ ';'.\n" << " строка " << err.str_number
				<< "\ позиция" << err.position - elem.lexem.size() << "\n";
			return 0;
		}
		t.add_node_tree(elem.lex_plus_typ(), "OP");
	}
	else if (elem.type == "FOR") {
		t.add_node_tree(elem.lex_plus_typ(), "OP");
		elem = lexemes.parse(fin, table);
		if (elem.type != "LBRACKET") {
			err = lexemes.pos;
			std::cout << "\nОшибка! Ожидался символ '('.\n" << " строка " << err.str_number
				<< "\ позиция" << err.position - elem.lexem.size() << "\n";
			return 0;
		}
		t.add_node_tree(elem.lex_plus_typ(), "OP");
		elem = lexemes.parse(fin, table);
		if (elem.type != "IDENTIF") {
			err = lexemes.pos;
			std::cout << "\nОшибка! Ожидалось название переменной.\n" << " строка " << err.str_number
				<< "\ позиция" << err.position - elem.lexem.size() << "\n";
			return 0;
		}
		t.add_node_tree(elem.lex_plus_typ(), "OP");
		elem = lexemes.parse(fin, table);
		if (elem.type != "ASSIGN") {
			err = lexemes.pos;
			std::cout << "\nОшибка! Ожидался символ '='.\n" << " строка " << err.str_number
				<< "\ позиция" << err.position - elem.lexem.size() << "\n";
			return 0;
		}
		t.add_node_tree(elem.lex_plus_typ(), "OP");
		temp.uborshica();
		temp.set_root("EXPR");
		if (!Expr(temp))
			return 0;
		t.add_node_tree("EXPR", "OP");
		t.insert_tree(temp, "EXPR");
		elem = lexemes.parse(fin, table);
		if (elem.type != "END_SYMBOL") {
			err = lexemes.pos;
			std::cout << "\nОшибка! Ожидался символ ';'.\n" << " строка " << err.str_number
				<< "\ позиция" << err.position - elem.lexem.size() << "\n";
			return 0;
		}
		t.add_node_tree(elem.lex_plus_typ(), "OP");
		temp.uborshica();
		temp.set_root("CONDITION");
		if (!Condition(temp))
			return 0;
		t.add_node_tree("CONDITION", "OP");
		t.insert_tree(temp, "CONDITION");
		elem = lexemes.parse(fin, table);
		if (elem.type != "END_SYMBOL") {
			err = lexemes.pos;
			std::cout << "\nОшибка! Ожидался символ ';'.\n" << " строка " << err.str_number
				<< "\ позиция" << err.position - elem.lexem.size() << "\n";
			return 0;
		}
		t.add_node_tree(elem.lex_plus_typ(), "OP");
		temp.uborshica();
		temp.set_root("EXPR");
		if (!Expr(temp))
			return 0;
		t.add_node_tree("EXPR", "OP");
		t.insert_tree(temp, "EXPR");
		elem = lexemes.parse(fin, table);
		if (elem.type != "RBRACKET") {
			err = lexemes.pos;
			std::cout << "\nОшибка! Ожидался символ ')'.\n" << " строка " << err.str_number
				<< "\ позиция" << err.position - elem.lexem.size() << "\n";
			return 0;
		}
		t.add_node_tree(elem.lex_plus_typ(), "OP");
		elem = lexemes.parse(fin, table);
		if (elem.type != "LBRACE") {
			err = lexemes.pos;
			std::cout << "\nОшибка! Ожидался символ '{'.\n" << " строка " << err.str_number
				<< "\ позиция" << err.position - elem.lexem.size() << "\n";
			return 0;
		}
		t.add_node_tree(elem.lex_plus_typ(), "OP");
		temp.uborshica();
		temp.set_root("OPERATORS");
		if (!Operators(temp))
			return 0;
		t.add_node_tree("OPERATORS", "OP");
		t.insert_tree(temp, "OPERATORS");
		elem = lexemes.parse(fin, table);
		if (elem.type != "RBRACE") {
			err = lexemes.pos;
			std::cout << "\nОшибка! Ожидался символ '}'.\n" << " строка " << err.str_number
				<< "\ позиция" << err.position - elem.lexem.size() << "\n";
			return 0;
		}
		t.add_node_tree(elem.lex_plus_typ(), "OP");
	}
	else {
		err = lexemes.pos;
		std::cout << "\nОшибка! Ожидался оператор.\n" << " строка " << err.str_number
			<< "\ позиция" << err.position - elem.lexem.size() << "\n";
		return 0;
	}
	return 1;
}

bool synt_analysator::Condition(syntax_tree& t) {
	syntax_tree temp;
	temp.uborshica();
	temp.set_root("EXPR");
	if (!Expr(temp))
		return 0;
	t.insert_sons(temp, "CONDITION");
	info elem = lexemes.parse(fin, table);
	if (elem.type != "EQUAL" && elem.type != "NON_EQUAL" && elem.type != "LESS_OR_EQUAL" &&
		elem.type != "GREATER_OR_EQUAL" && elem.type != "GREATER" && elem.type != "LESS") {
		err = lexemes.pos;
		std::cout << "\nОшибка! Ожидалась операция сравнения.\n" << " строка " << err.str_number
			<< "\ позиция" << err.position - elem.lexem.size() << "\n";
		return 0;
	}
	t.add_node_tree(elem.lex_plus_typ(), "CONDITION");
	temp.uborshica();
	temp.set_root("EXPR");
	if (!Expr(temp))
		return 0;
	t.add_node_tree("EXPR", "CONDITION");
	t.insert_tree(temp, "EXPR");
	return 1;
}

bool synt_analysator::Expr(syntax_tree& t) {
	syntax_tree temp;
	temp.uborshica();
	temp.set_root("SIMPLE_EXPR");
	if (!S1mpleExpr(temp))
		return 0;
	t.add_node_tree("SIMPLE_EXPR", "EXPR");
	t.insert_tree(temp, "SIMPLE_EXPR");
	info elem = lexemes.parse(fin, table);
	if (elem.type != "PLUS" && elem.type != "MINUS") {
		lexemes.comeback_pos(fin, elem.lexem);
		return 1;
	}
	t.add_node_tree(elem.lex_plus_typ(), "EXPR");
	if (!Expr(t))
		return 0;
	return 1;
}

bool synt_analysator::S1mpleExpr(syntax_tree& t) {
	info elem = lexemes.parse(fin, table);
	syntax_tree temp;
	if (elem.type == "LBRACKET") {
		t.add_node_tree(elem.lex_plus_typ(), "SIMPLE_EXPR");
		temp.uborshica();
		temp.set_root("EXPR");
		if (!Expr(temp))
			return 0;
		t.add_node_tree("EXPR", "SIMPLE_EXPR");
		t.insert_tree(temp, "EXPR");
		elem = lexemes.parse(fin, table);
		if (elem.type != "RBRACKET") {
			err = lexemes.pos;
			std::cout << "\nОшибка! Ожидался символ ')'.\n" << " строка " << err.str_number
				<< "\ позиция" << err.position - elem.lexem.size() << "\n";
			return 0;
		}
	}
	else if (elem.type != "IDENTIF" && elem.type != "NUMBER") {
		err = lexemes.pos;
		std::cout << "\nОшибка! Ожидалось название переменной или число.\n" << " строка " << err.str_number
			<< "\ позиция" << err.position - elem.lexem.size() << "\n";
		return 0;
	}
	t.add_node_tree(elem.lex_plus_typ(), "SIMPLE_EXPR");
	return 1;
}

bool synt_analysator::End(syntax_tree& t) {
	info elem = lexemes.parse(fin, table);
	if (elem.type != "RETURN") {
		err = lexemes.pos;
		std::cout << "\nОшибка! Ожидался return.\n" << " строка " << err.str_number
			<< "\ позиция" << err.position - elem.lexem.size() << "\n";
		return 0;
	}
	t.add_node_tree(elem.lex_plus_typ(), "END");
	elem = lexemes.parse(fin, table);
	if (elem.type != "IDENTIF") {
		err = lexemes.pos;
		std::cout << "\nОшибка! Ожидалось название переменной.\n" << " строка " << err.str_number
			<< "\ позиция" << err.position - elem.lexem.size() << "\n";
		return 0;
	}
	t.add_node_tree(elem.lex_plus_typ(), "END");
	elem = lexemes.parse(fin, table);
	if (elem.type != "END_SYMBOL") {
		err = lexemes.pos;
		std::cout << "\nОшибка! Ожидался символ ';'.\n" << " строка " << err.str_number
			<< "\ позиция" << err.position - elem.lexem.size() << "\n";
		return 0;
	}
	t.add_node_tree(elem.lex_plus_typ(), "END");
	elem = lexemes.parse(fin, table);
	if (elem.type != "RBRACE") {
		err = lexemes.pos;
		std::cout << "\nОшибка! Ожидался символ '}'.\n" << " строка " << err.str_number
			<< "\ позиция" << err.position - elem.lexem.size() << "\n";
		return 0;
	}
	t.add_node_tree(elem.lex_plus_typ(), "END");
	return 1;
}

bool synt_analysator::analys(syntax_tree& t) {
	return Function(t);
}
