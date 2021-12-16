#include <iostream> // cin, cout
#include <string> // string

bool checkEqualSubstr(
	const char *s1begin, const char *s1end,
	const char *s2begin, const char *s2end
) {
	if ((s1end - s1begin) != (s2end - s2begin)) throw std::runtime_error("You screwed up checking substrings!");

	for (; s1begin != s1end; ++s1begin, ++s2begin) {
		if (*s1begin != *s2begin) return false;
	}
	return true;
}

void interestingSubstring() {
	std::string s;
	std::cin >> s;
	size_t n = s.size();
	int largest = -1;
	for (size_t i = 1; i <= n - 2; ++i) {
		if (checkEqualSubstr(&s[0], &s[i], &s[n - i], &s[n])) {
			for (size_t k = 1; k <= n - i - 1; ++k) {
				if (checkEqualSubstr(&s[0], &s[i], &s[k], &s[k + i])) {
					largest = (int)i;
					break;
				}
			}
		}
	}

	if (largest == -1) {
		std::cout << -1 << std::endl;
		return;
	}

	for (size_t i = 0; i < largest; ++i) {
		std::cout << s[i];
	}
	std::cout << std::endl;
}