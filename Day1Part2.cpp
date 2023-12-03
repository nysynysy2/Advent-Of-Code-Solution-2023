#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>
using namespace std;
int main() {
	unordered_map<string, size_t> num_vec{ {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six",6}, {"seven",7}, {"eight",8}, {"nine",9} };
	ifstream file{"input.txt"};
	if (!file)return 1;
	size_t sum{};
	string buffer{};
	while (file >> buffer) {
		size_t shi{}, ge{}, num{};
		vector < pair<size_t, string> > poses{};
		for (const auto& [str, num] : num_vec) {
			size_t pos{};
			while (1) {
				pos = buffer.find(str, pos);
				if (pos == string::npos) {
					break;
				}
				poses.emplace_back(pos, str);
				pos++;
			}
		}
		if (!poses.empty()) {
			sort(poses.begin(), poses.end(), [](const auto& a, const auto& b) {return a.first < b.first; });
			buffer.replace((*poses.begin()).first,(*poses.begin()).second.size(), to_string(num_vec[(*poses.begin()).second]));
			poses.erase(poses.begin());
			if (!poses.empty()) {
				auto str = (*poses.rbegin()).second;
				auto last_pos = buffer.rfind(str);
				if (last_pos != string::npos) {
					buffer.replace(last_pos,str.size(), to_string(num_vec[str]));
				}
			}
		}
		for (size_t idx = 0 ; idx != buffer.size();idx++) {
			if (isdigit(buffer[idx])) {
				shi = buffer[idx] - '0';
				break;
			}
		}
		for (size_t idx = buffer.size() - 1; idx != numeric_limits<size_t>::max(); idx--) {
			if (isdigit(buffer[idx])) {
				ge = buffer[idx] - '0';
				break;
			}
		}
		num = 10 * shi + ge;
		std::cout << shi << " " << ge << " " << num << endl;
		sum += num;
	}
	std::cout << sum;
}
