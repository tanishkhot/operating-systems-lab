#include<stdio.h>
#include<unistd.h>


void bubbleSort(int array[], int size) {
    int i, j, temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            // Swap if the element found is greater than the next element
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int main(){
	printf("We are in main prcoess with process id %d\n" , getpid());
	
    	printf("Enter 5 elements in the array: ");
    	int arr[5];
	printf("Enter 5 integers:\n");
	for (int i = 0; i < 5; i++) {
	        scanf("%d", &arr[i]);
    	}
	
	bubbleSort(arr, 5);
	
	
	//creating a new fork
	pid_t pid;
	//pid = fork();
	
	printf("The child has been born with pid: %d\n" , pid);
            for (int i = 0; i < 5; i++) {
       	  	char num_str[20]; // Assuming a maximum number length of 20 characters
         	sprintf(num_str, "%d", arr[i]);
            	argv[i + 1] = strdup(num_str); // Allocate memory for string and copy
            }
          
        
	char *argv[] = {"./child.out", arr, NULL};
	execv(argv[0], argv);
	
	printf("This will not print");
}
