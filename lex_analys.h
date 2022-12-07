#ifndef LEX_ANALYS_H
#define LEX_ANALYS_H
#include "dka.h"
#include "hash_table.h"
#include "data.h"
#include <string>
#include <vector>
#include <fstream>

//позиция, на которой произошла ошибка
class pos_error {
public:
	//номер строчки
	int str_number;
	//позиция в строчке
	int position;
	//конструктор
	pos_error() : str_number(1), position(1) {};
	//обновление позиции
	void update_pos(char symbs);
};

//лексичексий анализатор
class lex_analysator { 
private:
	//поля для определения принадлежности считанного объекта
	std::vector<std::string> service_words = { "return", "int", "for" };
	std::vector<char> operations = { '=', '+', '-' };
	std::vector<char> brackets = { '(', ')' };
	std::vector<char> braces = { '{', '}' };
	std::vector<char> space = { ' ', '\t' };
	char comma = ',';
	char str_end = ';';
	dka automat;
	int is_compare(char curr, char next);
	bool is_bracket(char elem);
	bool is_brace(char elem);
	bool is_operation(char elem);
	bool is_service(std::string elem);
	bool is_space(char elem);
	//функция считывания следующего лексемы по тексту
	std::string next_word(std::ifstream& fin);
public:
	//функция разбора строки
	info parse(std::ifstream& fin, hash_table& tab);
	//функция возврата лексемы в поток
	void comeback_pos(std::ifstream& fin, std::string word);
	//позиция в файле
	pos_error pos;
};


#endif 