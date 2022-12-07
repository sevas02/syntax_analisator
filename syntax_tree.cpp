#include "syntax_tree.h"

//проверка на терминал
bool is_terminal(std::string str) {
	for (auto& symb : str)
		if (symb == ' ')
			return 0;
	return 1;
}

void syntax_tree::add_node_tree(std::string data, std::string vin_disel, node &uzel) {
	if (uzel->get_field() == vin_disel)
		uzel->prinyatie_v_semju(data, uzel);
	else
		for (size_t i = 0; i < uzel->get_childs().size(); i++) {
			add_node_tree(data, vin_disel, uzel->get_childs()[i]);
		}
}

void syntax_tree::copy(node& from, node& to) {
	to = std::make_shared<node_tree>(*from);
	for (size_t i = 0; i < from->get_childs().size(); i++)
		copy(from->get_childs()[i], to->get_childs()[i]);
}

void syntax_tree::insert_tree(syntax_tree& t, std::string add, node& cur_pos) {
	if (!cur_pos) return;
	if (is_terminal(cur_pos->get_field()) && cur_pos->get_childs().size() == 0) {
		if (cur_pos->get_field() == add) {
			cur_pos = nullptr;
			copy(t.root, cur_pos);
			return;
		}
	}
	for (auto& elem : cur_pos->get_childs())
		insert_tree(t, add, elem);
}

void syntax_tree::insert_sons(syntax_tree& t, std::string add, node& cur_pos) {
	if (!cur_pos) return;
	if (is_terminal(cur_pos->get_field()) && cur_pos->get_childs().size() == 0) {
		if (cur_pos->get_field() == add) {
			cur_pos->get_childs().push_back(std::make_shared<node_tree>());
			copy(t.root, *cur_pos->get_childs().begin());
			return;
		}
	}
	for (auto& elem : cur_pos->get_childs())
		insert_sons(t, add, elem);
}

void syntax_tree::print(std::ofstream& fout, node uzel, int space) {
	for (int i = 0; i < space; i++)
		fout << '\t';
	fout << uzel->get_field() << '\n';
	for (auto& elem : uzel->get_childs())
		print(fout, elem, space + 1);
}




