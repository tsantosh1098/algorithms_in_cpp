#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>


/*

Shell Sort is an in-place sorting algorithm that is an extension of the Insertion Sort algorithm. 
It works by sorting elements that are distant from each other and progressively reducing the gap between elements to be compared

1. Time Complexity:
   - The time complexity of Shell Sort depends on the sequence used to determine the gap.
   - Worst-case time complexity: O(n^2) - This occurs for certain sequences, such as the original Shell's sequence.
   - Best-case time complexity: O(n log n) - This occurs for certain sequences with a more efficient gap sequence, like the Pratt sequence.
   - Average-case time complexity: Depends on the gap sequence but generally better than O(n^2). It is often considered to be around O(n^(3/2)) or better, depending on the chosen gap sequence.

The choice of the gap sequence significantly influences the performance of Shell Sort. Some sequences, like the Sedgewick sequence or the Pratt sequence, lead to better average-case performance compared to others. 
The Pratt sequence, in particular, achieves O(n log n) average-case time complexity.

2. Space Complexity:
   - Shell Sort is an in-place sorting algorithm, meaning it does not use additional memory proportional to the size of the input array.
   - The space complexity is O(1), indicating constant space usage.

*/


void shellSort(std::vector<int>& arr) {
    int n = arr.size();

    // Start with a large gap and reduce it until gap becomes 1
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements arr[0..gap-1] are already in gapped order.
        // Keep adding one more element until the entire array is gap sorted.
        for (int i_itr = gap; i_itr < n; i_itr++) {
            // Add arr[i] to the elements that have been gap sorted
            // Save arr[i] in temp and make a hole at position i
            int temp = arr[i_itr];

            // Shift the elements in the sorted part to make room for temp
            int j_itr;
            for (j_itr = i_itr; j_itr >= gap && arr[j_itr - gap] > temp; j_itr -= gap) {
                arr[j_itr] = arr[j_itr - gap];
            }

            // Put temp (the original arr[i]) in its correct location
            arr[j_itr] = temp;
        }
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
    shellSort(arr);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Sorted array: ";
    printArray(arr);
    std::cout << "Time taken: " << duration.count() << " nanoseconds" << std::endl;

    return 0;
}
