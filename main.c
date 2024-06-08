#include "record.c"
#include "sortingalgorithms.c"
#include "filereader.c"
#include "timer.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int i, index;
    int status, choice;
    int recordCount; //number of records in file
    long startTime, endTime, executionTime;
    pathName path; //path of .txt file to be sorted

    /*
        This part of the main program asks the user to input the file path of the .txt file that contains the records.
        If the input is invalid, the program will keep asking the user to input the file path until the file is found.
        It is assumed that the .txt file is already in the correct format, with the first line being the number of records.
    */
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

    /*
        This part of the main program reads the number of records in the .txt file. It is assumed that the .txt file is already in the correct format,
        with the first line being the number of records. The number of records is then stored in the variable recordCount, and is used to allocate 
        memory to store the records in the array sortedRecords (named so because this will be sorted).
    */
    recordCount = getRecordCount(path);
    printf("Number of records: %d\n", recordCount);
	Record *sortedRecords = (Record *)malloc(recordCount * sizeof(Record));
    readFile(sortedRecords, path);

    /*
        This part of the main program asks the user to choose a sorting algorithm to use. The user can choose from either executing insertion sort,
        selection sort, merge sort, or quick sort. The program will then call the respective sorting algorithm and time how long it takes to sort.
        It will also store the records from the SORTED array of structs into a .txt file called output.txt for verification purposes.
    */
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
                insertionSort(sortedRecords, recordCount);
                endTime = currentTimeMillis();
                executionTime = endTime - startTime;
                printRecordsToFile(sortedRecords, recordCount); //to double check if the array of structs is sorted
                printf("Start Time: %ld ms\n End Time: %ld ms\n", startTime, endTime);
                printf("Time taken: %ld milliseconds.\n", executionTime);
            break;

            case 2: //selection sort
                startTime = currentTimeMillis();
                selectionSort(sortedRecords, recordCount); //call selection sort here (sortingalgorithms.c
                endTime = currentTimeMillis();
                executionTime = endTime - startTime;
                printRecordsToFile(sortedRecords, recordCount); //to double check if the array of structs is sorted  
                printf("Start Time: %ld ms\n End Time: %ld ms\n", startTime, endTime);
                printf("Time taken: %ld milliseconds.\n", executionTime);
            break;

            case 3: //merge sort
                startTime = currentTimeMillis();
                iterativeMergeSort(sortedRecords, recordCount); //call merge sort here (sortingalgorithms.c)
                endTime = currentTimeMillis();
                executionTime = endTime - startTime;
                printRecordsToFile(sortedRecords, recordCount); //to double check if the array of structs is sorted
                printf("Start Time: %ld ms\n End Time: %ld ms\n", startTime, endTime);
                printf("Time taken: %ld milliseconds.\n", executionTime);
            break;

            case 4: //quick sort 
                startTime = currentTimeMillis();
                iterativeQuickSort(sortedRecords, 0, recordCount - 1);
                endTime = currentTimeMillis();
                executionTime = endTime - startTime;
                printRecordsToFile(sortedRecords, recordCount); //to double check if the array of structs is sorted
                printf("Start Time: %ld ms\n End Time: %ld ms\n", startTime, endTime);
                printf("Time taken: %ld milliseconds.\n", executionTime);
            break;

            default:
                printf("Invalid choice. Please try again.\n");
            break;
        }
    } while( choice < 1 || choice > 4);

    /*
        This part of the main program helps us check if the sorted array is correct (in the sense that
        it is arranged from least to greatest while also maintaining the connection between the ID number
        and the name of the person).
    */

    //allocate memory (again) for the unsorted array of structs (done AFTER sorting the array of structs earlier)
	Record *unsortedRecords = (Record *)malloc(recordCount * sizeof(Record));
    readFile(unsortedRecords, path);
    FILE *fp = fopen("comparison.txt", "w");

    //compare the sorted array of structs with the unsorted array of structs
    for (i = 0; i < recordCount; i++) {
        index = binarySearchForRecord(sortedRecords, recordCount, unsortedRecords[i].idNumber, unsortedRecords[i].name);
        if (index != -1) {
            fprintf(fp, "Record with ID %d and name %s found at index %d.\n", unsortedRecords[i].idNumber, unsortedRecords[i].name, index);
        } else {
            fprintf(fp, "Record with ID %d and name %s not found.\n", unsortedRecords[i].idNumber, unsortedRecords[i].name);
        }
    }
    fclose(fp);

    //frees the memory allocated for the arrays of structs
    free(sortedRecords);
    free(unsortedRecords);

    printf("Please check output.txt for the sorted .txt file.\n");
    printf("Please check comparison.txt for the comparison between sorted and unsorted arrays using entries from user-specified .txt file at start of program.\n");

    return 0;
}