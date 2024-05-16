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
        while (j > 0 && arr[j].idNumber > key) {
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
void mergeSort(Record *arr, int p, int r)
{
    // TODO: Implement this sorting algorithm here.






}

/*
* Define AT LEAST ONE more sorting algorithm here, apart from the
* ones given above. Make sure that the method accepts an array of
* record structures.
*/

/*
    pseudo-code for quick sort is as follows
*/
void quickSort()
{

}


#endif