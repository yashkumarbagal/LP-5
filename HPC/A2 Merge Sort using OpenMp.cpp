#include <iostream>
#include <stdlib.h>
#include <omp.h>
#include <ctime>
#include <iomanip>

using namespace std;

void merge(int *a, int low, int mid, int high)
{
    int i = low, j = mid + 1, k = 0;
    int *temp = new int[high - low + 1];

    while (i <= mid && j <= high)
    {
        if (a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];

    while (j <= high)
        temp[k++] = a[j++];

    for (i = low, k = 0; i <= high; i++, k++)
        a[i] = temp[k];

    delete[] temp;
}

void merge_sort_sequential(int *a, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        merge_sort_sequential(a, low, mid);
        merge_sort_sequential(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

void merge_sort_parallel(int *a, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

#pragma omp parallel sections
        {
#pragma omp section
            merge_sort_parallel(a, low, mid);

#pragma omp section
            merge_sort_parallel(a, mid + 1, high);
        }

        merge(a, low, mid, high);
    }
}

int main()
{
    int *a, n, choice;

    cout << "\nChoose the sorting method: ";
    cout << "\n1. Sequential Merge Sort";
    cout << "\n2. Parallel Merge Sort";
    cout << "\nEnter your choice: ";
    cin >> choice;

    if (choice == 1 || choice == 2)
    {
        cout << "\nEnter total number of elements: ";
        cin >> n;

        a = new int[n];

        // Generate random array
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
            merge_sort_sequential(a, 0, n - 1);
        else
            merge_sort_parallel(a, 0, n - 1);

        // End timing
        clock_t end_time = clock();

        // Calculate time in microseconds
        double time_microsec = 1.0 * (end_time - start_time) * 1e6 / CLOCKS_PER_SEC;

        // Print sorted array
        cout << "\nSorted array: ";
        for (int i = 0; i < n; i++)
            cout << a[i] << " ";
        cout << endl;

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
