//
// Copyright (c) 2024 Aaron Carmona Sanchez <aaroncz032@gmail.com>
//
#ifndef SORT_HPP
#define SORT_HPP
// NOLINT(build/header_guard)

#include <algorithm>
#include <random>
#include <vector>

namespace Sort {

  /**
   * Sort the given vector using the merge sort algorithm
   *
   * @param vector  Reference to the vector to be sorted
   */
  void mergesort(std::vector<int>& vector);

  /**
   * Sort the given array with the merge algorithm
   *
   * @param vector  Vector to be sorted.
   */
  void insertion(std::vector<int>& vector);

  /**
   * Sort the given vector with the selection algorithm
   *
   * @param vector  Vector to be sorted
   */
  void selection(std::vector<int>& vector);

  /**
   * Sort the given vector with the merge algorithm
   *
   * @param vector  Vector to be sorted
   */
  void mergesort(std::vector<int>& vector);

  /**
   * Sort the given array with the heap algorithm
   *
   * @param A   Array to be sorted
   * @param n   Array's size
   */
  void heapsort(int *A, int n);

  /**
   * Sort the given array with the quick algorithm
   *
   * @param A   Array to be sorted
   * @param n   Array's size
   */
  void quicksort(int *A, int start, int end);

  /**
   * Sort the given array with the radix algorithm
   *
   * @param A   Array to be sorted
   * @param n   Array's size
   */
  void radixsort(int *A, int n);
}

#endif //SORT_HPP
