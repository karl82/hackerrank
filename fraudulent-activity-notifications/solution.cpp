#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <list>
#include <algorithm>

using namespace std;


int main() {
    unsigned int n;
    unsigned int d;

    cin >> n >> d;

    if (n < d) { return 0; }

    list<unsigned int> spending;
    auto warnings = 0;

    vector<unsigned int> sliding_window;
    const auto median_pos = d / 2;

    cerr << "median_pos: " << median_pos << endl;

    for (auto i = 0; i < n; i++) {
        unsigned int that_day;
        scanf("%u", &that_day);
        spending.push_back(that_day);
        sliding_window.insert(lower_bound(sliding_window.begin(), sliding_window.end(), that_day), that_day);

        if (i >= d) {
            auto median = (d % 2) == 0 ? (sliding_window[median_pos] + sliding_window[median_pos - 1]) / 2.0
                                                : sliding_window[median_pos];

            if (2 * median <= spending.back()) {
                warnings++;
            }

            auto removal_it = lower_bound(sliding_window.begin(), sliding_window.end(), spending.front());
            sliding_window.erase(removal_it);
            spending.pop_front();
        }
    }

    cout << warnings << endl;

    return 0;
}

