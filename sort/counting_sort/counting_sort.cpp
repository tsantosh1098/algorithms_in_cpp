#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <chrono>
using namespace std;

/*

1. Time Complexity:
   - Counting Sort has a time complexity of O(n + k), where n is the number of elements in the input array and k is the range of input values (the difference between the maximum and minimum values).
   - The algorithm performs well when the range of input values (k) is not significantly larger than the number of elements (n).
   - Counting Sort is a linear time sorting algorithm and is especially efficient for sorting integers within a limited range.

2. Space Complexity:
   - Counting Sort has a space complexity of O(k), where k is the range of input values.
   - The space complexity is determined by the count array used to store the frequency of each element in the input array.

Additional Details:-
- Time Complexity Analysis:
  - The first loop that counts the occurrences of each element in the input array takes O(n) time.
  - The second loop that updates the count array to store the cumulative count takes O(k) time.
  - The third loop that builds the sorted array using the count array also takes O(n) time.
  - Combining these steps, the overall time complexity is O(n + k).

- Space Complexity Analysis:
  - The space complexity is determined by the count array, which has a size proportional to the range of input values (k).
  - The space complexity is O(k).

Counting Sort is particularly useful when the range of input values is not significantly larger than the number of elements. 
It is a stable, non-comparative sorting algorithm that can be efficient for certain types of datasets, especially when dealing with integers or small key ranges.

*/
void countingSort(std::vector<int>& arr) {
    // Find the maximum element in the array
    int maxElement = *max_element(arr.begin(), arr.end());

    // Create a count array to store the count of each element
    std::vector<int> count(maxElement + 1, 0);

    // Count the occurrences of each element in the input array
    for (int num : arr) {
        count[num]++;
    }

    // Update the count array to store the cumulative count
    for (int i_itr = 1; i_itr <= maxElement; i_itr++) {
        count[i_itr] += count[i_itr - 1];
    }

    // Create a temporary array to store the sorted elements
    std::vector<int> output(arr.size());

    // Build the output array using the count array
    for (int i_itr = arr.size() - 1; i_itr >= 0; i_itr--) {
        output[count[arr[i_itr]] - 1] = arr[i_itr];
        count[arr[i_itr]]--;
    }

    // Copy the sorted elements back to the original array
    for (int i_itr = 0; i_itr < arr.size(); i_itr++) {
        arr[i_itr] = output[i_itr];
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
    countingSort(arr);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Sorted array: ";
    printArray(arr);
    std::cout << "Time taken: " << duration.count() << " nanoseconds" << std::endl;

    return 0;
}
