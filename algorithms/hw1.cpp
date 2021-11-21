#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <list>

int shortestPaths() {
	size_t n, m;
	std::cin >> n >> m;

	std::unordered_map<size_t, std::vector<std::pair<size_t, size_t>>> adj_list;
	for (size_t i = 0; i < m; ++i) {
		size_t idx = 0;
		std::pair<size_t, size_t> vertex;
		std::cin >> idx >> vertex.first >> vertex.second;
		adj_list[idx].emplace_back(vertex);
	}
	size_t s, t, d;
	std::cin >> s >> t >> d;

	// Generate reversed graph.
	std::unordered_map<size_t, std::vector<std::pair<size_t, size_t>>> adj_list_back;
	for (size_t i = 0; i < adj_list.size(); ++i) {
		for (size_t j = 0; j < adj_list[i].size(); ++j) {
			adj_list_back[adj_list[i][j].first].push_back(std::make_pair(i, adj_list[i][j].second));
		}
	}

	// Priority queue.
	auto pair_greater = [](std::pair<size_t, size_t> left, std::pair<size_t, size_t> right) {
		return left.second > right.second;
	};
	std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, decltype(pair_greater)> Q(pair_greater);
	std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, decltype(pair_greater)> Q_back(pair_greater);

	auto pair_less = [](std::pair<size_t, size_t> left, std::pair<size_t, size_t> right) {
		return left.second < right.second;
	};
	std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, decltype(pair_greater)> begin(pair_greater);
	std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, decltype(pair_less)> end(pair_less);

	size_t num_visited = 0;
	std::vector<bool> boarder(n);
	Q.push(std::make_pair(s, 0));
	Q_back.push(std::make_pair(t, 0));
	std::vector<size_t> dist(n, ULONG_MAX);
	std::vector<size_t> dist_back(n, ULONG_MAX);
	dist[s - 1] = 0;
	dist_back[t - 1] = 0;
	std::vector<bool> visited(n, false);
	std::vector<bool> visited_back(n, false);
	std::vector<bool> yellow(n);
	std::vector<bool> yellow_back(n);
	yellow[s - 1] = true;
	yellow_back[t - 1] = true;
	visited[s - 1] = true;
	visited_back[t - 1] = true;
	size_t counter = 0;
	while (!Q.empty() || !Q_back.empty()) {
		if (!Q.empty()) {
			auto current = Q.top();
			Q.pop();
			for (auto neighbour : adj_list[current.first]) {
				if (!visited[neighbour.first - 1] &&
					dist[current.first - 1] + neighbour.second < dist[neighbour.first - 1])
				{
					dist[neighbour.first - 1] = std::min(dist[current.first - 1] + neighbour.second, dist[neighbour.first - 1]);
					Q.push(neighbour);
				}
			}
			for (auto neighbour : adj_list_back[current.first]) {
				if (!visited[neighbour.first - 1])
				{
					break;
				}
				visited[current.first - 1] = true;
			}

			if (!visited_back[current.first - 1])
				begin.push(std::make_pair(current.first, dist[current.first - 1]));
		}

		if (!Q_back.empty()) {
			auto current = Q_back.top();
			Q_back.pop();
			for (auto neighbour : adj_list_back[current.first]) {
				if (!visited_back[neighbour.first - 1] && dist_back[current.first - 1] + neighbour.second < dist_back[neighbour.first - 1]) {
					dist_back[neighbour.first - 1] = dist_back[current.first - 1] + neighbour.second;
					Q_back.push(neighbour);
				}
			}

			for (auto neighbour : adj_list[current.first]) {
				if (!visited_back[neighbour.first - 1]) {
					break;
				}
				visited_back[current.first - 1] = true;
			}
			if (!visited[current.first - 1])
				end.push(std::make_pair(current.first, dist_back[current.first - 1]));
			if (end.top().second > d && counter == 900) {
				while (!Q_back.empty() && !Q.empty()) {
					Q_back.pop();
					Q.pop();
				}
			}
			else if (end.top().second > d) {
				counter++;
			}
		}
	}

	size_t res = 0;
	while (!begin.empty()) {
		auto left = begin.top();
		begin.pop();
		while (!end.empty()) {
			auto right = end.top();
			if (left.second + right.second + 1 <= d) {
				res += end.size();
				break;
			}
			else
			{
				end.pop();
			}
		}
	}

	if (dist[t - 1] <= d)
	{
		res = n * (n - 1);
	}
	std::cout << res;
	return 0;
}
