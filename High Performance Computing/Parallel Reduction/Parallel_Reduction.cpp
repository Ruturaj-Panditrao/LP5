#include <omp.h>
#include <vector>
#include <chrono>
#include <iostream>
using namespace std;

// Prefer using omp_get_wtime()
// However, may face compiler version issues, so can use chrono as well
// It measures the clock ticks 
// To see difference in start and end times, use larger arrays of size 1e5 or more, can initialize them using rand()

void parallel_reduction_findMinimum(vector<int>&array)
{
    int n = array.size();
    int minvalue = array[0]; 
    // #pragma omp => indicates that it is an omp directive
    // parallel for => for-loop is parallelized across multiple threads
    // reduction(min:minvalue) => the reduction operation is finding minimum, and it is to be stored in minvalue

    // OpenMp divides the array into chunks
    // Each thread finds the minimum within its own chunk
    // Then in reduction phase, the overall minimum value is obtained
    // double start = omp_get_wtime();
    auto start = chrono::high_resolution_clock::now();
    #pragma omp parallel for reduction(min : minvalue)
    for(int i=0; i<n;i++)
    {
        if(array[i]<minvalue) minvalue=array[i];
    }
    // double end = omp_get_wtime();
    auto end = chrono::high_resolution_clock::now();
    cout<<"Parallel Reduction"<<endl;
    cout<<"Minimum Element : "<<minvalue<<endl;
    cout<<"Time Taken : "<<(end-start).count()<<endl;
}


void sequential_findMinimum(vector<int>&array)
{
    int n = array.size();
    int minvalue = array[0];
    // double start = omp_get_wtime();
    auto start = chrono::high_resolution_clock::now();
    for(int i=0; i<n;i++)
    {
        if(array[i]<minvalue) minvalue=array[i];
    }
    // double end = omp_get_wtime();
    auto end = chrono::high_resolution_clock::now();
    cout<<"Sequential Operation"<<endl;
    cout<<"Minimum Element : "<<minvalue<<endl;
    cout<<"Time Taken : "<<(end-start).count()<<endl;
}

void parallel_reduction_findMaximum(vector<int>&array)
{
    int n = array.size();
    int maxvalue = array[0];
    // double start = omp_get_wtime();
    auto start = chrono::high_resolution_clock::now();
    #pragma omp parallel for reduction(max : maxvalue)
    for(int i=0; i<n;i++)
    {
        if(array[i]>maxvalue) maxvalue=array[i];
    }
    // double end = omp_get_wtime();
    auto end = chrono::high_resolution_clock::now();
    cout<<"Parallel Reduction"<<endl;
    cout<<"Maximum Element : "<<maxvalue<<endl;
    cout<<"Time Taken : "<<(end-start).count()<<endl;
}

void sequential_findMaximum(vector<int>&array)
{
    int n = array.size();
    int maxvalue = array[0];
    // double start = omp_get_wtime();
    auto start = chrono::high_resolution_clock::now();
    for(int i=0; i<n;i++)
    {
        if(array[i]>maxvalue) maxvalue=array[i];
    }
    // double end = omp_get_wtime();
    auto end = chrono::high_resolution_clock::now();
    cout<<"Sequential Operation"<<endl;
    cout<<"Minimum Element : "<<maxvalue<<endl;
    cout<<"Time Taken : "<<(end-start).count()<<endl;
}

void sequential_findSum(vector<int>&array)
{
    int n = array.size();
    int sum = 0;
    // double start = omp_get_wtime();
    auto start = chrono::high_resolution_clock::now();
    for(int i=0; i<n;i++)
    {
       sum+=array[i];
    }
    // double end = omp_get_wtime();
    auto end = chrono::high_resolution_clock::now();
    cout<<"Sequential Operation"<<endl;
    cout<<"Sum : "<<sum<<endl;
    cout<<"Time Taken : "<<(end-start).count()<<endl;
}

void parallel_reduction_findSum(vector<int>&array)
{
    int n = array.size();
    int sum = 0;
    // double start = omp_get_wtime();
    auto start = chrono::high_resolution_clock::now();
    #pragma omp parallel for reduction(+:sum)
    for(int i=0; i<n;i++)
    {
       sum+=array[i];
    }
    // double end = omp_get_wtime();
    auto end = chrono::high_resolution_clock::now();
    cout<<"Parallel Reduction"<<endl;
    cout<<"Sum : "<<sum<<endl;
    cout<<"Time Taken : "<<(end-start).count()<<endl;
}

void sequential_findAverage(vector<int>&array)
{
    int n = array.size();
    int sum = 0;
    // double start = omp_get_wtime();
    auto start = chrono::high_resolution_clock::now();
    for(int i=0; i<n;i++)
    {
       sum+=array[i];
    }
    double avg = sum/n;
    // double end = omp_get_wtime();
    auto end = chrono::high_resolution_clock::now();
    cout<<"Sequential Operation"<<endl;
    cout<<"Average : "<<avg<<endl;
    cout<<"Time Taken : "<<(end-start).count()<<endl;
}

void parallel_reduction_findAverage(vector<int>&array)
{
    int n = array.size();
    int sum = 0;
    // double start = omp_get_wtime();
    auto start = chrono::high_resolution_clock::now();
    #pragma omp parallel for reduction(+:sum)
    for(int i=0; i<n;i++)
    {
       sum+=array[i];
    }
    double avg = sum/n;
    // double end = omp_get_wtime();
    auto end = chrono::high_resolution_clock::now();
    cout<<"Parallel Reduction"<<endl;
    cout<<"Average : "<<avg<<endl;
    cout<<"Time Taken : "<<(end-start).count()<<endl;
}

int main()
{
    int n;
    cout<<"Enter Number of Elements : ";
    cin>>n;
    vector<int>array;
    // This is a sample for functionality 
    // You can take 1000 elements randomly and put them into the vector using rand()%10
    for(int i=0; i<n; i++)
    {
        cout<<"Enter Element : ";
        int ele;
        cin>>ele;
        array.push_back(ele);
    }
    
    cout<<"Finding the Minimum Element : "<<endl;
    sequential_findMinimum(array); cout<<endl;
    parallel_reduction_findMinimum(array); cout<<"\n\n";

    cout<<"Finding the Maximum Element : "<<endl;
    sequential_findMaximum(array); cout<<endl;
    parallel_reduction_findMaximum(array); cout<<"\n\n";

    cout<<"Finding the Sum of the Array : "<<endl;
    sequential_findSum(array); cout<<endl;
    parallel_reduction_findSum(array); cout<<"\n\n";

    cout<<"Finding the Average of the Array : n"<<endl;
    sequential_findAverage(array); cout<<endl;
    parallel_reduction_findAverage(array); cout<<"\n\n";
}