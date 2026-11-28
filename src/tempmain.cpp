#include "song.h"
#include "quicksort.h"
#include <iostream>

int main() {
    // 1. Test CSV loading
    std::vector<Song> songs = loadSongs("data/dataset.csv");
    std::cout << "Loaded " << songs.size() << " tracks.\n\n";

    if (songs.empty()) {
        std::cerr << "Check that data/dataset.csv exists in the right folder!\n";
        return 1;
    }

    // 2. Test sorting by popularity (descending) + Top N tracks
    auto byPopularityDesc = [](const Song& a, const Song& b) {
        return a.popularity > b.popularity;
    };

    std::uint64_t comparisons = quickSort(songs, byPopularityDesc);
    std::cout << "QuickSort comparisons: " << comparisons << "\n";
    topNTracks(songs, 5, "popularity");

    std::cout << "\n";

    // 3. Test another attribute (e.g., duration descending)
    auto byDurationDesc = [](const Song& a, const Song& b) {
        return a.duration_ms > b.duration_ms;
    };

    quickSort(songs, byDurationDesc);
    topNTracks(songs, 3, "duration");

    return 0;
}
