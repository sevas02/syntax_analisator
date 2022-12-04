#include "lex_analys.h"
#include "hash_table.h"
#include "data.h"
#include "dka.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

//обновление ошибки
void pos_error::update_pos(char symb) {
	position++;
	if (symb == '\n') {
		str_number++;
		position = 1;
	}
}

//функция считывания следующего лексемы по тексту
std::string lex_analysator::next_word(std::ifstream& fin) {
	std::string str = "";
	while (true) {
		char symb = fin.get();
		if (fin.eof())
			break;
		pos.update_pos(symb);
		if (is_space(symb) || symb == '\n')
			if (!str.empty()) {
				pos.position--;
				fin.unget();
				return str;
			}
			else
				continue;
		if (is_brace(symb) || is_bracket(symb) || is_compare(symb, fin.peek())
			|| is_operation(symb) || symb == comma || symb == str_end) {
			fin.unget();
			pos.position--;
			return str;
		}
		str += symb;
	}
	return str;
}

//функция возврата лексемы в поток
void lex_analysator::comeback_pos(std::ifstream& fin, std::string word) {
	std::reverse(word.begin(), word.end());
	for (auto symb : word) {
		fin.putback(symb);
		pos.position--;
	}
	if (pos.position == 0)
		pos.str_number--;
}

int lex_analysator::is_compare(char curr, char next) {
	if (curr == '=' && next == '=')
		return 1;
	if (curr == '!' && next == '=')
		return 2;
	if (curr == '<' && (next == ' ' || next == '\n'))
		return 3;
	if (curr == '<' && next == '=')
		return 4;
	if (curr == '>' && (next == ' ' || next == '\n'))
		return 5;
	if (curr == '>' && (next == '='))
		return 6;
	return 0;
}
bool lex_analysator::is_bracket(char elem) {
	return (std::find(brackets.begin(), brackets.end(), elem)
		!= brackets.end());
}
bool lex_analysator::is_brace(char elem) {
	return (std::find(braces.begin(), braces.end(), elem)
		!= braces.end());
}
bool lex_analysator::is_operation(char elem) {
	return (std::find(operations.begin(), operations.end(), elem)
		!= operations.end());
}
bool lex_analysator::is_service(std::string elem) {
	return (std::find(service_words.begin(), service_words.end(), elem)
		!= service_words.end());
}
bool lex_analysator::is_space(char elem) {
	return (std::find(space.begin(), space.end(), elem)
		!= space.end());
}

//проведение лексического анализа
info lex_analysator::parse(std::ifstream& fin, hash_table& tab) {
	std::string str = next_word(fin);
	if (str == "") {
		char symb = fin.get();
		pos.update_pos(symb);
		char next_symb = fin.peek();
		str += symb;
		if (is_compare(symb, next_symb)) {
			if (next_symb != ' ' && next_symb != '\n') {
				next_symb = fin.get();
				str += next_symb;
				if (is_compare(symb, next_symb) == 1) {
					info el(str, "EQUAL");
					str = "";
					tab.insert(el);
					return el;
				}
				else if (is_compare(symb, next_symb) == 2) {
					info el(str, "NON_EQUAL");
					str = "";
					tab.insert(el);
					return el;
				}
				else if (is_compare(symb, next_symb) == 4) {
					info el(str, "LESS_OR_EQUAL");
					str = "";
					tab.insert(el);
					return el;
				}
				else if (is_compare(symb, next_symb) == 6) {
					info el(str, "GREATER_OR_EQUAL");
					str = "";
					tab.insert(el);
					return el;
				}
			}
			else if (is_compare(symb, next_symb) == 3) {
				info el(str, "LESS");
				str = "";
				tab.insert(el);
				return el;
			}
			else if (is_compare(symb, next_symb) == 5) {
				info el(str, "GREATER");
				str = "";
				tab.insert(el);
				return el;
			}
		}
		else if (is_space(symb) || symb == str_end || is_bracket(symb) || is_operation(symb) || is_brace(symb) || symb == comma) {
			if (is_bracket(symb)) {
				if (symb == brackets[0]) {
					info el(str, "LBRACKET");
					tab.insert(el);
					str = "";
					return el;
				}
				info el(str, "RBRACKET");
				tab.insert(el);
				str = "";
				return el;
			}
			else if (is_brace(symb)) {
				if (symb == braces[0]) {
					info el(str, "LBRACE");
					tab.insert(el);
					str = "";
					return el;
				}
				info el(str, "RBRACE");
				tab.insert(el);
				str = "";
				return el;
			}
			else if (is_operation(symb)) {
				if (symb == operations[0]) {
					info el(str, "ASSIGN");
					str = "";
					tab.insert(el);
					return el;
				}
				else if (symb == operations[1]) {
					info el(str, "PLUS");
					str = "";
					tab.insert(el);
					return el;
				}
				else if (symb == operations[2]) {
					info el(str, "MINUS");
					str = "";
					tab.insert(el);
					return el;
				}
			}
			else if (symb == str_end) {
				info el(str, "END_SYMBOL");
				str = "";
				tab.insert(el);
				return el;
			}
			else if (symb == comma) {
				info el(str, "COMMA");
				str = "";
				tab.insert(el);
				return el;
			}
		}
	}
	else if (is_service(str)) {
		if (str == service_words[0]) {
			info el(str, "RETURN");
			str = "";
			tab.insert(el);
			return el;
		}
		else if (str == service_words[1]) {
			info el(str, "INT");
			str = "";
			tab.insert(el);
			return el;
		}
		else if (str == service_words[2]) {
			info el(str, "FOR");
			str = "";
			tab.insert(el);
			return el;
		}
	}
	else {
		std::string type = automat.checker(str);
		info el(str, type);
		str = "";
		tab.insert(el);
		return el;
	}
	return info("", "NOT_DEFINED");
}

