
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <functional>
#include "../src/quicksort.h"

using namespace std;

template <typename Compare>
bool runTest(string name, vector<int> values, Compare compare) {

    // make a copy to check results later
    vector<int> expected = values;

    sort(expected.begin(), expected.end(), compare);

    uint64_t comparisons = quickSort(values, compare);

    bool passed = values == expected;

    cout << name << ": ";
    cout << (passed ? "PASS" : "FAIL");
    cout << " | comparisons: " << comparisons << endl;

    return passed;
}
struct TestSong {
    string name;
    int popularity;
    double energy;
};

bool testSongs() {
    vector<TestSong> songs = {
        {"Song A", 80, 0.5},
        {"Song B", 30, 0.9},
        {"Song C", 90, 0.3},
        {"Song D", 80, 0.7}
    };

    // sort by popularity
    quickSort(songs, [](const TestSong& a, const TestSong& b) {
        return a.popularity > b.popularity;
    });

    bool popularityPassed =
        is_sorted(songs.begin(), songs.end(),
            [](const TestSong& a, const TestSong& b) {
                return a.popularity > b.popularity;
            });

    // sort by energy
    quickSort(songs, [](const TestSong& a, const TestSong& b) {
        return a.energy < b.energy;
    });

    bool energyPassed =
        is_sorted(songs.begin(), songs.end(),
            [](const TestSong& a, const TestSong& b) {
                return a.energy < b.energy;
            });

    bool passed = popularityPassed && energyPassed;

    cout << "song objects: "
         << (passed ? "PASS" : "FAIL") << endl;

    return passed;
}
int main() {

    int passed = 0;
    int total = 0;

    // basic sorting tests
    passed += runTest("random values",
        {50, 20, 80, 10, 90, 30}, less<int>());
    total++;

    passed += runTest("already sorted",
        {10, 20, 30, 40, 50}, less<int>());
    total++;

    passed += runTest("reverse sorted",
        {50, 40, 30, 20, 10}, less<int>());
    total++;

    passed += runTest("descending order",
        {30, 10, 50, 20, 40}, greater<int>());
    total++;

    // check how the algorithm handles duplicates
    passed += runTest("duplicate values",
        {50, 20, 50, 30, 50, 20}, less<int>());
    total++;

    passed += runTest("all equal",
        {50, 50, 50, 50, 50}, less<int>());
    total++;

    // check edge cases
    passed += runTest("empty vector",
        {}, less<int>());
    total++;

    passed += runTest("single element",
        {50}, less<int>());
    total++;

    // generate popularity scores for 114000 songs
    mt19937 generator(42);
    uniform_int_distribution<int> distribution(0, 100);

    vector<int> largeData(114000);

    for (int& value : largeData) {
        value = distribution(generator);
    }

    passed += runTest("large random dataset",
        largeData, less<int>());
    total++;

    sort(largeData.begin(), largeData.end());

    passed += runTest("large sorted dataset",
        largeData, less<int>());
    total++;

    reverse(largeData.begin(), largeData.end());

    passed += runTest("large reverse sorted dataset",
        largeData, less<int>());
    total++;

    passed += runTest("large descending dataset",
        largeData, greater<int>());
    total++;
    passed += testSongs();
    total++;
    cout << "\nTests passed: " << passed
         << "/" << total << endl;

    return passed == total ? 0 : 1;
}
