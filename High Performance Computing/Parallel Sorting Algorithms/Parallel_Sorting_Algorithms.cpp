#include <omp.h>
#include <chrono>
#include <vector>
#include <iostream>
using namespace std;

// Time difference in sequential and parallel operations is noticeable only on huge arrays with size > 1e5

void sequentialBubbleSort(vector<int>arr, int n)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                swap(arr[j],arr[j+1]);
            }
        }
    }
}

void parallelBubbleSort(vector<int>arr, int n)
{
    for(int i=0; i<n; i++)
    {
        #pragma omp parallel for
        for(int j=0; j<n-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                swap(arr[j],arr[j+1]);
            }
        }
    }
}



void merge(vector<int>arr, int l, int m, int r)
{
    int n1 = m-l+1;
    int n2 = r-m;

    int left[n1];
    int right[n2];
    
    // Initialize left and right arrays that are to be merged

    for(int i=0; i<n1; i++)
    {
        left[i] = arr[l+i];
    }

    for(int i=0; i<n2; i++)
    {
        right[i] = arr[m+1+i];
    }   

    int i=0; // Left array pointer
    int j=0; // Right array pointer
    int k=l; // Final array pointer

    while(i<n1 && j<n2)
    {
        if(left[i]<=right[j])
        {
            arr[k]=left[i];
            i++;
            k++;
        }
        else
        {
            arr[k]=right[j];
            j++;
            k++;
        }
    }

    while(i<n1)
    {
        arr[k]=left[i];
        i++;
        k++;
    }

    while(j<n2)
    {
        arr[k]=right[j];
        j++;
        k++;
    }

}

void sequentialMergeSort(vector<int>arr, int l, int r)
{
    
    if(l<r)
    {
        int m = l + (r-l)/2;
        sequentialMergeSort(arr,l,m);
        sequentialMergeSort(arr,m+1,r);
        merge(arr,l,m,r);
    }
}


void parallelMergeSort(vector<int>arr, int l, int r)
{
    
    if(l<r)
    {
        int m = l + (r-l)/2;
        #pragma omp parallel sections
        {
            #pragma omp section
        parallelMergeSort(arr,l,m);
            #pragma omp section
        parallelMergeSort(arr,m+1,r);
        }
        merge(arr,l,m,r);
    }
}

void printArray(vector<int>arr, int n)
{
    for(int i=0; i<n; i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}
int main()
{
   int n = 1000;
   vector<int>arr;

   for(int i=0; i<n; i++)
   {
     arr.push_back(rand()%10);
   }

    cout<<"Array : ";
    printArray(arr,n);
    cout<<"Bubble Sort Output : "<<endl;
    cout<<"Sequential Bubble Sort Output : "<<endl;
    auto start = chrono::high_resolution_clock::now();
    sequentialBubbleSort(arr,n);
    auto end = chrono::high_resolution_clock::now();
    printArray(arr,n);
    cout<<"Time taken in Clock Ticks : "<<(end-start).count()<<endl;

    cout<<"Paralle Bubble Sort Output : "<<endl;
     start = chrono::high_resolution_clock::now();
    parallelBubbleSort(arr,n);
     end = chrono::high_resolution_clock::now();
    printArray(arr,n);
    cout<<"Time taken in Clock Ticks : "<<(end-start).count()<<endl;

    cout<<"Sequential Merge Sort Output : "<<endl;
     start = chrono::high_resolution_clock::now();
    sequentialMergeSort(arr,0,n-1);
     end = chrono::high_resolution_clock::now();
    printArray(arr,n);
    cout<<"Time taken in Clock Ticks : "<<(end-start).count()<<endl;

    cout<<"Parallel Merge Sort Output : "<<endl;
     start = chrono::high_resolution_clock::now();
    parallelMergeSort(arr,0,n-1);
     end = chrono::high_resolution_clock::now();
    printArray(arr,n);
    cout<<"Time taken in Clock Ticks : "<<(end-start).count()<<endl;


}