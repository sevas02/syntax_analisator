#include "dka.h"

dka::dka() {
	state q0("NOT_DEFINED", false, 1, 2);
	vec.push_back(q0);
	state q1("IDENTIF", true, 1, 3);
	vec.push_back(q1);
	state q2("NUMBER", true, 3, 2);
	vec.push_back(q2);
	state q3("NOT_DEFINED", false, 3, 3);
	vec.push_back(q3);
}

std::string dka::checker(std::string str) {
	int idx = 0;
	//идем по автомату
	for (auto elem : str) {
		idx = vec[idx].get_next(elem);
		if (idx == -1)
			return "NOT_DEFINED";
	}
	return vec[idx].get_type();
}