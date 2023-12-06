#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <vector>
using namespace std;
int main() {
	//Input Modified!!!
	size_t product{ 1 };
	size_t time{};
	size_t record{};
	ifstream file{ "input.txt" };
	string line_buf{};
	getline(file, line_buf);
	stringstream time_stream{line_buf};
	size_t number_buf{};
	string time_buf{};
	string record_buf{};
	while (time_stream >> number_buf) {
		time_buf += to_string(number_buf);
	}

	getline(file, line_buf);
	stringstream record_stream{ line_buf };

	while (record_stream >> number_buf) {
		record_buf += to_string(number_buf);
	}
	
	time = stoull(time_buf);
	record = stoull(record_buf);

		size_t ways{};
		for (size_t hold{ 1 };hold < time; ++hold) {
			size_t speed = hold;
			size_t distance = speed * (time - hold);
			if (distance > record)ways++;
		}
	cout << ways << endl;
}
