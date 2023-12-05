#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <regex>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include <atomic>
using namespace std;
static mutex lowest_lock{};
static size_t lowest_location{ static_cast<size_t>(-1) };
static atomic<size_t> seed_left{};
size_t udiff(size_t a, size_t b) {
	return a > b ? a - b : b - a;
}
struct maprange {

	size_t des_start{};
	size_t src_start{};
	size_t range{};
};
struct mapper {
	vector<maprange> v{};
	size_t get_corr(size_t src) {
		for (size_t i = v.size() - 1; i != numeric_limits<size_t>::max();--i) {
			auto& r = v[i];
			if (src < r.src_start || src >= r.src_start + r.range)continue;
			else return r.des_start > r.src_start ? src + udiff(r.des_start, r.src_start) : src - udiff(r.des_start, r.src_start);
		}
		return src;
	}
};
struct seed_range {
	size_t start{};
	size_t range{};
};
enum MI {
	seed_to_soil = 0, soil_to_f = 1, f_to_water = 2, water_to_light=3, light_to_t=4, t_to_h=5, h_to_l=6
};

void func(seed_range seed_num, mapper* maps) {
	seed_range tmp = seed_num;
	size_t thread_local_low{ static_cast<size_t>(-1) };
	if (tmp.start + tmp.range < tmp.start) {
		std::cout << "FUCK!!!" << endl;
	}
	for (size_t s = tmp.start; s < tmp.start + tmp.range; ++s) {
		size_t inum = s;
		for (size_t im{}; im < 7; ++im) {
			inum = maps[im].get_corr(inum);
		}

		thread_local_low = inum < thread_local_low ? inum : thread_local_low;
	}
	lowest_lock.lock();
	lowest_location = thread_local_low < lowest_location ? thread_local_low : lowest_location;
	lowest_lock.unlock();
	seed_left--;
	std::cout << seed_left << " Seed:" << seed_num.start << " OUT" << endl;
}
int main() {
	vector<seed_range> seeds{};
	mapper maps[7];
	fstream file{"input.txt"};
	string line_buf{};
	regex seed_regex{"seeds:(.*)"};
	smatch seed_res{};
	getline(file, line_buf);
	regex_match(line_buf, seed_res, seed_regex);
	stringstream seeds_stream{seed_res[1]};
	size_t seed_buf{};
	while (seeds_stream >> seed_buf) {
		seed_range sr{ seed_buf };
		seeds_stream >> seed_buf;
		sr.range = seed_buf;
		seeds.push_back(sr);
		seed_left++;
	}
	getline(file, line_buf);//empty line
	for (size_t mapidx = 0; getline(file, line_buf);++mapidx) {
		mapper m{};
		size_t src_start{}, des_start{}, range{};
		
		while (getline(file, line_buf) && !line_buf.empty()) {
			stringstream line_stream{ line_buf };
			line_stream >> des_start >> src_start >> range;
			m.v.push_back({ des_start , src_start , range });

		}
		maps[mapidx] = m;
	}
	vector<jthread> threads{};
	for (const auto& seed_num : seeds) {
		threads.emplace_back(func, seed_num, maps);
	}
	while (seed_left != 0);
	::cout << lowest_location;
}
