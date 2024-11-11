#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <map>
#include <vector>


void shakerSort(int* arr, int N) {
    // B1
    int left = 0;
    int right = N - 1;

    // B2
    int t;

    do {
        t = 0;

        // Проход как в пузырьковой сортировке
        for (int j = left; j < right; j++) {
            // B3
            if (arr[j] > arr[j + 1]) {
                int k = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = k;

                t = j;
            }
        }
        // B4
        right = t;

        // Проход справа налево
        for (int j = right; j > left; j--) {
            if (arr[j] < arr[j - 1]) {
                int k = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = k;
                t = j;
            }
        }

        left = t;

    } while (left < right);
}


void bubbleSort(int* arr, int N) {
    // B1
    int bound = N - 1;
    // B2
    int t;
    do {
        t = 0;
        for (int j = 0; j < bound; j++) {
            // B3
            if (arr[j] > arr[j + 1]) {
                int k = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = k;

                t = j;
            }
        }
        // B4
        bound = t;
    } while (t != 0);
}

void writeArrayToFile(const int* arr, int N, const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing.\n";
        return;
    }

    for (int i = 0; i < N; ++i) {
        outfile << arr[i] << std::endl;
    }
    outfile.close();
    std::cout << "Sorted array written to " << filename << "\n";
}

bool loadArrayFromFile(int*& arr, int& N, const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error: Failed to open file " << filename << std::endl;
        return false;
    }

    std::vector<int> values;
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int number;
        while (iss >> number) {
            values.push_back(number);
        }
    }

    infile.close();

    if (values.empty()) {
        std::cerr << "Error: File " << filename << " is empty or contains invalid data.\n";
        return false;
    }

    N = values.size();

    arr = new int[N];
    std::copy(values.begin(), values.end(), arr);

    return true;
}

bool isSorted(const int* arr, int N) {
    for (int i = 1; i < N; ++i) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int N;
    int* arr = nullptr;

    std::map<int, std::string> files = {
        {16, "d16.txt"},
        {100, "d100.txt"},
        {500, "d500.txt"},
        {1000, "d1000.txt"},
        {5000, "d5000.txt"}
    };

    while (true) {
        int fileChoice;
        std::cout << "Choose the number of elements in the file (16, 100, 500, 1000, 5000): ";
        std::cin >> fileChoice;

        if (files.find(fileChoice) == files.end()) {
            std::cerr << "Error: Invalid choice. Available options are 16, 100, 500, 1000, 5000.\n";
            return 1;
        }

        if (!loadArrayFromFile(arr, N, files[fileChoice])) {
            return 1;
        }

        int choice;
        std::cout << "Choose sorting method:\n";
        std::cout << "1. shakerSort\n";
        std::cout << "2. qsort\n";
        std::cout << "3. bubbleSort\n";
        std::cout << "4. exit\n";
        std::cin >> choice;

        std::chrono::time_point<std::chrono::system_clock> start, end;

        switch (choice) {
        case 1:
            start = std::chrono::high_resolution_clock::now();
            shakerSort(arr, N);
            break;
        case 2:
            start = std::chrono::high_resolution_clock::now();
            std::sort(arr, arr + N);
            break;
        case 3:
            start = std::chrono::high_resolution_clock::now();
            bubbleSort(arr, N);
            break;
        case 4:
            delete[] arr;
            return 0;
        default:
            std::cerr << "Error: Invalid sorting choice.\n";
            delete[] arr;
            return 1;
        }

        end = std::chrono::high_resolution_clock::now();
        long duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        if (isSorted(arr, N)) {
            std::cout << "Array is correctly sorted.\n";
            for (int i = 0; i < 16; ++i) {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
            writeArrayToFile(arr, N, "../sorted_array.txt");
        } else {
            std::cerr << "Error: Array is not sorted correctly.\n";
        }

        std::cout << "Sorting time: " << duration << " microseconds\n";

        delete[] arr;
    }
}