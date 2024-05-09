#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#define MAX_SIZE 100000
#define ITERATIONS 26
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void copyArray(int src[], int dest[], int n)
{
    for (int i = 0; i < n; i++)
    {
        dest[i] = src[i];
    }
}

void insSort(int a[], int n) // Insertion Sort
{
    int i, j, key;
    for (i = 2; i <= n; i++)
    {
        key = a[i];
        for (j = i - 1; j > 0 && a[j] > key; j--)
            a[j + 1] = a[j];
        a[j + 1] = key;
    }
}

void selSort(int a[], int n) // Selection Sort
{
    int i, j, min, temp;
    for (i = 1; i <= n; i++)
    {
        min = i;
        for (j = i + 1; j <= n; j++)
            if (a[j] < a[min])
                min = j;
        SWAP(a[i], a[min], temp);
    }
}

int partition(int a[], int low, int high) // Partition for Quick Sort
{
    int mid = low + (high - low) / 2; 
    int pivot = a[mid]; 
    int i = (low - 1);
    int temp;

    for (int j = low; j <= high - 1; j++)
    {
        if (a[j] < pivot)
        {
            i++;
            SWAP(a[i], a[j], temp);
        }
    }
    SWAP(a[mid], a[high], temp);
    return (i + 1);
}

void quickSort(int a[], int low, int high) // Quick Sort
{
    if (low < high)
    {
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

void merge(int a[], int low, int mid, int high) // Merge for Merge Sort
{
    int i, j, k;
    int b[MAX_SIZE];
    i = low;
    j = mid + 1;
    k = low;

    while (i <= mid && j <= high)
    {
        if (a[i] <= a[j])
            b[k++] = a[i++];
        else
            b[k++] = a[j++];
    }

    while (i <= mid)
        b[k++] = a[i++];

    while (j <= high)
        b[k++] = a[j++];

    for (i = low; i <= high; i++)
        a[i] = b[i];
}

void mergeSort(int a[], int low, int high) // Merge Sort
{
    int mid;
    if (low < high)
    {
        mid = (low + high) / 2;
        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

void heapify(int a[], int n, int i) // Heapify for Heap Sort
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int temp;

    if (left < n && a[left] > a[largest])
        largest = left;

    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i)
    {
        SWAP(a[i], a[largest], temp);
        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n) // Heap Sort
{
    int temp;
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        SWAP(a[0], a[i], temp);
        heapify(a, i, 0);
    }
}

void genDataRandom(int list[], int n)
{
    static int vSeed;

    srand(time(NULL) + vSeed);
    for (int i = 0; i < n; i++)
        list[i] = rand() % (n * 10);
    vSeed += 1;
}

void genDataDescending(int list[], int n)
{
    for (int i = 0; i < n; i++)
        list[i] = n - i;
}

void genDataAscending(int list[], int n)
{
    for (int i = 0; i < n; i++)
        list[i] = i;
}

void runSort(void (*sortFunc)(int[], int), int list[], int temp[], int n, double* total_time) {
    copyArray(list, temp, n);
    clock_t start = clock();
    sortFunc(temp, n);
    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    if (total_time != NULL) {
        *total_time += cpu_time_used;
    }
    printf("%f\t", cpu_time_used);
}

void runSortWithIndices(void (*sortFunc)(int[], int, int), int list[], int temp[], int n, double* total_time) {
    copyArray(list, temp, n);
    clock_t start = clock();
    sortFunc(temp, 0, n - 1);
    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    if (total_time != NULL) {
        *total_time += cpu_time_used;
    }
    printf("%f\t", cpu_time_used);
}
int main()
{
    int n, trials;
    printf("Enter # of Data to generate: ");
    scanf("%d", &n);
    printf("Enter # of Trials: ");
    scanf("%d", &trials);

    int* list = (int*)malloc(n * sizeof(int));
    int* temp = (int*)malloc(n * sizeof(int));
    double total_time_sel = 0, total_time_ins = 0, total_time_quick = 0, total_time_merge = 0, total_time_heap = 0;

    printf("\n=== Upon [%d] data, doing %d trials .....\n", n, trials);
    printf("Selection\tInsertion\tQuick\t\tMerge\t\tHeap\n");
    printf("--------------------------------------------------------\n");
  
    for (int t = 0; t < trials; t++)
    {
        genDataRandom(list, n);

        runSort(selSort, list, temp, n, &total_time_sel);
        runSort(insSort, list, temp, n, &total_time_ins);
        runSortWithIndices(quickSort, list, temp, n, &total_time_quick);
        runSortWithIndices(mergeSort, list, temp, n, &total_time_merge);
        runSort(heapSort, list, temp, n, &total_time_heap);

        printf("\n");
    }

    printf("\n=== Average of %d trials upon [%d] data: \n", trials, n);
    printf("Selection\tInsertion\tQuick\t\tMerge\t\tHeap\n");
    printf("--------------------------------------------------------\n");
    printf("%f\t", total_time_sel / trials);
    printf("%f\t", total_time_ins / trials);
    printf("%f\t", total_time_quick / trials);
    printf("%f\t", total_time_merge / trials);
    printf("%f\n", total_time_heap / trials);

    printf("\n=== Case of [DESCENDING] upon [%d] data:\n", n);
    printf("Selection\tInsertion\tQuick\t\tMerge\t\tHeap\n");
    printf("--------------------------------------------------------\n");
    genDataDescending(list, n);

    runSort(selSort, list, temp, n, NULL);
    runSort(insSort, list, temp, n, NULL);
    runSortWithIndices(quickSort, list, temp, n, NULL);
    runSortWithIndices(mergeSort, list, temp, n, NULL);
    runSort(heapSort, list, temp, n, NULL);

    printf("\n\n=== Case of [ASCENDING] upon [%d] data:\n", n);
    printf("Selection\tInsertion\tQuick\t\tMerge\t\tHeap\n");
    printf("--------------------------------------------------------\n");
    genDataAscending(list, n);

    runSort(selSort, list, temp, n, NULL);
    runSort(insSort, list, temp, n, NULL);
    runSortWithIndices(quickSort, list, temp, n, NULL);
    runSortWithIndices(mergeSort, list, temp, n, NULL);
    runSort(heapSort, list, temp, n, NULL);


    free(list);
    free(temp);

    return 0;
}