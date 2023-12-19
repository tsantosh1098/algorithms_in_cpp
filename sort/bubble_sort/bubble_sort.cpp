#include <iostream>
#include <fstream>
#include <chrono>

/*

Bubble Sort is a simple sorting algorithm that repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order.
Bubble Sort has a nested loop structure. In each pass, it compares and swaps elements, and the total number of passes required is roughly proportional to the square of the number of elements in the array. 
This makes Bubble Sort inefficient for large datasets.

1. Time Complexity:
   - Worst-case time complexity: O(n^2) - This occurs when the input array is in reverse order, and the algorithm requires maximum swapping in each pass.
   - Best-case time complexity: O(n) - This occurs when the array is already sorted, and the algorithm needs only one pass to recognize this.
   - Average-case time complexity: O(n^2) - On average, the algorithm performs quadratic comparisons and swaps.

2. Space Complexity:
   - Bubble Sort is an in-place sorting algorithm, meaning it doesn't require additional memory for sorting and operates directly on the input array.
   - The space complexity is O(1), which indicates constant space usage. The amount of extra memory used by the algorithm does not depend on the size of the input array.

*/

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void bubbleSort(int arr[], int n) {
    for (int i_itr = 0; i_itr < n - 1; i_itr++) {
        for (int j_itr = 0; j_itr < n - i_itr - 1; j_itr++) {
            if (arr[j_itr] > arr[j_itr + 1]) {
                swap(arr[j_itr], arr[j_itr + 1]);
            }
        }
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
    bubbleSort(arr, n);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Sorted array: ";
    printArray(arr, n);
    std::cout << "Time taken: " << duration.count() << " nanoseconds" << std::endl;

    return 0;
}
