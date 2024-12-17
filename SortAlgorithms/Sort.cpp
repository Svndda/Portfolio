//
// Copyright (c) 2024 Aaron Carmona Sanchez <aaroncz032@gmail.com>
//
#include "Sort.hpp"

void mergesort(std::vector<int>& vector, const int left, const int right);
void divConquer(std::vector<int>& vector, const int left, const int middle, const int right);
void heapify(int* A, int n, int parent);
int partition(int* A, int start, int end);
void createSafeKey(int* A, int low, int high);
void radixHandler(int* A, int n, int pos);
int getMax(const int* A, int n);

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
      while(j >= 0 && vector[j] > key) {
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
}

void mergesort(std::vector<int>& vector, const int left, const int right) {
  // Check if there are more than one element in the subarray
  if (left < right) {

    // Calculate the middle index of the subarray
    int middle = left + (right - left) / 2;
    // Recursive call to mergeSort for the left half of the array
    mergesort(vector, left, middle);
    // Recursive call to mergeSort for the right half of the array
    mergesort(vector, middle + 1, right);
    // Merge the sorted halves
    divConquer(vector, left, middle, right);
  }
}

void divConquer(std::vector<int>& vector, const int left, const int middle, const int right) {
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
  while(i < leftSize && j < rigthSize) {
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
  while(i < leftSize) {
    vector[k] = leftVector[i];
    i++;
    k++;
  }

  // Copy any remaining elements of right subarray
  while(j < rigthSize) {
    vector[k] = rigthVector[j];
    j++;
    k++;
  }
}

void heapsort(int *A, int n) {
  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify(A, n, i);
  }

  for (int i = n - 1; i > 0; i--) {
    std::swap(A[0], A[i]);
    heapify(A, i, 0);
  }
}

void heapify(int* A, int n, int parent) {
  int largest = parent;
  int leftSon = parent * 2;
  int rightSon = (parent * 2) + 1;

  if (leftSon < n && A[leftSon] > A[largest]) {
    largest = leftSon;
  }

  if (rightSon < n && A[rightSon] > A[largest]) {
    largest = rightSon;
  }

  if (largest != parent) {
    std::swap(A[parent], A[largest]);
    heapify(A, n, largest);
  }
}

void quicksort(int *A, int start, int end) {
  if (start < end) {
    int key = partition(A, start, end);
    quicksort(A, start, key - 1);
    quicksort(A,key + 1, end);
  }
}

/**
 * Sort the given subarray based on a pivot
 *
 * @param A       Subarray to be sorted
 * @param start   Subarray´s begin index
 * @param end     Subarray´s final index
 * @return        new pivot´s index
 */
int partition(int* A, int start, int end) {
  createSafeKey(A, start, end);
  int key = A[end];

  int it1 = start;
  int it2 = end - 1;

  for (; it1 < it2; it1++) {
    if (A[it1] > key) {
      for (; it2 > it1; it2--) {
        if (A[it2] < key) {
          std::swap(A[it1], A[it2]);
          break;
        }
      }
    }
  }
  std::swap(A[it1], A[end]);
  return it1;
}

/**
 * Creates a safe key value by swapping the pivots value with a random subarray value
 *
 * @param A       Subarray to be access
 * @param low     Lowest index to be accessed
 * @param high    Higher index to be accessed (Pivot´s index)
 */
void createSafeKey(int* A, int low, int high) {
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(low, high - 1);
  int safeIndex = dist(rng);
  std::swap(A[safeIndex], A[high]);
}

void radixsort(int *A, int n) {
  int max = getMax(A, n);
  for (int i = 1; (max / i) > 0; i *= 10) {
    radixHandler(A, n, i);
  }
}

/**
 * Sort an array based on the recurrence of each digit
 *
 * @param A       Array to be sorted
 * @param n       Array size
 * @param pos     Value used to evaluate each digit of the numbers
 */
void radixHandler(int* A, int n, int pos) {
  // Count array
  int count[10] = { 0 };

  // Count the frequency of each digit separately
  for (int i = 0; i < n; i++) {
    count[(A[i] / pos) % 10]++;
  }

  // Create the histogram to generate the results
  for (int i = 1; i < 10; i++) {
    count[i] = count[i] + count[i - 1];
  }

  // Stores the results in a temporal array
  int results[n];
  for (int i = n - 1; i >= 0; i--) {
    results[--count[(A[i] / pos) % 10]] = A[i];
  }

  // Replace the array
  for (int i = 0; i < n; i++) {
    A[i] = results[i];
  }
}

/**
 * Search the max value contained in the given array
 *
 * @param A   Array to be searched
 * @param n   Array's size
 * @return    Founded max value
 */
int getMax(const int* A, int n) {
  int max = INT32_MIN;
  for(int i = 0; i < n; i++) {
    if (A[i] > max) {
      max = A[i];
    }
  }
  return max;
}


