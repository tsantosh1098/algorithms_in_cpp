#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>


/*
Quick Sort's time complexity is dominated by the partitioning step, and its average-case time complexity is O(n log n) due to the balanced partitions. 
However, in the worst case, it can degrade to O(n^2), making it less suitable for certain datasets.
Quick Sort is an in-place sorting algorithm, meaning it doesn't require additional memory proportional to the size of the input array. 
However, the space complexity is influenced by the depth of the recursive call stack.

1. Time Complexity:
   - Worst-case time complexity: O(n^2) - This occurs when the chosen pivot is always the smallest or largest element in the array, resulting in unbalanced partitions.
   - Best-case time complexity: O(n log n) - This occurs when the chosen pivot consistently divides the array into balanced partitions.
   - Average-case time complexity: O(n log n) - On average, Quick Sort demonstrates good performance due to its divide-and-conquer approach.

2. Space Complexity:
   - Quick Sort has a space complexity of O(log n) for the recursive call stack during the sorting process.
   - In the best case, the space complexity is O(log n) because the algorithm partitions the array in-place.
   - In the worst case, the space complexity can be O(n) due to the unbalanced partitions, requiring a deep recursive call stack.

*/


// Function to partition the array and return the index of the pivot
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Choose the last element as the pivot
    int i_itr = low - 1; // Index of smaller element

    for (int j_itr = low; j_itr < high; j_itr++) {
        // If the current element is smaller than or equal to the pivot
        if (arr[j_itr] <= pivot) {
            i_itr++;
            std::swap(arr[i_itr], arr[j_itr]);
        }
    }

    std::swap(arr[i_itr + 1], arr[high]);
    return i_itr + 1;
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        // Partition the array and get the pivot index
        int pivotIndex = partition(arr, low, high);

        // Recursively sort the sub-arrays
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
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
    quickSort(arr, 0, n-1);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Sorted array: ";
    printArray(arr);
    std::cout << "Time taken: " << duration.count() << " nanoseconds" << std::endl;

    return 0;
}
