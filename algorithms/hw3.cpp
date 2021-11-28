#include <iostream> // cin, cout
#include <list> // list
#include <vector> // vector
#include <algorithm> // min, max
#include <utility> // pair
#include <cstddef> // size_t

struct Face {
	size_t x_, y_;
	Face(size_t x, size_t y) : x_(x), y_(y) {}
};

bool operator==(const Face &left, const Face &right) {
	return
		left.x_ == right.x_ && left.y_ == right.y_ ||
		left.x_ == right.y_ && left.y_ == right.x_;
}

bool operator!=(const Face &left, const Face &right) {
	return !(left == right);
}

class HashTable {
public:
	struct Node {
		std::pair<Face, size_t> data_ = { {0, 0}, 0 };
		bool empty_ = true;
	};

	HashTable() : table_(hashGroups_) {}
	HashTable(const HashTable &) = delete;
	HashTable &operator=(const HashTable &) = delete;

	~HashTable() { hashGroups_ = 0; }

	size_t hash(const Face &key) const {
		size_t x = hashNum(key.x_ < key.y_ ? key.x_ : key.y_);
		size_t y = hashNum(key.x_ >= key.y_ ? key.x_ : key.y_);
		return (x ^ (y << 1)) % hashGroups_;
	}

	void insert(const Face &key, size_t value) {
		size_t index = hash(key);
		size_t step = probingStep_;

		while (!table_[index].empty_ &&
			   table_[index].data_.first != key) {
			index = (index + step) % hashGroups_;
			step *= probingStep_;
		}
		table_[index].data_ = { key, value };
		table_[index].empty_ = false;
	}

	std::pair<std::pair<Face, size_t> *, bool> find(const Face &key) {
		std::pair<std::pair<Face, size_t> *, bool> result = std::make_pair(nullptr, false);
		size_t index = hash(key);
		size_t step = probingStep_;
		while (!table_[index].empty_ &&
			   table_[index].data_.first != key) {
			index = (index + step) % hashGroups_;
			step *= probingStep_;
		}
		if (!table_[index].empty_) {
			result.first = &table_[index].data_;
			result.second = true;
		}
		return result;
	}

	void reserve(size_t n) {
		if (n > hashGroups_) {
			hashGroups_ = n; // updates hash
			auto oldTable = table_;
			table_ = std::vector<Node>(n);

			for (auto cell = oldTable.begin(); cell != oldTable.end(); ++cell) {
				size_t index = hash(cell->data_.first);
				size_t step = probingStep_;
				while (!table_[index].empty_) {
					index = (index + step) % hashGroups_;
					step *= probingStep_;
				}
				table_[index].data_ = cell->data_;
				table_[index].empty_ = false;
			}
		}
	}

private:
	size_t hashGroups_ = 50;
	std::vector<Node> table_;
	static const size_t probingStep_ = 7;

	size_t hashNum(size_t num) const {
		return num % hashGroups_;
	}
};

struct Stone {
	size_t x_ = 0, y_ = 0, z_ = 0;

	Stone() = default;

	// Create a stone from a face and size.
	Stone(const Face &face, size_t size) :
		x_(face.x_),
		y_(face.y_),
		z_(size)
	{
	}

	std::vector<std::pair<Face, size_t>> facesAndHeights() const {
		return { {{x_, y_}, z_}, {{x_, z_}, y_}, {{y_, z_}, x_} };
	}

	size_t min() const {
		return std::min({ x_, y_, z_ });
	}
};

size_t girlOnTheBall() {
	size_t n;
	std::cin >> n;

	size_t count = 0;
	size_t maxSize = 0;
	HashTable sizes;
	sizes.reserve(4 * 3 * n + 13); // every stone has max 3 faces, we reseve more than that to have less collisions

	for (size_t i = 0; i < n; ++i) {
		Stone stone;
		std::cin >> stone.x_ >> stone.y_ >> stone.z_;

		size_t sizeGlue = 0;
		for (const auto &faceHeight : stone.facesAndHeights()) {
			auto found = sizes.find(faceHeight.first);
			if (found.second) {
				sizeGlue = std::max(
					sizeGlue,
					Stone(found.first->first, found.first->second + faceHeight.second).min()
				);
			}
		}

		size_t newSize = std::max(sizeGlue, stone.min());
		if (newSize > maxSize) {
			maxSize = newSize;
			++count;
		}

		for (const auto &it : stone.facesAndHeights()) {
			auto found = sizes.find(it.first);
			if (found.second) {
				found.first->second = std::max(it.second, found.first->second);
			} else {
				sizes.insert(it.first, it.second);
			}
		}
	}

	return count;
}
