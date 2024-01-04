#include "Heap.h"
#include <iostream>

void tok(std::string_view s, std::vector<std::string>& v) {
    int start {}, end {};
    while ((end = s.find(" ", start))!=std::string::npos) {
        std::string_view tmp {s};
        tmp.remove_prefix(start);
        tmp.remove_suffix(s.length()-end);
        start = end+1;
        v.push_back(std::string {tmp});
    }
    s.remove_prefix(start);
    v.push_back(std::string {s});
}

int main() {

    std::vector<int> heap {10,4,1,9,21,15,23,28};

    Heap<int> max_heap {heap};

    while (!max_heap.is_empty()) {
        std::cout << max_heap.pop() << " ";
    }

    return 0;
}