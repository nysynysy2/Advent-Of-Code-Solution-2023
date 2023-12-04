#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <print>
#include <algorithm>
using namespace std;
struct Card {
	size_t id{};
	bool scratched{};
	size_t winning_amount{};
};
int main() {
	ifstream file{ "input.txt" };
	regex card_regex{"Card[ ]*(\\d+):(.*)[|](.*)"};
	smatch card_res{};
	string line_buf{};
	vector<Card> cards{};
	while(getline(file, line_buf)){
		Card c{};
		vector<size_t> winning{};
		vector<size_t> mine{};
		regex_match(line_buf, card_res, card_regex);
		c.id = stoull(card_res[1]);
		stringstream swin{ card_res[2].str() }, smine{ card_res[3].str() };
		size_t num_buf{};
		while (swin >> num_buf) {
			winning.push_back(num_buf);
		}
		while (smine >> num_buf) {
			mine.push_back(num_buf);
		}
		for (int i = 0; i < winning.size(); ++i) {
			if (find(mine.begin(), mine.end(), winning[i]) != mine.end()) {
				c.winning_amount++;
			}
		}
		cards.push_back(c);
	}
	for (size_t i{}; i < cards.size(); ++i) {
		if (!cards[i].scratched) {
			size_t amount = cards[i].winning_amount;
			cards[i].scratched = true;
			for (size_t jidx = cards[i].id; jidx < cards[i].id + amount; ++jidx) {
				Card new_card = cards[jidx];
				new_card.scratched = false;
				cards.push_back(new_card);
			}
		}
	}
	cout << cards.size();
}
