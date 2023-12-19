#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

/*

Heap Sort's time complexity is determined by two main steps:
   - Building the heap, which takes O(n) time.
   - Performing n heapify operations (extracting elements from the heap), each taking O(log n) time.   
   The dominant term is O(n log n).

1. Time Complexity:
   - Worst-case time complexity: O(n log n) - This is the same as the average-case time complexity. Heap Sort consistently performs well, regardless of the input distribution.
   - Best-case time complexity: O(n log n) - Same as the worst and average case. The algorithm always builds and performs heapify operations, leading to a consistent time complexity.
   - Average-case time complexity: O(n log n) - Heap Sort has a stable time complexity of O(n log n) due to the inherent structure of the heap.

Heap Sort uses the input array itself to build the heap and perform the sorting, without requiring additional memory proportional to the size of the input. 
This in-place characteristic contributes to its efficient use of memory.

2. Space Complexity:
   - Heap Sort has a space complexity of O(1) for in-place sorting. The algorithm does not require additional memory proportional to the input size, making it an in-place sorting algorithm.

*/


void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i; // Initialize largest as the root
    int left = 2 * i + 1; // Left child
    int right = 2 * i + 2; // Right child

    // If the left child is larger than the root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // If the right child is larger than the largest so far
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If the largest is not the root
    if (largest != i) {
        std::swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();

    // Build a max heap (rearrange array)
    for (int i_itr= n / 2 - 1; i_itr >= 0; i_itr--) {
        heapify(arr, n, i_itr);
    }

    // One by one extract elements from the heap
    for (int i_itr = n - 1; i_itr > 0; i_itr--) {
        // Move the current root to the end
        std::swap(arr[0], arr[i_itr]);

        // Call max heapify on the reduced heap
        heapify(arr, i_itr, 0);
    }
}

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
    heapSort(arr);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Sorted array: ";
    printArray(arr);
    std::cout << "Time taken: " << duration.count() << " nanoseconds" << std::endl;

    return 0;
}
