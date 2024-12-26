//
// Copyright (c) 2024 Aaron Carmona Sanchez <aaroncz032@gmail.com>
//
#ifndef SORT_HPP
#define SORT_HPP

#include <utility>
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
 * Sort the given vector using the heapsort algorithm
 *
 * @param vector  Reference to the vector to be sorted
 */
void heapsort(std::vector<int>& vector);

/**
 * Sort the given vector using the quicksort algorithm
 *
 * @param vector  Reference to the vector to be sorted
 */
void quicksort(std::vector<int>& vector);

/**
 * Sort the given vector using the radix sort algorithm
 *
 * @param vector  Reference to the vector to be sorted
 */
void radixsort(std::vector<int>& vector);
}  // namespace Sort

#endif  // SORT_HPP
