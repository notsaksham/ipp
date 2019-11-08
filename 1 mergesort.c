#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void merge(int arr[],int l,int m,int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j]; //m+one+j
    i = 0;
    j = 0;
    k = l;// it is el no one
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void serial_merge_Sort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        serial_merge_Sort(arr, l, m);
        serial_merge_Sort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void parallel_merge_sort(int a[],int n,int left,int right,int threads){
    if (threads == 1){
        // Serialized Merge Sort
        serial_merge_Sort(a,left,right);
    }else if (threads > 1){
        int mid = (left+right)/2;
        #pragma omp parallel sections firstprivate(mid)
        {
            #pragma omp section
                parallel_merge_sort(a,n,left,mid,threads/2);
            #pragma omp section
                parallel_merge_sort(a,n,mid+1,right,threads-threads/2);
        }
        merge(a,left,mid,right);
    }
}

int main()
{
   int n;
   printf("Size : ");
   scanf("%d",&n);
   int arr[n];
   for(int i=0;i<n;i++)
   {
       arr[i] =rand()%100;
   }
    double start = omp_get_wtime();
    omp_set_num_threads(2);
    parallel_merge_sort(arr,n,0,n-1,2);
    double end = omp_get_wtime();
    printf("Sorted List\n");
    for (int i=0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    printf("Execution Time : %g",end-start);
    return 0;
}
