//
// Created by ibqo on 2020/1/4.
//
#include <cstdint>
#include <folly/AtomicHashmap.h>

using namespace folly;
using namespace std;

class Counters {
private:
    AtomicHashMap<int64_t,int64_t> ahm;

public:
    explicit Counters(size_t numCounters) : ahm(numCounters) {}

    void increment(int64_t obj_id) {
        auto ret = ahm.insert(make_pair(obj_id, 1));
        if (!ret.second) {
            // obj_id already exists, increment
            NoBarrier_AtomicIncrement(&ret.first->second, 1);
        }
    }

    int64_t getValue(int64_t obj_id) {
        auto ret = ahm.find(obj_id);
        return ret != ahm.end() ? ret->second : 0;
    }

    // Serialize the counters without blocking increments
    string toString() {
        string ret = "{\n";
        ret.reserve(ahm.size() * 32);
        for (const auto& e : ahm) {
            ret += folly::to<string>(
                    "  [", e.first, ":", NoBarrier_Load(&e.second), "]\n");
        }
        ret += "}\n";
        return ret;
    }
};

