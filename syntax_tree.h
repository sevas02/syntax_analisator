#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H
#include <string>
#include "data.h"
#include <vector>
#include <fstream>

class node_tree {
private:
	//поле узла (токен)
	std::string field;
	//вектор сыновей
	std::vector<std::shared_ptr<node_tree>> net_nichego_vajnee_semji;
public:
	//конструкторы
	node_tree() : field(""), net_nichego_vajnee_semji(std::vector<std::shared_ptr<node_tree>>()) {};
	node_tree(std::string str) : field(str), net_nichego_vajnee_semji(std::vector<std::shared_ptr<node_tree>>(0)) {};
	node_tree(const node_tree& obj) {
		this->field = obj.field;
		this->net_nichego_vajnee_semji = obj.net_nichego_vajnee_semji;
	}

	//геттеры
	std::string get_field() { return field; }
	std::vector<std::shared_ptr<node_tree>>& get_childs() { return net_nichego_vajnee_semji; }

	//сеттеры
	void set_field(std::string str) { field = str; }
	void prinyatie_v_semju(std::string str, std::shared_ptr<node_tree> &elem) {
		node_tree temp(str);
		auto pointer = &elem->net_nichego_vajnee_semji;
		pointer->push_back(std::make_shared<node_tree>(temp));
	}
};

using node = std::shared_ptr<node_tree>;

class syntax_tree {
private:
	//корень
	node root;
	//добавление узла к дереву
	void add_node_tree(std::string, std::string, node&);
	//вставка поддерева в дерево
	void insert_tree(syntax_tree& t, std::string ins_pos, node& cur_pos);
	//вставка сыновей в дерево
	void insert_sons(syntax_tree& t, std::string ins_pos, node& cur_pos);
	//печать дерева
	void print(std::ofstream& fout, node, int);
public:
	//конструкторы
	syntax_tree() { root = std::make_shared<node_tree>(node_tree("FUNCTION")); }
	syntax_tree(std::string str) { root = std::make_shared<node_tree>(node_tree(str)); }
	syntax_tree(syntax_tree& obj) { copy(obj.root, root); }

	//сеттер
	void set_root(std::string str) {
		root->set_field(str);
	}

	void add_node_tree(std::string data, std::string vin_disel) {
		add_node_tree(data, vin_disel, root);
	}
	void print(std::ofstream& fout) {
		print(fout, root, 0);
	}

	//вставка поддерева в дерево
	void insert_tree(syntax_tree& t, std::string ins_pos) { insert_tree(t, ins_pos, root); };
	//вставка сыновей в дерево
	void insert_sons(syntax_tree& t, std::string ins_pos) { insert_sons(t, ins_pos, root); };
	//копирование
	void copy(node& from, node& to);
	//чистилка
	void uborshica() { root->get_childs().clear(); }
};

#endif // !SYNTAX_TREE_H
