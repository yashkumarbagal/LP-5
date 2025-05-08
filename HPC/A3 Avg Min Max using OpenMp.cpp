#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <iomanip>  // for setprecision

using namespace std;

void calculate_min_max_avg_sequential(int *a, int n, int &min, int &max, double &avg)
{
    min = a[0];
    max = a[0];
    double sum = 0;

    // Sequential calculation for min, max, and sum
    for (int i = 0; i < n; i++)
    {
        if (a[i] < min)
            min = a[i];
        if (a[i] > max)
            max = a[i];
        sum += a[i];
    }

    avg = sum / n;
}

void calculate_min_max_avg_parallel(int *a, int n, int &min, int &max, double &avg)
{
    min = a[0];
    max = a[0];
    double sum = 0;

    // Parallel calculation for min, max, and sum
    #pragma omp parallel for reduction(min: min) reduction(max: max) reduction(+: sum)
    for (int i = 0; i < n; i++)
    {
        if (a[i] < min)
            min = a[i];
        if (a[i] > max)
            max = a[i];
        sum += a[i];
    }

    avg = sum / n;
}

void print_array(int *a, int n)
{
    cout << "\nArray elements: ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

int main()
{
    int *a, n, choice, min, max;
    double avg;

    cout << "\nChoose the method for calculation: ";
    cout << "\n1. Sequential Calculation (Min, Max, Avg)";
    cout << "\n2. Parallel Calculation (Min, Max, Avg)";
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
            a[i] = rand() % 1000; // Random values between 0 and 999

        // Print the array elements
        print_array(a, n);

        // Start the timer using OpenMP high precision timer
        double start_time = omp_get_wtime();

        // Call the appropriate function based on user choice
        if (choice == 1)
            calculate_min_max_avg_sequential(a, n, min, max, avg);
        else
            calculate_min_max_avg_parallel(a, n, min, max, avg);

        // Stop the timer
        double end_time = omp_get_wtime();

        // Calculate time in microseconds
        double time_microsec = (end_time - start_time) * 1e6;

        // Output the results
        cout << "\nMinimum value: " << min;
        cout << "\nMaximum value: " << max;
        cout << "\nAverage value: " << fixed << setprecision(2) << avg;
        cout << "\nExecution time: " << time_microsec << " microseconds" << endl;

        delete[] a;
    }
    else
    {
        cout << "Invalid choice! Exiting program..." << endl;
    }

    return 0;
}
