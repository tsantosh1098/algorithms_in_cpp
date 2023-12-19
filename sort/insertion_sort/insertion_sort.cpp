#include <iostream>
#include <fstream>
#include <chrono>


/*

Insertion Sort is adaptive, meaning it performs better on partially sorted arrays. In the best-case scenario, where the array is already sorted, the time complexity becomes linear.
The main operations in Insertion Sort involve comparing and shifting elements. In the worst case, for each element, it may need to compare and shift elements up to the beginning of the array, 
resulting in quadratic time complexity.


1. Time Complexity:
   - Worst-case time complexity: O(n^2) - This occurs when the input array is in reverse order, and the algorithm requires maximum comparisons and shifts in each pass.
   - Best-case time complexity: O(n) - This occurs when the input array is already sorted, and the algorithm only needs to perform comparisons without any shifts.
   - Average-case time complexity: O(n^2) - On average, the algorithm performs quadratic comparisons and shifts.

2. Space Complexity:
   - Insertion Sort is an in-place sorting algorithm, meaning it doesn't require additional memory for sorting and operates directly on the input array.
   - The space complexity is O(1), indicating constant space usage. The amount of extra memory used by the algorithm does not depend on the size of the input array.

*/
void insertionSort(int arr[], int n) {
    for (int i_itr = 1; i_itr < n; i_itr++) {
        int key = arr[i_itr];
        int j_itr = i_itr - 1;

        // Move elements of arr[0..i-1] that are greater than key to one position ahead of their current position
        while (j_itr >= 0 && arr[j_itr] > key) {
            arr[j_itr + 1] = arr[j_itr];
            j_itr = j_itr - 1;
        }

        arr[j_itr + 1] = key;
    }
}

void printArray(int arr[], int size) {
    for (int i_itr = 0; i_itr < size; i_itr++) {
        std::cout << arr[i_itr] << " ";
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

    int arr[n];
    for (int i_itr = 0; i_itr < n; i_itr++) {
        inputFile >> arr[i_itr];
    }

    inputFile.close();

    std::cout << "Unsorted array: ";
    printArray(arr, n);

    // Measure the execution time
    auto start = std::chrono::high_resolution_clock::now();
    insertionSort(arr, n);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Sorted array: ";
    printArray(arr, n);
    std::cout << "Time taken: " << duration.count() << " nanoseconds" << std::endl;

    return 0;
}
