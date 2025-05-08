#include <iostream>
#include <stdlib.h>
#include <omp.h>
#include <ctime>     // For clock()
#include <iomanip>   // For setprecision

using namespace std;

void bubble_sequential(int *, int);
void bubble_parallel(int *, int);
void swap(int &, int &);

void bubble_sequential(int *a, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - 1; j++)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
}

void bubble_parallel(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        int first = i % 2;
#pragma omp parallel for shared(a, first)
        for (int j = first; j < n - 1; j += 2)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
    }
}

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int *a, n, choice;

    cout << "\nChoose the sorting method: ";
    cout << "\n1. Sequential Bubble Sort";
    cout << "\n2. Parallel Bubble Sort";
    cout << "\nEnter your choice: ";
    cin >> choice;

    if (choice == 1 || choice == 2)
    {
        cout << "\nEnter total number of elements: ";
        cin >> n;

        a = new int[n];

        // Auto-fill with random values
        srand(time(0));
        for (int i = 0; i < n; i++)
            a[i] = rand() % 1000;

        // Print unsorted array
        cout << "\nUnsorted array: ";
        for (int i = 0; i < n; i++)
            cout << a[i] << " ";
        cout << endl;

        // Start timing
        clock_t start_time = clock();

        if (choice == 1)
            bubble_sequential(a, n);
        else
            bubble_parallel(a, n);

        // End timing
        clock_t end_time = clock();

        // Calculate time in microseconds
        double time_microsec = 1.0 * (end_time - start_time) * 1e6 / CLOCKS_PER_SEC;

        // Print sorted array
        cout << "\nSorted array: ";
        for (int i = 0; i < n; i++)
            cout << a[i] << " ";
        cout << endl;

        // Display execution time
        cout << fixed << setprecision(2);
        cout << "Execution time: " << time_microsec << " microseconds" << endl;

        delete[] a;
    }
    else
    {
        cout << "Invalid choice! Exiting program..." << endl;
    }

    return 0;
}
