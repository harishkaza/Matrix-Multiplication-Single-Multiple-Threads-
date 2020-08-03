/*
 * This program will be used to compare two matrices by reading them from file.
 * Sample usage : ./x.out <size_of_matrix> <input file for C1> <input file for C2>
 */

#include <stdio.h>

int compareMatrices(FILE *rptrA, FILE *rptrB, int x){
	//initialize helper variables for the loops
	int i, j;
	
	
	for(i = 0; i<x; i++){
		for(j = 0; j<x; j++){
			//helper variables for the values of C1 and C2
			int A, B;
			
			//read in next values from C1 and C2
			fscanf(rptrA, "%d ", &A);
			fscanf(rptrB, "%d ", &B);
			
			//if same, continue, else return 0
			if(A!=B) return 0;
		}
	}
	return 1;
}


void main(int argc, char *argv[]){
	FILE *rptrA;
	FILE *rptrB;
	int x = atoi(argv[1]);//get the size of matrix from arguments

	rptrA = fopen(argv[2], "r");//open file for matrix C1 from arguments
	rptrB = fopen(argv[3], "r");//open file for matrix C2 from arguments

	//check if matrices are same.
	
	//if same print out Matrices are same
	if(compareMatrices(rptrA, rptrB, x)==1) printf("Matrices are same\n");
	
	//else print out matrices are not same
	else printf("Matrices are not same\n");
	
	//close pointers for C1 and C2
	fclose(rptrA);
	fclose(rptrB);
}
