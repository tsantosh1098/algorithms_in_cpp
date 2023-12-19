#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>



/*

Merge Sort consistently achieves a time complexity of O(n log n) due to its divide-and-conquer approach. 
It recursively divides the input array into smaller halves until it reaches subarrays of size 1, then merges them back in a sorted manner.
Merge Sort is an out-of-place algorithm, meaning it does not sort the array in its original memory location. Instead, it creates temporary arrays during the merging process, 
and the additional space required is directly proportional to the size of the input array.

1. Time Complexity:
   - Worst-case time complexity: O(n log n) - This occurs when the input array needs to be divided into log n levels, and each level requires O(n) operations to merge the sorted halves.
   - Best-case time complexity: O(n log n) - Merge Sort always divides the array into two halves, regardless of the input order.
   - Average-case time complexity: O(n log n) - The average-case time complexity is the same as the worst-case, as the algorithm consistently divides and conquers.


2. Space Complexity:
   - Merge Sort has a space complexity of O(n) due to the additional space required for the temporary arrays during the merging process.
   - The additional space is needed to store the two halves of the array being merged.

*/
void merge(std::vector<int>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Create temporary arrays
    std::vector<int> leftArray(n1);
    std::vector<int> rightArray(n2);

    // Copy data to temporary arrays leftArray[] and rightArray[]
    for (int i_itr = 0; i_itr < n1; i_itr++)
        leftArray[i_itr] = arr[left + i_itr];
    for (int j_itr = 0; j_itr < n2; j_itr++)
        rightArray[j_itr] = arr[middle + 1 + j_itr];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = left; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            arr[k] = leftArray[i];
            i++;
        } else {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArray[], if there are any
    while (i < n1) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArray[], if there are any
    while (j < n2) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        // Same as (left+right)/2, but avoids overflow for large left and right
        int middle = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        // Merge the sorted halves
        merge(arr, left, middle, right);
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
    mergeSort(arr, 0, n-1);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Sorted array: ";
    printArray(arr);
    std::cout << "Time taken: " << duration.count() << " nanoseconds" << std::endl;

    return 0;
}
