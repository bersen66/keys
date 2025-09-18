#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

#include <keys/keys.hpp>

struct Entry {
    std::string id;
    int epoch;
};

int main() {
    std::priority_queue<Entry, std::vector<Entry>, keys::Greater<&Entry::epoch, &Entry::id>> q;
    q.emplace("a", 1);
    q.emplace("b", 2);
    q.emplace("c", 4);
    q.emplace("d", 5);

    std::cout << "In priority_queue: " << std::endl;
    while (q.size()) {
        std::cout << " -- " << q.top().id << " " << q.top().epoch << std::endl;
        q.pop();
    }

    std::unordered_set<Entry, keys::Hash<&Entry::epoch, &Entry::id>, keys::Equal<&Entry::epoch, &Entry::id>> set;
    set.emplace("a", 1);
    set.emplace("b", 2);
    set.emplace("b", 3);

    std::cout << "In unordered_set: " << std::endl;

    for (const auto& [epoch, id] : set) {
        std::cout << " -- " << epoch << " " << id << std::endl;
    }

    std::vector<Entry> entries = {
        {"Hello", 10},
        {"Hello", 10},
        {"Hello",  9},
        {"Hello",  8},
        {"Hello",  7},
    };

    std::cout << "Sort vector of structs" << std::endl;
    std::ranges::sort(entries, keys::Greater<&Entry::epoch>{});

    for (const auto& [epoch, id] : entries) {
        std::cout << " -- " << epoch << " " << id << std::endl;
    }

    std::vector<Entry*> entries2 = {
        &entries[0], &entries[0], &entries[1], &entries[2], &entries[4],
        &entries[4], &entries[4], &entries[4], &entries[3],
    };
    std::sort(entries2.begin(), entries2.end(), keys::Less<&Entry::epoch>{});

    std::cout << "Sort vector of pointers" << std::endl;

    for (Entry* ptr : entries2) {
        std::cout << " -- " << (ptr->epoch) << " " << (ptr->id) << std::endl;
    }

    std::unordered_map<Entry, int, keys::Hash<&Entry::id>, keys::Equal<&Entry::id>> map;
    map[Entry{.id = "hello", .epoch = 0}] = 1;
    map[Entry{.id = "hello", .epoch = 2}] = 10;
    std::cout << "In unordered_map: " << std::endl;

    for (const auto& [entry, num] : map) {
        std::cout << " -- [" << entry.id << ", " << entry.epoch << "] " << num << std::endl;
    }

    return 0;
}
