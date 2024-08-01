#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	printf("Hello, this is child with my pid %d\n", getpid());
	printf("Printing the array in child process: \n");
	for(int i=0 ; i < 5; i++){
		 printf("%s\n", argv[i]);
	}
}
