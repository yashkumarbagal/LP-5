#include <iostream>
#include <omp.h>
#include <limits>
using namespace std;

// Sequential computation of min, max, sum, and average
void compute_sequential(int* arr, int n) {
    int min_val = INT_MAX;
    int max_val = INT_MIN;
    long long sum = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
        sum += arr[i];
    }

    double avg = static_cast<double>(sum) / n;

    cout << "\n--- Sequential Output ---\n";
    cout << "Minimum: " << min_val << endl;
    cout << "Maximum: " << max_val << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << avg << endl;
}

// Parallel computation using OpenMP reduction
void compute_parallel(int* arr, int n) {
    int min_val = INT_MAX;
    int max_val = INT_MIN;
    long long sum = 0;

    // Parallel loop with reduction for min, max, and sum
    #pragma omp parallel for reduction(min:min_val) reduction(max:max_val) reduction(+:sum)
    for (int i = 0; i < n; ++i) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
        sum += arr[i];
    }

    double avg = static_cast<double>(sum) / n;

    cout << "\n--- Parallel Output ---\n";
    cout << "Minimum: " << min_val << endl;
    cout << "Maximum: " << max_val << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << avg << endl;
}

int main() {
    int n, choice;
    cout << "Enter number of elements: ";
    cin >> n;

    int* arr = new int[n];
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    // Menu to choose execution method
    cout << "\nChoose execution type:";
    cout << "\n1. Sequential";
    cout << "\n2. Parallel (OpenMP)";
    cout << "\n3. Exit";
    cout << "\nEnter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            compute_sequential(arr, n);
            break;
        case 2:
            compute_parallel(arr, n);
            break;
        case 3:
            cout << "Exiting the program..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
    }

    delete[] arr;
    return 0;
}

