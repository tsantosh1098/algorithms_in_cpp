#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>


/*

Radix Sort is a linear time, non-comparative sorting algorithm that works by distributing elements into buckets according to their individual digits. 
It sorts the elements by processing the digits from the least significant to the most significant. 

1. Time Complexity:
   - Radix Sort has a time complexity of O(nk), where n is the number of elements in the input array and k is the maximum number of digits in the largest number.
   - The k factor arises from the number of passes needed to sort the elements based on each digit place (units, tens, hundreds, etc.).
   - Radix Sort is a linear time sorting algorithm, and its performance is often better than O(n log n) for certain types of datasets, especially when k is not very large compared to n.

2. Space Complexity:
   - Radix Sort has a space complexity of O(n + k), where n is the number of elements in the input array and k is the maximum number of digits in the largest number.
   - The space complexity is determined by the additional count array used in the counting sort subroutine and the output array.
   - The count array has a size of 10 (for base 10 digits), and the output array has the same size as the input array.

Additional Details:

- Time Complexity Analysis:
  - The main loop in the `radixSort` function iterates through each digit place, performing counting sort for each pass.
  - The counting sort subroutine processes each element once for each digit place, contributing to the O(nk) time complexity.

- Space Complexity Analysis:
  - The additional space used by the algorithm includes the count array and the output array.
  - The count array has a fixed size of 10 (for base 10 digits), and the output array has the same size as the input array.
  - Therefore, the space complexity is O(n + k).

*/
// Function to find the maximum number in the array
int findMax(const std::vector<int>& arr) {
    return *std::max_element(arr.begin(), arr.end());
}

// Function to print an array
void printArray(const std::vector<int>& arr);

// Using counting sort as a subroutine for radix sort
void countingSort(std::vector<int>& arr, int exp) {
    const int n = arr.size();
    std::vector<int> output(n);
    std::vector<int> count(10, 0);

    // Count the occurrences of each digit at the current place value
    for (int i_itr = 0; i_itr < n; i_itr++) {
        count[(arr[i_itr] / exp) % 10]++;
    }

    // Update count[i] to store the cumulative count of elements with digit i
    for (int i_itr = 1; i_itr < 10; i_itr++) {
        count[i_itr] += count[i_itr - 1];
    }

    // Build the output array using the count array
    for (int i_itr = n - 1; i_itr >= 0; i_itr--) {
        output[count[(arr[i_itr] / exp) % 10] - 1] = arr[i_itr];
        count[(arr[i_itr] / exp) % 10]--;
    }

    // Copy the sorted elements back to the original array
    for (int i_itr = 0; i_itr < n; i_itr++) {
        arr[i_itr] = output[i_itr];
    }
}

// Radix Sort function
void radixSort(std::vector<int>& arr) {
    int maxElement = findMax(arr);

    // Perform counting sort for every digit place (1, 10, 100, ...)
    for (int exp = 1; maxElement / exp > 0; exp *= 10) {
        countingSort(arr, exp);
    }
}

// Function to print an array
void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    const char* filename = "../input_sort.txt";
    std::ifstream inputFile(filename);

    if (!inputFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    int n;
    inputFile >> n;

    std::vector<int> arr;
    int num;
    while(inputFile >> num){
        arr.push_back(num);
    }

    inputFile.close();

    std::cout << "Unsorted array: ";
    printArray(arr);

    // Measure the execution time
    auto start = std::chrono::high_resolution_clock::now();
    radixSort(arr);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Sorted array: ";
    printArray(arr);
    std::cout << "Time taken: " << duration.count() << " nanoseconds" << std::endl;

    return 0;
}
