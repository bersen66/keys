# Keys: projections for containers

This library provides generic comparators for usage with STL containers.

## Examples:

### Less painful `priority_queue` initialization

```C++
#include <queue>
#include <keys/keys.hpp>

struct Entry {
    std::string id;
    int epoch;
};

// You don't need to implement your own comparator
// Instead -- use `projection-like` interface
using EpochHeap = std::priority_queue<Entry, std::vector<Entry>, keys::Less<&Entry::epoch>>;

EpochHeap eph;
eph.emplace("Floppa the cat", 1);
eph.emplace("Floppa the cat", 2);
eph.emplace("Floppa the cat", 3);

```


### Composite hash

```C++
struct Entry {
    std::string id;
    std::string surname;
    int epoch;
};

std::unordered_set<
    Entry, // Stores Entries
    keys::Hash<&Entry::epoch, &Entry::id>, // Combining hash of fields
    keys::Equal<&Entry::epoch, &Entry::id> // Composite == for Entry
> set;

// Or

std::unordered_set<
    Entry, // Stores Entries
    keys::Hash<>, // Combine hash of whole struct
    keys::Equal<> // Compare all fields
> set;

set.emplace("a", "cd", 1);
set.emplace("b", "cq", 2);
set.emplace("b", "de", 3);

```