
#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>
#include <algorithm>
#include <cstdint>

template <typename T, typename Compare>
void quickSortHelper(std::vector<T>& songs, int low, int high,
                     Compare compare, std::uint64_t& comparisons) {

    if (low >= high) {
        return;
    }

    // pick the middle element as the pivot
    T pivot = songs[low + (high - low) / 2];

    int left = low;
    int i = low;
    int right = high;

    // separate smaller, equal and larger values
    while (i <= right) {
        comparisons++;

        if (compare(songs[i], pivot)) {
            std::swap(songs[i], songs[left]);
            left++;
            i++;
        }
        else {
            comparisons++;

            if (compare(pivot, songs[i])) {
                std::swap(songs[i], songs[right]);
                right--;
            }
            else {
                i++;
            }
        }
    }

    // sort both sides of the pivot
    quickSortHelper(songs, low, left - 1, compare, comparisons);
    quickSortHelper(songs, right + 1, high, compare, comparisons);
}

template <typename T, typename Compare>
std::uint64_t quickSort(std::vector<T>& songs, Compare compare) {

    std::uint64_t comparisons = 0;

    if (!songs.empty()) {
        quickSortHelper(songs, 0, static_cast<int>(songs.size()) - 1,
                        compare, comparisons);
    }

    return comparisons;
}

#endif
