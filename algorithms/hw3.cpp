#include <iostream>

struct Ball {
  unsigned x, y, z;


};

unsigned girlOnTheBall() {
  unsigned n;
  std::cin >> n;

  unsigned diamIncreased = 0;
  for (unsigned i = 0; i < n; ++i) {
    Ball ball;
    std::cin >> ball.x >> ball.y >> ball.z;
  }

  Ball b{ 1, 2, 3 };
  return 0;
}
