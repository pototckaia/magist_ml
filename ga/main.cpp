#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <map>
#include <random>
#include <set>
#include <string>
#include <climits>
#include <windows.h>
#include <ppl.h>

using namespace concurrency;
using namespace std;

const int MAX_STEP = 10000;
const int POP_SIZE = 5000; // чем больше тем дальше деградация
const int SEL_SIZE = 400;
const int MIN_MUTATIONS_NUMBER = 400;
const int MAX_MUTATIONS_NUMBER = 700;
const int MAX_PERSONAL_MUTATIONS_NUMBER = 300;
const int K_POINT = 200;
const bool USE_LAST_POPULATION = true;
// 571
// 607

int n, m;
vector<int> complex;
vector<double> times;
vector<vector<double>> coeff;

// i - номер разработчика, назначенного на i - ю задачу. 
int epoch = 0;
double bestTime;
vector<int> bestMember;

vector<vector<int>> population;
vector<vector<int>> new_population;

vector<double> fitnessCash;

mt19937 gen(time(0));

void single_point_crossover(vector<int>& a, vector<int>& b, int point) {
	for (int i = point + 1; i < int(a.size()); ++i) {
		swap(a[i], b[i]);
	}
}

void two_point_crossover(vector<int>& a, vector<int>& b, int first, int second) {	
	single_point_crossover(a, b, first);
	single_point_crossover(a, b, second);
}

void k_point_crossover(vector<int>& a, vector<int>& b, vector<int>& points) {
	for (auto& p: points) {
		single_point_crossover(a, b, p);
	}
}
	
void init() {
	population.clear();
	fitnessCash.resize(POP_SIZE, 0);
	epoch = 0;
	bestTime = 100000000;
	bestMember.resize(n, 0);
	new_population.resize(POP_SIZE, vector<int>(n));
	
	if (USE_LAST_POPULATION) {
		ifstream in("last_population.txt");
		for (int i = 0; i < POP_SIZE; ++i) {
			population.push_back(vector<int>(n));
			for (int j =0; j < n; ++j) {
				in >> population[i][j];
			}
		}
		in.close();
		return;
	}
	
	std::uniform_int_distribution<int> dist(1,m);
	for (int i = 0; i < POP_SIZE; ++i) {
		// [1, m]
		population.push_back(vector<int>(n));
		for (int j = 0; j < n; ++j) {
			population[i][j] = dist(gen);
		}
	}
}

double fitness(vector<int>& population_member) {
	double t = INT_MIN;
	for (int i = 0; i < m; ++i) {
		auto iter = std::find(population_member.begin(), population_member.end(), i + 1);
		if (iter != population_member.end()) {
			double t_acc = 0;
			for (int j = 0; j < n; ++j) {
				if (i + 1 == population_member[j]) {
					t_acc += times[j] * coeff[i][complex[j] - 1];
				}
			}
			t = max(t_acc, t);
		}
	}
	return t;
}

vector<int> randomArray(const int size, const int a, const int b, bool uniq = true) {
	vector<int> ar;
	set<int> dig;
	uniform_int_distribution<int> dist(a,b);
	while (int(ar.size()) <= size) {
		auto d = dist(gen);
		if (!uniq || (uniq && dig.count(d) == 0)) {
			dig.insert(d);
			ar.push_back(d);
		}
	}
	return ar;
}

pair<int, int> selection() {
	// random array replace false [0, min(sel_size, pop_size)]
	auto candidate = randomArray(SEL_SIZE, 0, POP_SIZE - 1);
	sort(candidate.begin(), candidate.end(), [&](auto& a, auto& b)
	{
		return fitnessCash[a] < fitnessCash[b];
	});
	return make_pair(candidate[0], candidate[1]);
}

void crossover(vector<int>& a, vector<int>& b) {
	uniform_int_distribution<int> dist(0, int(a.size()) - 1);

	if (K_POINT == 1) {
		int point = dist(gen);
		single_point_crossover(a, b, point);
		// point mutation late
	}
	else if (K_POINT == 2) {
		int first = dist(gen) / 2;
		int second = first + dist(gen) / 2;
		two_point_crossover(a, b, first, second);
	}
	else {
		auto point = randomArray(K_POINT, 0, int(a.size()) - 1);
		sort(point.begin(), point.end());
		k_point_crossover(a, b, point);
	}
}

void mutation(vector<int>& a) {
	auto in = randomArray(MAX_PERSONAL_MUTATIONS_NUMBER, 0, int(a.size()) - 1);
	auto mu = randomArray(MAX_PERSONAL_MUTATIONS_NUMBER, 1, coeff.size(), false);
	for (int i = 0; i < int(in.size()); ++i) {
		a[in[i]] = mu[i];
	}
}

void step() {
	++epoch;
	parallel_for(0, POP_SIZE, [](int i)
	{
			fitnessCash[i] = fitness(population[i]);
	});
	/*for (int i = 0; i < POP_SIZE; ++i) {
		fitnessCash[i] = fitness(population[i]);
	}*/

	auto min_pos = std::distance(fitnessCash.begin(), std::min_element( fitnessCash.begin(), fitnessCash.end()));
	if (fitnessCash[min_pos] < bestTime)
	{
		bestTime = fitnessCash[min_pos];
		bestMember = population[min_pos];
	}

	cout << "Epoch: " << epoch << '\t'
	<< "best_time=" << bestTime << '\t'
	<< "local_time=" << fitnessCash[min_pos] << endl;

	parallel_for(0, POP_SIZE / 2, [](int i){
			auto cand = selection();
			new_population[2 * i] = population[cand.first];
			new_population[2 * i + 1] = population[cand.second];
			crossover(new_population[2 * i], new_population[2 * i + 1]);
		});
	//for (int i = 0; i < POP_SIZE / 2; ++i)
	//{
	//	auto cand = selection();
	//	new_population[2 * i] = population[cand.first];
	//	new_population[2 * i + 1] = population[cand.second];
	//	crossover(new_population[2 * i], new_population[2 * i + 1]);
	//}

	std::shuffle(new_population.begin(), new_population.end(), gen);
	
	uniform_int_distribution<int> dis(MIN_MUTATIONS_NUMBER, MAX_MUTATIONS_NUMBER);
	
	auto mutationMember = randomArray(dis(gen), 0, POP_SIZE - 1);
	if (!mutationMember.empty()) {
		parallel_for_each(mutationMember.begin(), mutationMember.end(), [](int i) {
			mutation(new_population[i]);
		});
		/*for (auto& i: mutationMember) {
			mutation(new_population[i]);
		}*/
	}
	swap(new_population, population);
}

void solve() {
	ios_base::sync_with_stdio(false);
	std::string infile = "input.txt";
	std::string outfile = "output.txt";
	ifstream in(infile);
	
	in >> n;
	complex.resize(n);
	times.resize(n);
	for (int i = 0; i < n; ++i) { in >> complex[i];}
	for (int i = 0; i < n; ++i) { in >> times[i];}
	in >> m;
	coeff.resize(m, vector<double>(4));
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < 4; ++j) {
			in >> coeff[i][j];
		}
	}
	in.close();

	init();

	for (int i = 0; i < MAX_STEP; ++i) {
		step();
		if (GetAsyncKeyState(VK_ESCAPE)) {
			break;
		}
	}

	ofstream out_p("last_population.txt");
	for (auto& p : population) {
		for (auto& pi : p) {
			out_p << pi << " ";
		}
		out_p << endl;
	}
	out_p.close();

	ofstream out(outfile);
	for (auto& m : bestMember)
	{
		out << m << ' ';
	}
	out.close();
	
}

int main() {
	solve();
	return 0;
}