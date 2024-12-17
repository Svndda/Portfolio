//
// Copyright (c) 2024 Aaron Carmona Sanchez <aaroncz032@gmail.com>
//
#include <iostream>
#include <vector>
#include <random>

#include "Sort.hpp"

std::vector<int> generateRandomVector();
void printVector(std::vector<int> vector);

int main() {
  std::vector<int> vector = generateRandomVector();
  std::cout << "Original vector: ";
  printVector(vector);
  Sort::mergesort(vector);
  std::cout << "Sorted vector with selection:   ";
  printVector(vector);
  return 0;
}

std::vector<int> generateRandomVector() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dis(1, 100);

  std::vector<int> res(10);
  for (int& element : res) {
    element = dis(gen);
  }
  return res;
}

void printVector(std::vector<int> vector) {
  for (const int element : vector) {
    std::cout << element << " ";
  }
  std::cout << std::endl;
}
