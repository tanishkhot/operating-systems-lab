#include <stdio.h>


void printArray(int rows, int cols, int array[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", array[i][j]);
            printf("\t");
        }
        printf("\n");
    }
}

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




void nonPreemption(){
    // Logic : sort the array according to arrival time. Then, directly display the order in which they are.
    int rows, cols = 4;
    printf("This will take input row wise.");

    printf("The usual format is: \n Process #\t:\tArrival time\t:\tBurst time\t:\tCompletion time");
    printf("Enter the number of rows (Processes): ");
    scanf("%d", &rows);
    
    int array[rows][cols];
    
    printf("Enter the arrival and burst times:\n");
    for(int i = 0; i < rows; i++) {
        array[i][0] = i;
        
        printf("Process %d Arrival time: ", i);
        scanf("%d", &array[i][1]);

        printf("Process %d Burst time: ", i);
        scanf("%d", &array[i][2]);

        array[i][3] = 0;
    }

    printf("Original array: \n");
    printArray(rows, cols,array);

    sortRowsBySecondColumn(array, rows);

    //printing the sorted array
    printf("Sorted array by the AT:\n");
    printArray(rows, cols,array);
    
    int currentTime = 0;
    for(int i = 0; i < rows; i++){
        if(currentTime < array[i][1]){
            currentTime = array[i][1];
        }
        currentTime += array[i][2];
        array[i][3] = currentTime;
    }

    printf("Final order with which processes run: ");
    for(int i = 0 ; i < rows; i++) {
        printf("%d --> ", array[i][0]);
    }
    printf("END\n");
    
    



    return;
}



int main() {
    nonPreemption();    
    return 0;
}
