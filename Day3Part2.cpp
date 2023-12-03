#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <print>
using namespace std;
struct Pos {
	size_t line{};
	size_t pos{};
};
struct Number {
	size_t num{};
	size_t len{};
	Pos pos{};
};
struct Aster {
	Pos pos{};
	vector<size_t> nums_adj{};
};

size_t udiff(size_t num1, size_t num2) {
	return num1 > num2 ? num1 - num2 : num2 - num1;
}
void num_is_adj(Number& num, Aster& aster) {
	if (udiff(num.pos.line, aster.pos.line) <= 1) {
		for (size_t i = num.pos.pos; i < num.pos.pos + num.len; ++i) {
			if (udiff(i, aster.pos.pos) <= 1) {
				aster.nums_adj.push_back(num.num);
				return;
			}
		}
	}
}

int main() {
	vector<Number> num_pos{};
	vector<Aster> asters{};
	ifstream file{ "input.txt" };
	string line_buf{};
	size_t sum{};
	for (size_t line_idx{}; getline(file, line_buf); ++line_idx) {
		size_t aster_pos{ 0 };
		while ((aster_pos = line_buf.find('*', aster_pos)) != string::npos) {
			asters.push_back({ {line_idx, aster_pos} });
			aster_pos++;
		}
		for (size_t read{}; read < line_buf.size(); ++read) {
			if (isdigit(line_buf[read])) {
				size_t pos = read;
				size_t num{};
				while (read < line_buf.size() && isdigit(line_buf[read])) {
					num = num * 10 + (line_buf[read] - '0');
					read++;
				}
				num_pos.push_back({ num, read - pos, { line_idx, pos } });
			}
		}
	}
	for (auto& num : num_pos) {
		for (auto& ast : asters) {
			num_is_adj(num, ast);
		}
	}
	for (auto& ast : asters) {
		if (ast.nums_adj.size() == 2) {
			sum += ast.nums_adj[0] * ast.nums_adj[1];
		}
	}
	cout << sum;
}
