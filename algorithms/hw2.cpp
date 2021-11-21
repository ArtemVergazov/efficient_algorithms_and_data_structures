#include <vector>
#include <iostream>

std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> grid;
std::vector<int> matching;
std::vector<bool> used;

bool kuhn(int v) {
	if (used[v])
		return false;
	used[v] = true;
	for (int to : graph[v]) {
		if (matching[to] == -1 || kuhn(matching[to])) {
			matching[to] = v;
			return true;
		}
	}
	return false;
}

int dominoes() {
	int m, n;
	int count = 0;
	std::cin >> m >> n;

	int blacks = 0, whites = 0;
	for (int i = 0; i < m; i++) {
		char row[255];
		std::cin >> row;
		std::vector<int> gridRow;
		for (int j = 0; j < n; j++) {
			if (row[j] != '#')
				gridRow.push_back((i + j) % 2 == 0 ? ++blacks : -++whites);
			else
				gridRow.push_back(0);
		}
		grid.push_back(gridRow);
	}

	graph.resize(blacks, { 0 });
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			std::vector<int> tmp;
			if (grid[i][j] > 0) {
				for (int add : {-1, 1}) {
					if (0 <= j + add && j + add < n && grid[i][j + add] < 0)
						tmp.push_back(-grid[i][j + add] - 1);
					if (0 <= i + add && i + add < m && grid[i + add][j] < 0) {
						tmp.push_back(-grid[i + add][j] - 1);
					}
				}
				graph.insert(graph.begin() + grid[i][j] - 1, tmp);
				graph.erase(graph.begin() + grid[i][j]);
			}
		}
	}

	matching.assign(whites, -1);
	for (int v = 0; v < blacks; ++v) {
		used.assign(blacks, false);
		kuhn(v);
	}

	for (int i = 0; i < whites; ++i)
		if (matching[i] != -1) {
			++count;
		}
	return count;
}
