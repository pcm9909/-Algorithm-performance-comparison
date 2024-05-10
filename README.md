정렬 알고리즘(선택정렬, 삽입정렬, 퀵정렬, 병합정렬, 힙정렬) 성능 비교

```c
cc TERM.c
```

선택 정렬
```c
void selSort(int a[], int n)
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
```

삽입정렬
```c
void insSort(int a[], int n)
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
```

퀵소트
```c
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
```

병합정렬
```c
void merge(int a[], int low, int mid, int high) 
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

```

힙정렬
```c
void heapify(int a[], int n, int i)
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
```
