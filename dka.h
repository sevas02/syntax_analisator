#ifndef DKA_H
#define DKA_H
#include "data.h"
#include <string>
#include <vector>

//��������� ��������
class state {
private:
	//����� ��� �����
	std::string type;
	//�������� ��� ���
	bool status;
	//���� ���� 0 - �����; 1 - ����� 
	int next_state[2];

public:
	state(std::string typ, bool stat, int idx1, int idx2) {
		this->type = typ;
		this->status = stat;
		this->next_state[0] = idx1;
		this->next_state[1] = idx2;
	}

	int get_next (char symb) {
		if (isdigit(symb))
			return next_state[1];
		if (((int)symb >= 65 && (int)symb <= 90) ||
			((int)symb >= 97 && (int)symb <= 122))
			return next_state[0];
		else
			return -1;
	}

	bool get_status() { return status; }
	std::string get_type() { return type; }
};

class dka {
private:
	std::vector<state> vec;
public:
	dka();
	std::string checker(std::string str);
};


#endif
