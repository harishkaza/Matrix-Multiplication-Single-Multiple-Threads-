/*
 * This program will be used to generate random matrices and write them to file.
 * Sample usage : ./x.out <size_of_matrix> <output file for A> <output file for B>
 */

#include <stdio.h>

void writeMatrix(FILE *wptr, int x){
	//initialize variables for looping
	int i, j;
	
	for(i = 0; i<x; i++){
		for(j = 0; j<x; j++){
			
			//make sure that the random number generated is less than 2000
			int val = rand() % 2000;
			
			//write to file
			fprintf(wptr, "%d ", val);
			
		}
	}
}


void main(int argc, char *argv[]){
	FILE *wptrA;
	FILE *wptrB;
	
	//get the size of matrix from arguments
	int x = atoi(argv[1]);

	//open file for matrix A from arguments
	wptrA = fopen(argv[2], "wb");
	
	//open file for matrix B from arguments
	wptrB = fopen(argv[3], "wb");
	
	//seed the rand function with current time
	srand(time(NULL));
	
	
	//write matrix A
	writeMatrix(wptrA, x);
	
	//write matrix B
	writeMatrix(wptrB, x);

	//close file pointers
	fclose(wptrA);
	fclose(wptrB);
}

