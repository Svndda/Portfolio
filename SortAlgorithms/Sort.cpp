//
// Copyright (c) 2024 Aaron Carmona Sanchez <aaroncz032@gmail.com>
//

#include <utility>
#include <random>
#include <vector>

#include "Sort.hpp"

void mergesort(std::vector<int>& vector, const int left, const int right);
void divConquer(std::vector<int>& vector, const int left, const int middle,
    const int right);
void heapify(std::vector<int>& vector, const int n, const int parent);
void quicksort(std::vector<int>& vector, const int start, const int end);
int partition(std::vector<int>& vector, const int start, const int end);
void createSafeKey(std::vector<int>& vector, const int low, const int high);
void radixHandler(std::vector<int>& vector, const int pos);
int getMax(const std::vector<int>& vector);

namespace Sort {
void insertion(std::vector<int>& vector) {
  const int size = vector.size();
  // Iterate over the vector starting from the second element.
  for (int i = 1; i < size; i++) {
    // Take the current element as the key.
    const int key = vector[i];
    // Initialize the index of the previous element.
    int j = i - 1;
    // Shift elements of the sorted portion to make space for the key.
    while (j >= 0 && vector[j] > key) {
      // Shift the element to the right.
      vector[j + 1] = vector[j];
      // Move to the previous element in the sorted portion.
      j--;
    }
    // Insert the key in the correct position.
    vector[j + 1] = key;
  }
}

void selection(std::vector<int>& vector) {
  const int size = vector.size();
  // Iterate over the vector
  for (int i = 0; i < size; i++) {
    // Initialize the index of the minimum element
    int key = i;
    // Find the index of the minimum element
    for (int j = i + 1; j < size; j++) {
      // Update the index of the minimum element
      if (vector[j] < vector[key]) {
        key = j;
      }
    }
    // Swap the found minimum element with the first element
    std::swap(vector[i], vector[key]);
  }
}

void mergesort(std::vector<int>& vector) {
  ::mergesort(vector, 0, vector.size() - 1);
}

void heapsort(std::vector<int>& vector) {
  for (int i = vector.size() / 2 - 1; i >= 0; i--) {
    heapify(vector, vector.size(), i);
  }

  for (int i = vector.size() - 1; i > 0; i--) {
    std::swap(vector[0], vector[i]);
    heapify(vector, i, 0);
  }
}

void quicksort(std::vector<int>& vector) {
  ::quicksort(vector, 0, vector.size() - 1);
}

void radixsort(std::vector<int>& vector) {
  int max = getMax(vector);
  for (int i = 1; (max / i) > 0; i *= 10) {
    radixHandler(vector, i);
  }
}

}  // namespace Sort

void mergesort(std::vector<int>& vector, const int left, const int right) {
  // Check if there are more than one element in the subarray
  if (left < right) {
    // Calculate the middle index of the subarray
    const int middle = left + (right - left) / 2;
    // Recursive call to mergeSort for the left half of the array
    mergesort(vector, left, middle);
    // Recursive call to mergeSort for the right half of the array
    mergesort(vector, middle + 1, right);
    // Merge the sorted halves
    divConquer(vector, left, middle, right);
  }
}

void divConquer(std::vector<int>& vector, const int left, const int middle,
    const int right) {
  // Calculate the sizes of the left and right subarrays
  const int leftSize = middle - left + 1;
  const int rigthSize = right - middle;

  // Create temporary vectors to store the left and right subarrays
  std::vector<int> leftVector(leftSize);
  std::vector<int> rigthVector(rigthSize);

  // Copy data to temporary arrays
  for (int i = 0; i < leftSize; i++) {
    leftVector[i] = vector[left + i];
  }
  for (int i = 0; i < rigthSize; i++) {
    rigthVector[i] = vector[middle + i + 1];
  }

  // Merge the two subarrays into the original array
  int i = 0;
  int j = 0;
  int k = left;

  // Copy any remaining elements of left subarray
  while (i < leftSize && j < rigthSize) {
    if (leftVector[i] <= rigthVector[j]) {
      vector[k] = leftVector[i];
      i++;
    } else {
      vector[k] = rigthVector[j];
      j++;
    }
    k++;
  }

  // Copy any remaining elements of left subarray
  while (i < leftSize) {
    vector[k] = leftVector[i];
    i++;
    k++;
  }

  // Copy any remaining elements of right subarray
  while (j < rigthSize) {
    vector[k] = rigthVector[j];
    j++;
    k++;
  }
}

void heapify(std::vector<int>& vector, const int n, const int parent) {
  // Initialize largest as root.
  int largest = parent;
  // Left and right child of the root.
  const int leftSon = parent * 2;
  const int rightSon = (parent * 2) + 1;

  // If the left child is larger than the root.
  if (leftSon < n && vector[leftSon] > vector[largest]) {
    largest = leftSon;
  }

  // If the right child is larger than the root.
  if (rightSon < n && vector[rightSon] > vector[largest]) {
    largest = rightSon;
  }
  // If the largest element is not the parent.
  if (largest != parent) {
    // Swap the parent with the largest element.
    std::swap(vector[parent], vector[largest]);
    // Recursively heapify the affected sub-tree.
    heapify(vector, n, largest);
  }
}


void quicksort(std::vector<int>& vector, const int start, const int end) {
  if (start < end) {
    // Creates a pivot index to divide the array.
    const int key = partition(vector, start, end);
    // Recursively sort the left subarray.
    quicksort(vector, start, key - 1);
    // Recursively sort the right subarray.
    quicksort(vector, key + 1, end);
  }
}

int partition(std::vector<int>& vector, const int start, const int end) {
  // Create a safe key.
  createSafeKey(vector, start, end);
  // Pivot
  const int key = vector[end];
  // Index of smaller index.
  int it1 = start;
  // Traverse the subarray
  for (int it2 = start; it2 < end; it2++) {
    // If current element is smaller than or equal to pivot, then swap the
    // current element with the smaller elements.
    if (vector[it2] <= key) {
      std::swap(vector[it1], vector[it2]);
      it1++;
    }
  }
  // Swap the pivot element with the smaller element
  std::swap(vector[it1], vector[end]);
  return it1;
}

void createSafeKey(std::vector<int>& vector, const int low, const int high) {
  std::mt19937 rng(std::random_device {} ());
  // Create a random number between low and high.
  std::uniform_int_distribution<int> dist(low, high - 1);
  const int safeIndex = dist(rng);
  // Swap the pivot with a random subarray value.
  std::swap(vector[safeIndex], vector[high]);
}

void radixHandler(std::vector<int>& vector, const int pos) {
  // Count array
  int count[10] = { 0 };

  // Calculate the frequency of each digit.
  for (int i = 0; i < vector.size(); i++) {
    count[(vector[i] / pos) % 10]++;
  }

  // Calculate the histogram to get the starting index of each digit.
  for (int i = 1; i < 10; i++) {
    count[i] = count[i] + count[i - 1];
  }

  // Generate the results.
  int results[vector.size()];
  for (int i = vector.size() - 1; i >= 0; i--) {
    results[--count[(vector[i] / pos) % 10]] = vector[i];
  }

  // Copy the results to the original array.
  for (int i = 0; i < vector.size(); i++) {
    vector[i] = results[i];
  }
}

int getMax(const std::vector<int>& vector) {
  int max = INT32_MIN;
  // Find the max value in the vector.
  for (int i = 0; i < vector.size(); i++) {
    if (vector[i] > max) {
      max = vector[i];
    }
  }
  return max;
}


