#include "record.c"
#include "sortingalgorithms.c"
#include "filereader.c"
#include "timer.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int status, choice;
    int recordCount; //number of records in file
    long startTime, endTime, executionTime;
    pathName path; //path of .txt file to be sorted

    do 
    {
        printf("\t=== CHOOSING A FILE ===\n\n");
        printf("Enter file path of .txt file to sort:\n");
        fgets(path, 500, stdin);
        path[strcspn(path, "\n")] = '\0';

        status = isFileValid(path);
        if (status == 0) {
            printf("File not found. Please try again.\n");
        } else {
            printf("File found.\n");
        }
        printf("\n");
	} while (status == 0);

    //do dynamic memory allocation here
    recordCount = getRecordCount(path);
    printf("Number of records: %d\n", recordCount);
	Record *records = (Record *)malloc(recordCount * sizeof(Record));

    //file reading and storing to *records
    readFile(records, path);

    do
    {
        printf("\t=== SORTING ALGORITHMS ==\n\n");
        printf("Choose a sorting algorithm to use: \n");
        printf("[1] Insertion Sort.\n");
        printf("[2] Selection Sort.\n");
        printf("[3] Merge Sort.\n");
        printf("[4] Quick Sort.\n");
        printf("Input: ");
        scanf("%d", &choice);

        //call timer.c before starting, and after ending algorithm
        switch (choice)
        {
            case 1: //insertion
                startTime = currentTimeMillis();
                insertionSort(records, recordCount);
                endTime = currentTimeMillis();
                executionTime = endTime - startTime;
                // printRecordsToFile(records, recordCount); //to double check if the array of structs is sorted
                printf("Start Time: %ld ms\n End Time: %ld ms\n", startTime, endTime);
                printf("Time taken: %ld milliseconds.\n", executionTime);
            break;

            case 2: //selection sort
                startTime = currentTimeMillis();
                selectionSort(records, recordCount); //call selection sort here (sortingalgorithms.c
                endTime = currentTimeMillis();
                executionTime = endTime - startTime;
                // printRecordsToFile(records, recordCount); //to double check if the array of structs is sorted
                printf("Start Time: %ld ms\n End Time: %ld ms\n", startTime, endTime);
                printf("Time taken: %ld milliseconds.\n", executionTime);
            break;

            case 3: //merge sort

            break;

            case 4: //quick sort

            break;

            default:
                printf("Invalid choice. Please try again.\n");
            break;
        }
    } while( choice < 1 || choice > 4);

    free(records);

    return 0;
}