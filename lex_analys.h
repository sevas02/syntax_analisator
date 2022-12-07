#ifndef LEX_ANALYS_H
#define LEX_ANALYS_H
#include "dka.h"
#include "hash_table.h"
#include "data.h"
#include <string>
#include <vector>
#include <fstream>

//�������, �� ������� ��������� ������
class pos_error {
public:
	//����� �������
	int str_number;
	//������� � �������
	int position;
	//�����������
	pos_error() : str_number(1), position(1) {};
	//���������� �������
	void update_pos(char symbs);
};

//����������� ����������
class lex_analysator { 
private:
	//���� ��� ����������� �������������� ���������� �������
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
	//������� ���������� ���������� ������� �� ������
	std::string next_word(std::ifstream& fin);
public:
	//������� ������� ������
	info parse(std::ifstream& fin, hash_table& tab);
	//������� �������� ������� � �����
	void comeback_pos(std::ifstream& fin, std::string word);
	//������� � �����
	pos_error pos;
};


#endif 