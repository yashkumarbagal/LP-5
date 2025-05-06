#include<iostream>
#include<omp.h>
using namespace std;

void merge(int *a, int low, int mid, int high) {
    int *temp = new int[high - low + 1];
    int i = low, j = mid + 1, k = 0;

    while (i <= mid && j <= high) {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];
    while (j <= high)
        temp[k++] = a[j++];

    for (int i = low, k = 0; i <= high; ++i, ++k)
        a[i] = temp[k];

    delete[] temp;
}

void merge_sort_sequential(int *a, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        merge_sort_sequential(a, low, mid);
        merge_sort_sequential(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

void merge_sort_parallel(int *a, int low, int high) {
    if (low < high) {
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

int main() {
    int *a, n, choice;

    cout << "\nChoose the sorting method: ";
    cout << "\n1. Sequential Merge Sort";
    cout << "\n2. Parallel Merge Sort";
    cout << "\n3. Exit";
    cout << "\nEnter your choice: ";
    cin >> choice;

    if (choice == 1 || choice == 2) {
        cout << "\nEnter total number of elements: ";
        cin >> n;

        a = new int[n];
        cout << "Enter elements: ";
        for (int i = 0; i < n; i++)
            cin >> a[i];

        if (choice == 1)
            merge_sort_sequential(a, 0, n - 1);
        else
            merge_sort_parallel(a, 0, n - 1);

        cout << "\nSorted array: ";
        for (int i = 0; i < n; i++)
            cout << a[i] << " ";
        cout << endl;

        delete[] a;
    } else if (choice == 3) {
        cout << "Exiting the program..." << endl;
    } else {
        cout << "Invalid choice! Exiting program..." << endl;
    }

    return 0;
}

