/*
 * This program does matrix mulltiplication using multiple threads.
 * Example usage: ./x.out <path for file A> <path for file B> <path for file C> <number of threads> <size of matrix>
 * 
 *
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
//initialize double pointers to matrices
int  **matrix1, **matrix2, **matrix3;

//struct to pass data to threads
struct thread_args{
	int thread_no;
	int no_threads;
	int arraysize;
};

//method to do the matrix multiplication
void *calculate(void *arguments){
	//read in data from struct passed to this method
	struct thread_args *args = arguments;
	
	//get data from struct
	//thread number
	int thread_no = (int) args -> thread_no;
	
	//number of threads
	int no_threads = (int) args -> no_threads;
	
	//size of matrix
	int arraysize = (int) args -> arraysize;
	
	//helper variables for loops
	int x, y, z;
	
	//calculate the multiplier to identify the work to be done by this thread
	int multiplier = arraysize/no_threads;
	
	//do matrix multiplication
	for(x = thread_no*multiplier;x<(thread_no+1)*multiplier; x++){
		for(y = 0; y<arraysize; y++){
			for(z=0; z<arraysize; z++){
				matrix3[x][y] += matrix1[x][z] * matrix2[z][y];
			}
			//sleep for 10 microseconds
			usleep(10);
		}
	}
}

void main(int argc, char *argv[]){
	//open file pointers for files for A and B
	FILE *rptrA = fopen(argv[1], "r");
	FILE *rptrB = fopen(argv[2], "r");
	
	//helper variables for loops
	int i, j;
	
	//read number of threads from commandline arguments
	int no_threads = atoi(argv[4]);

	//declare variable for threads
	pthread_t tid[no_threads];

	//matrix size
	int arraysize = atoi(argv[5]);

	//initialize the first dimension of the matrices
	matrix1 = (int **)malloc(sizeof(int *) * arraysize);
	matrix2 = (int **)malloc(sizeof(int *) * arraysize);
	matrix3 = (int **)malloc(sizeof(int *) * arraysize);

	//initialize the second domension of matrices
	for(i = 0; i<arraysize; i++){
		matrix1[i] = (int *)malloc(sizeof(int) * arraysize);
		matrix2[i] = (int *)malloc(sizeof(int) * arraysize);
		matrix3[i] = (int *)malloc(sizeof(int) * arraysize);
	}

	//read matrix A and B from file and load them into matrix1 and matrix2
	for(i=0; i<arraysize; i++){
		for(j=0; j<arraysize; j++){
			fscanf(rptrA, "%d ", &matrix1[i][j]);
			fscanf(rptrB, "%d ", &matrix2[i][j]);
		}
	}
	
	//close pointers for files for A and B
	fclose(rptrA);
	fclose(rptrB);

	for(i = 0; i<no_threads; i++){
		//initialize and set values in the struct to be passed to multi threaded method
		struct thread_args *arguments = malloc(sizeof(struct thread_args));
		arguments->thread_no = i;
		arguments->no_threads = no_threads;
		arguments->arraysize = arraysize;
		
		//create multiple threads
		pthread_create(&tid[i], NULL, calculate, (void *) arguments );
	}	

	//make sure the main method waits for threads to terminate before terminating
	for(i = 0; i<no_threads; i++){
		pthread_join(tid[i], NULL);
	}
	
	//open a pointer for file for C
	FILE *wptrC = fopen(argv[3], "wb");
	
	//write matrix C to file
	for(i = 0; i < arraysize; i++){
		for(j = 0; j < arraysize; j++){
			fprintf(wptrC, "%d ", matrix3[i][j]);
		}
	}
	
	//close the pointer for C
	fclose(wptrC);

}
