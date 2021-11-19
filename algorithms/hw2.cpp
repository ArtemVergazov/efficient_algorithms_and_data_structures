#include <iostream>

auto input() {
  uint16_t m, n;
  std::cin >> m, n;

  for (uint16_t i = 0; i < m; ++i) {
    for (uint16_t j = 0; j < n; ++j) {
      char *c = new char[n];
      std::cin >> c;

      delete[] c;
      c = nullptr;
    }
  }
}

void dominoes() {
}
