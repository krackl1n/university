#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <map>
#include <vector>
#include <cmath>



void mergeListSort(int* arr, int N) {
    int* L = new int[N + 2];

    int s, p, t, q;

    //  L1
    L[0] = 1;
    L[N - 1] = 0;
    L[N + 1] = 2;

    for (int i = 1; i < N - 1; i++) {
        L[i] = - (i + 2);
    }

    do {
        //  L2
        s = 0;
        t = N + 1;
        p = L[s];
        q = L[t];

        if (q == 0) {
            break;
        }

        //  L3
        do {
            if (arr[p] <= arr[q]) {
                //  L4
                L[s] = (L[s] < 0) ? -abs(p) : abs(p);
                s = p;
                p = L[p];
                if (p > 0) {
                    continue;
                }

                //  L5
                L[s] = q;
                s = t;
                do {
                    t = q;
                    q = L[q];
                } while (q > 0);
            }
            else {
                //  L6
                L[s] = (L[s] < 0) ? -abs(q) : abs(q);
                s = q;
                q = L[q];

                if (q > 0) {
                    continue;
                }

                //  L7
                L[s] = p;
                s = t;
                do {
                    t = p;
                    p = L[p];
                } while (p > 0);
            }

            //  L8
            p = -p;
            q = -q;

            if (q != 0) {
                continue;
            }
            break;
        } while (true);

        L[s] = (L[s] < 0) ? -abs(p) : abs(p);
        if (std::signbit(L[s])) {
            L[t] = -0; // Присваиваем отрицательный ноль
        } else {
            L[t] = 0; // Присваиваем положительный ноль
        }



    } while (true);







    for (int i = 0; i < N + 2; i++) {
        std::cout << L[i] << " " << arr[i] << "\n";
    }

    delete[] L;
}


void straightTwoWayMergeSort1(int* arr, int N) {
    int* R = new int[2 * N];

    for (int i = 0; i < N; i++)
    {
        R[i] = arr[i];
    }

    //  S1 Начальная установка
    int i, j, k, l, d, q, r;
    int s = 1, p = 1;

    do {
        bool flag = false;
        s = 1 - s;
        // S2: Подготовка к просмотру
        if (s == 0) {
            i = 0;
            j = N - 1;
            k = N - 1;
            l = 2 * N;
        } else {
            i = N;
            j = 2 * N - 1;
            k = -1;
            l = N;
        }

        d = 1;
        q = p;
        r = p;


        while (true) {
            // S3
            if (R[i] <= R[j]) {
                // S4
                k += d;
                R[k] = R[i];

                // S5
                i += 1;
                q -= 1;

                if (q > 0) {
                    continue;
                }

                // S6
                do {
                    k += d;
                    if (k == l) {
                        // S13
                        flag = true;
                        break;
                    }
                    R[k] = R[j];

                    // S7
                    j -= 1;
                    r -= 1;
                }
                while (r > 0);

            }
            else {
                // S8
                k += d;
                R[k] = R[j];

                // S9
                j -= 1;
                r -= 1;
                if (r > 0) {
                    continue;
                }

                // S10
                do {
                    k += d;
                    if (k == l) {
                        // НА S13
                        flag = true;
                        break;
                    }
                    R[k] = R[i];

                    // На S11
                    i += 1;
                    q -= 1;
                }
                while (q > 0);
            }

            // S12
            if (!flag) {
                q = p;
                r = p;
                d = -d;
                std::swap(k, l);

                if (j - i < p) {
                    // На S10
                    do {
                        k += d;
                        if (k == l) {
                            // НА S13
                            break;
                        }
                        R[k] = R[i];

                        // На S11
                        i += 1;
                        q -= 1;
                    }
                    while (q > 0);
                }
                else {
                    // На S3
                    continue;
                }
            }

            // S13
            p *= 2;
            break;
        }
    }
    while (p < N);

    for (int m = 0; m < N; m++) {
        if (s == 1)
        {
            arr[m] = R[m];
        }
        else
        {
            arr[m] = R[m + N];
        }
    }

    delete[] R;
}

// Функция сортировки пузырьком
void bubbleSort(int* arr, int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
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
        std::cout << "1. straightTwoWayMergeSort\n";
        std::cout << "2. qsort\n";
        std::cout << "3. bubbleSort\n";
        std::cout << "4. exit\n";
        std::cin >> choice;

        std::chrono::time_point<std::chrono::system_clock> start, end;

        switch (choice) {
        case 1:
            start = std::chrono::high_resolution_clock::now();
            mergeListSort(arr, N);  // Функция, которую нужно реализовать
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
            writeArrayToFile(arr, N, "../sorted_array.txt");
        } else {
            std::cerr << "Error: Array is not sorted correctly.\n";
        }

        std::cout << "Sorting time: " << duration << " microseconds\n";

        delete[] arr;
    }
}