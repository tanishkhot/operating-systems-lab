#include <stdio.h>
#include <stdlib.h>

//working
void printArray(int rows, int cols, int** array) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", array[i][j]);
        }
        printf("\n");
    }
}

//working
int** input(int* rows, int cols) {
    cols = 4;
    printf("This will take input row wise.\n");

    printf("The usual format is: \n Process #\t:\tArrival time\t:\tBurst time\t:\tCompletion time\n");
    printf("Enter the number of rows (Processes): ");
    scanf("%d", rows);
    //Dynamic memory allocation is when the data structure is changed at runtime.
    int** array = (int**)malloc(*rows * sizeof(int*));  //refer to malloc.c
    for (int i = 0; i < *rows; i++) {
        array[i] = (int*)malloc(cols * sizeof(int));
    }
    
    printf("Enter the arrival and burst times:\n");
    for (int i = 0; i < *rows; i++) {
        array[i][0] = i;
        
        printf("Process %d Arrival time: ", i);
        scanf("%d", &array[i][1]);

        printf("Process %d Burst time: ", i);
        scanf("%d", &array[i][2]);

        array[i][3] = 0; //initialize completion time to 0
    }

    printf("Original array: \nPID\tAT\tBT\tCT\n");
    
    printArray(*rows, cols, array);

    return array;
}

// Not workig: row int ptr issue 
void sortRowsBySecondColumn(int array[][4], int rows) {
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < rows - i - 1; j++) {
            if (array[j][1] > array[j + 1][1]){
                for (int k = 0; k < 4; k++) {
                    int temp = array[j][k];
                    array[j][k] = array[j + 1][k];
                    array[j + 1][k] = temp;
                }
            }
        }
    }
}

//working : manage how to pass an array here
void ganttChart(int* arr, int length){
    //top:
    for(int i = 0; i < length; i++){
        for(int j = 0; j < arr[i]; j++){
            printf("__");
        }
    }
    printf("\n");

    //inside block:
    for(int i = 0; i < length; i++){
        printf("|");
        for(int j = 0; j < arr[i]; j++){
            if(j == arr[i]/2){
                printf("%d ", arr[i]);
                if(arr[i] >= 10){   //for two digit numbers
                    j++;        
                }
            }
            else{
                printf("  ");
            }
        }
    }
    printf("|\n");

    //bottom:
    for(int i = 0; i < length; i++){
        printf("|");
        for(int j = 0; j < arr[i]; j++){
            printf("__");
        }
    }
    printf("|\n");
}

//Not working, chnge it from 2D array to a ptr
void nonPreemption(){
    // Logic : sort the array according to arrival time. Then, directly display the order in which they are.
    int* rows =4;
    int cols = 4;
    int** matrix = input(rows, cols);
    
    sortRowsBySecondColumn(matrix, rows);

    //printing the sorted array
    printf("Sorted array by the AT:\n");
    printArray(rows, cols,matrix);
    
    int currentTime = 0;
    for(int i = 0; i < rows; i++){
        if(currentTime < matrix[i][1]){
            currentTime = matrix[i][1];
        }
        currentTime += matrix[i][2];
        array[i][3] = currentTime;
    }

    printf("Final order with which processes run: ");
    for(int i = 0 ; i < rows; i++) {
        printf("%d --> ", matrix[i][0]);
    }
    printf("END\n");
    
    return;
}


int main() {
    nonPreemption();
    //int array[] = {5,3,7,2};
    //int length = sizeof(array) / sizeof(array[0]);
   // ganttChart(array,length);    
    //int rows, cols;
    //int** processArray = input(&rows, cols);

    //printArray(rows, cols, processArray);
    
    return 0;
}
