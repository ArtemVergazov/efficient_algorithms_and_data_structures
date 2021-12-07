#include <iostream> // cin, cout, endl
#include <string> // string
#include <vector> // vector

int reverseParent(const std::vector<int> &parent, int N) {
    return parent[N - 1] == 1 ? 1 : reverseParent(parent, parent[N - 1] - 1) + 1;
}

// The solution uses approach from Cormen's book: the for loops, the data structures, the DP approach...
std::pair<int, int> prettyPrinting() {
    int N, L;
    std::cin >> N >> L;
    std::vector<int> wordLengths(N);

    for (int i = 0; i < N; ++i) {
        std::string word;
        std::cin >> word;
        wordLengths[i] = static_cast<int>(word.size());
    }

    std::vector<std::vector<int>> spaces(N, { 0 });
    for (int i = 0; i < N; ++i) {
        spaces[i][0] = L - wordLengths[i];
        for (int j = 1; j < N - i; ++j) {
            int newSpaces = spaces[i][j - 1] - wordLengths[i + j] - 1;
            if (newSpaces < 0) break;
            spaces[i].push_back(newSpaces);
        }
    }

    std::vector<std::vector<int>> costs(N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < spaces[i].size(); ++j) {
            costs[i].push_back(i + j == N ? 0 : spaces[i][j] * spaces[i][j]);
        }
    }

    std::vector<int> optCost(N + 1, INT_MAX);
    std::vector<int> parent(N);
    optCost[0] = 0;
    for (int j = 1; j <= N; ++j) {
        for (int i = 1; i <= j; ++i) {
            if (
                spaces[i - 1].size() > j - i &&
                optCost[i - 1] != INT_MAX &&
                optCost[i - 1] + costs[i - 1][j - i] < optCost[j]
                ) {
                optCost[j] = optCost[i - 1] + costs[i - 1][j - i];
                parent[j - 1] = i;
            }
        }
    }

    return { optCost[N], reverseParent(parent, N) };
}
