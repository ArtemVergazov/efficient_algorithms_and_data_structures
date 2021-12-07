#include <iostream>
// int shortestPaths();
// int dominoes();
// size_t girlOnTheBall();
std::pair<int, int> prettyPrinting();

int main() {
	// std::cout << shortestPaths() << std::endl;
	// std::cout << dominoes() << std::endl;
	//std::cout << girlOnTheBall() << std::endl;
	auto pp = prettyPrinting();
	std::cout << pp.first << ' ' << pp.second << std::endl;
}
