#include <iostream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

using ll = long long;


#define FREE  0
#define WALL -1


int main() {
#ifdef _DEBUG
    std::string infile = "input.txt";
    std::string outfile = "output.txt";
    ios_base::sync_with_stdio(false);
    ifstream in(infile);
    ofstream out(outfile);
    cin.rdbuf(in.rdbuf());
    cout.rdbuf(out.rdbuf());
#endif

	int n, m;
	cin >> n >> m;

    vector<vector<ll>>labyrinth(n, vector<ll>(m, 0));
	for(int i = 0;  i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int c; cin >> c;
			if (c == 0) {
				labyrinth[i][j] = FREE;
			}
			else if (c == 1) {
				labyrinth[i][j] = WALL;
			}
		}
    }

    int x1, y1, x2, y2; cin >> y1 >> x1 >> y2 >> x2;
	--x1; --y1; --x2; --y2;

    queue<pair<int, int>> q;

    if (labyrinth[x1][y1] == FREE) {
        q.push(make_pair(x1, y1));
	}

    while (!q.empty()) {
        auto t = q.front();
         q.pop();
        if ((t.first + 1) < n && labyrinth[t.first + 1][t.second] == FREE) {
            q.push(make_pair(t.first + 1, t.second));
            labyrinth[t.first + 1][t.second] = labyrinth[t.first][t.second] + 1;
        }
        if ((t.second + 1) < m && labyrinth[t.first][t.second + 1] == FREE) {
            q.emplace(t.first, t.second + 1);
            labyrinth[t.first][t.second + 1] = labyrinth[t.first][t.second] + 1;
        }
        if ((t.first - 1) >= 0 && labyrinth[t.first - 1][t.second] == FREE) {
            q.emplace(t.first - 1, t.second);
            labyrinth[t.first - 1][t.second] = labyrinth[t.first][t.second] + 1;
        }
        if ((t.second - 1) >= 0 && labyrinth[t.first][t.second - 1] == FREE) {
            q.emplace(t.first, t.second - 1);
            labyrinth[t.first][t.second - 1] = labyrinth[t.first][t.second] + 1;
        }
        if (t.first == x2 && t.second == y2)
            break;
    }

	if (x1 == x2 && y2 == y1 && labyrinth[x2][y2] != WALL) {
		cout << 0;
	}
    else if (labyrinth[x2][y2] == FREE || labyrinth[x2][y2] == WALL)
        cout << -1;
    else
        cout << labyrinth[x2][y2];

    return 0;
}