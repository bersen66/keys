#include <iostream>
#include <set>
#include <queue>
#include <type_traits>
#include <vector>
#include <algorithm>
#include <unordered_set>

struct Entry {
    std::string id;
    int epoch;
};

int main() {
    
    std::priority_queue<Entry, std::vector<Entry>, member::Greater<&Entry::epoch, &Entry::id>> q;
    q.emplace("a", 1);
    q.emplace("b", 2);
    q.emplace("c", 4);
    q.emplace("d", 5);

    while (q.size()) {
        std::cout << q.top().id << " " << q.top().epoch << std::endl;
        q.pop();
    }

    std::unordered_set<Entry, member::Hash<&Entry::epoch, &Entry::id>, member::Equal<&Entry::epoch, &Entry::id>> set;
    set.emplace("a", 1);
    
    std::vector<Entry> enries = {
        {"Hello", 10},
        {"Hello", 10},
        {"Hello", 9},
        {"Hello", 8},
        {"Hello", 7},
    };

    std::vector<Entry*> enries2 = {
        &enries[0],
        &enries[1],
        &enries[2],
        &enries[4],
        &enries[3],
    };
    std::sort(enries2.begin(), enries2.end(), member::Less<&Entry::epoch>{});
    for (const auto& ptr : enries2) {
        std::cout << ptr->id << " -- " << ptr->epoch << std::endl;
    }
    return 0;
}
