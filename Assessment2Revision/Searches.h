//
// Created by Daniel Mackle on 10/12/2024.
//

#pragma once
#include <vector>

template<typename T>
class Searches {
public:
    static T linearSearch(T value, std::vector<T>& array) {
        for (int i = 0; i < array.size(); i++) {
            if (array[i] == value) {
                return i;
            }
        }
        return -1;
    }

    static T binarySearch(T value, std::vector<T>& array) {
        return binarySearch(value, array, 0, array.size() - 1);
    }
private:
    T binarySearch(T value, std::vector<T>& array, const int low, const int high) {
        if (low > high) {
            return -1;
        }
        int mid = low + (high - low) / 2;
        if (array[mid] == value) {
            return mid;
        }
        if (array[mid] > value) {
            return binarySearch(value, array, low, mid-1);
        }
        return binarySearch(value, array, mid+1, high);
    }
};
