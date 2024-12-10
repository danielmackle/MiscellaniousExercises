//
// Created by Daniel Mackle on 10/12/2024.
//

#pragma once
#include <iostream>
#include <vector>

template<typename T>
class Sorts {
public:
    // O(N^2)
    static void selectionSort(std::vector<T>& array) {
        const int size = array.size();
        for (int i = 0; i < size - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < size; j++) {
                if (array[j] < array[minIndex]) {
                    minIndex = j;
                }
            }
            if (minIndex != i) {
                std::swap(array[i], array[minIndex]);
            }
        }
        return array;
    }

    // O(N^2)
    static void insertionSort(std::vector<T>& array) {
        const int size = array.size();
        for (int i = 1; i < size; i++) {
            T key = array[i];
            int j = i - 1;
            while (j >= 0 && array[j] > key) {
                array[j + 1] = array[j];
                j = j - 1;
            }
            array[j + 1] = key;
        }
    }

    // O(N^2)
    static void bubbleSort(std::vector<T>& array) {
        const int size = array.size();
        bool swapped = false;
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (array[i] > array[j]) {
                    std::swap(array[j], array[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) {
                break;
            }
        }
    }

    // O(NlogN)
    static void mergeSort(std::vector<T> &array) {
        return mergeSort(array, 0, array.size()-1);
    }

    // O(NlogN)
    static void quickSort(std::vector<T>& array) {
        quickSort(array, 0, array.size()-1);
    }

    static void printArray(const std::vector<int>& array) {
        for (const int i : array) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
private:
    void merge(std::vector<T> &array, const int left, const int mid, const int right) {
        int sizeLeft = mid - left + 1;
        int sizeRight = right - mid;

        // Create temporary arrays for left and right sub-arrays
        std::vector<T> leftArr(sizeLeft);
        std::vector<T> rightArr(sizeRight);

        // Copy data to temp arrays leftArr[] and rightArr[]
        for (int i = 0; i < sizeLeft; i++) {
            leftArr[i] = array[left + i];
        }
        for (int j = 0; j < sizeRight; j++) {
            rightArr[j] = array[mid + 1 + j];
        }

        // Merge the temp arrays back into the original array
        int i = 0, j = 0, k = left;
        while (i < sizeLeft && j < sizeRight) {
            if (leftArr[i] <= rightArr[j]) {
                array[k] = leftArr[i];
                i++;
            } else {
                array[k] = rightArr[j];
                j++;
            }
            k++;
        }

        // Copy the remaining elements of leftArr[], if any
        while (i < sizeLeft) {
            array[k] = leftArr[i];
            i++;
            k++;
        }

        // Copy the remaining elements of rightArr[], if any
        while (j < sizeRight) {
            array[k] = rightArr[j];
            j++;
            k++;
        }
    }
    void mergeSort(std::vector<T> &array, const int left, const int right) {
        if (left < right) {
            const int mid = left + (right - left) / 2;

            // Recursively sort the two halves
            mergeSort(array, left, mid);
            mergeSort(array, mid + 1, right);

            // Merge the two sorted halves
            return merge(array, left, mid, right);
        }
    }
    static int partition(std::vector<int>& array, const int low, const int high) {
        const int pivot = array[high];  // Pivot element
        int i = low - 1;  // Index of smaller element

        for (int j = low; j <= high - 1; j++) {
            // If current element is smaller than or equal to pivot
            if (array[j] <= pivot) {
                i++;  // Increment index of smaller element
                std::swap(array[i], array[j]);  // Swap elements
            }
        }
        std::swap(array[i + 1], array[high]);  // Swap pivot with the element at i+1
        return (i + 1);  // Return the partitioning index
    }

    static void quickSort(std::vector<int>& arr, const int low, const int high) {
        if (low < high) {
            const int pi = partition(arr, low, high);  // Partitioning index
            quickSort(arr, low, pi - 1);  // Recursively sort the left part
            quickSort(arr, pi + 1, high);  // Recursively sort the right part
        }
    }
};
