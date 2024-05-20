#ifndef SORTINGALGORITHMS_C
#define SORTINGALGORITHMS_C

#include <stdio.h>
#include "record.c"

typedef char pathName[500]; //declaration of a type for the path name of the file

/*
    This function asks for the file path of the .txt file that contains the records.
    Returns 1 is file is found, 0 if the file is not found. 
*/
int isFileValid (pathName path)
{
    FILE *fp;
    fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 0; //file is not found
    } else {
        return 1; //file found
    }
    fclose(fp);
}
/*
    This functions reads the number of records in the .txt file. Assumes that .txt file is already in the correct format,
    with the first line being the number of records. Returns the number of records in the file.
*/
int getRecordCount(pathName path)
{
    int recordCount;
    FILE *fp;

    fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return -1;
    } else {
            fscanf(fp, "%d", &recordCount);
    }
    fclose(fp);

    return recordCount;
}

/*
    This function prints out the contents of the array of structs/records into a .txt file called output.txt
    Helps ensure that the sorting algorithms are working correctly. For testing purposes.
*/
void printRecordsToFile(Record *records, int recordCount) {
    FILE *file = fopen("output.txt", "w"); //opens file in write mode, if output.txt does not exist, it will be created
    if (file == NULL) {
        printf("Error opening file!\n"); //accounts for other instances where file may not be opened
        return;
    }

    for(int i = 0; i < recordCount; i++) {
        fprintf(file, "ID number %d, %s\n", records[i].idNumber, records[i].name);
    }

    fclose(file);
}

/*
    This function allows for the swapping of different elements in an array of structs/records.
*/
void swapStructs (Record *a, Record *b)
{
    Record temp = *a;
    *a = *b;
    *b = temp;
}

void merge (Record *arr, int p, int q, int r)
{   
    int i, j, k, len1, len2;

    //separates the main array into 2 subarrays
    len1 = q - p + 1; //length of first array
    len2 = r - q; //length of second array

    Record tempArr1[len1], tempArr2[len2]; //temp arrays to store the subarrays

    for (i = 0; i < len1; i++) { //copy the elements of first subarray into tempArr1
        tempArr1[i] = arr[p + i];
    }

    for (j = 0; j < len2; j++) { //copy the elements of second subarray into tempArr2
        tempArr2[j] = arr[q + 1 + j];
    }

    i = 0;
    j = 0;
    k = p;

    //this also sorts the elements of the temp arrays while also putting it back in main array
    while (i < len1 && j < len2) {
        if (tempArr1[i].idNumber <= tempArr2[j].idNumber) {
            arr[k] = tempArr1[i];
            i++;
        } else {
            arr[k] = tempArr2[j];
            j++;
        }
        k++;
    }

    //when either i == len1 or j == len2, the remaining elements are copied into the main array
    while (i < len1) {
        arr[k] = tempArr1[i];
        i++;
        k++;
    }

    while (j < len2) {
        arr[k] = tempArr2[j];
        j++;
        k++;
    }
}

/*
    pseudo-code for insertion sort is as follows
*/

void insertionSort(Record *arr, int n)
{
    // TODO: Implement this sorting algorithm here.
    int i, j, key;

    for (i = 1; i < n; i++) {
        key = arr[i].idNumber;
        j = i - 1;
        while (j >= 0 && arr[j].idNumber > key) {
            arr[j + 1] = arr[j];
            j -= 1;
        }
        arr[j + 1].idNumber = key;
    }
}

/*
    pseudo-code for selection sort is as follows
*/
void selectionSort(Record *arr, int n)
{
    // TODO: Implement this sorting algorithm here.
    int i, j, minIndex;

    for (i = 0; i < n - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j].idNumber < arr[minIndex].idNumber) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swapStructs(&arr[minIndex], &arr[i]);
        }
    }
}

/*
    pseudo-code for merge sort is as follows
*/
void mergeSort(Record *arr, int p, int r) //p is the starting index, r is the end index, q is the midpoint
{
    // TODO: Implement this sorting algorithm here.

    int q;

    if (p < r) {
        q = p + (r - p) / 2;
        mergeSort(arr, p, q);
        mergeSort(arr, q + 1, r);
        merge(arr, p, q, r);
        return;
    }
}

/*
* Define AT LEAST ONE more sorting algorithm here, apart from the
* ones given above. Make sure that the method accepts an array of
* record structures.
*/

//ITERATIVE QUICKSORT




//getPivot function rearranges so that the ones lower than the pivot are to the left, and the ones higher are to the right.
int getPivot(Record *arr, int lo, int hi){
    int mid = lo + (hi - lo) / 2;
    //median of three method to find the pivot
    if (arr[mid].idNumber < arr[lo].idNumber) 
        swapStructs(&arr[lo], &arr[mid]);

    if (arr[hi].idNumber < arr[lo].idNumber) 
        swapStructs(&arr[lo], &arr[hi]);

    if (arr[hi].idNumber < arr[mid].idNumber) 
        swapStructs(&arr[mid], &arr[hi]);


    swapStructs(&arr[mid], &arr[hi]); //move pivot to the very right/end
    Record pivot = arr[hi];//store the information of the pivot


    int left = lo;
    int right = hi - 1; //-1 to account for the pivot
    while (left <= right){//keep swapping until the left is bigger than the right, or the other way around
        if (arr[left].idNumber <= pivot.idNumber)
            left++;
        else if (arr[right].idNumber >= pivot.idNumber)
            right--;
        else{//when left is bigger than the right, swap.
            swapStructs(&arr[left], &arr[right]);
            left++;
            right--;
        }

        
    }
    
    swapStructs(&arr[left], &arr[hi]);//move pivot to its correct location
    return left; // return the pivot's final position

}


/*
    pseudo-code for quick sort is as follows
*/
void quickSort(Record *arr, int lo, int hi)
{
    //since were not using recursion, we'll utilize stacks
    int stack[hi - lo + 1];
    int top = -1; //initialized to -1, which means empty
    int pivot; 

    
    stack[++top] = lo; //lo takes the 0th index aka "pushing" a value to the stack
    stack[++top] = hi; //hi takes the 1th index

    //process stack elements until empty 
    while (top >= 0){
        hi = stack[top--]; // get the value of stack and then decrement, aka "popping" the stack
        lo = stack[top--]; // its back to lo's stack so gets it and decrements. were back at -1

        //getPivot gets the pivot by finding the median
        pivot = getPivot(arr, lo, hi);

        //if there are elements on the left that are unsorted...
        if (pivot - 1 > lo){
            stack[++top] = lo; //lo is now at 0
            stack[++top] = pivot - 1; //the new "hi" is now at 1(which is to the left of pivot)

        }
        //if there are elements on the right that are unsorted...
        if (pivot + 1 < hi){
            stack[++top] = pivot + 1; //set the right of the pivot to the new "lo" 
            stack[++top] = hi; //the hi remains the same
            
        }
    }
}


#endif