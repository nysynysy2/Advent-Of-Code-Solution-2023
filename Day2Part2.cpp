#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
using namespace std;

int main() {

	ifstream file{ "input.txt" };
	string buffer{};
	
	int sum{};

	while (getline(file, buffer)) {
		size_t power{ 1 };
		unordered_map<string, size_t> min_num{ {"red", 1}, {"green", 1}, {"blue", 1}};
		smatch game_res{};
		regex game_regex{ "Game ([0-9]+):(.*)" };
		regex color_regex{ " ([0-9]+) (blue|red|green)" };
		
		regex_match(buffer,game_res,game_regex);

		stringstream semicolonstream{ game_res[2] };
		string semicolonbuf{};
		while (getline(semicolonstream, semicolonbuf, ';')) {
			stringstream commastream{ semicolonbuf };
			string commabuf{};
			while (getline(commastream, commabuf, ',')) {
				smatch color_res{};
				regex_match(commabuf, color_res,  color_regex);
				size_t new_num = stoull(color_res[1].str());
				if (min_num[color_res[2].str()] < new_num) {
					min_num[color_res[2].str()] = new_num;
				}
			}
		}
		for (auto& [_, num] : min_num) {
			power *= num;
		}
		sum += power;
	}
	cout << sum;
}
