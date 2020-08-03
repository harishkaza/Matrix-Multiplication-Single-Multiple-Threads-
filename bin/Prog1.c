/*
 * This program will be used to do matrix multiplication on two square matrices.
 * Usage : ./x.out <file for first matrix A> <file for second matrix B> <file for output matrix C> <size of matrix>
 * The files will have n*n space separated integers, where n is the size of matrix.
 */
#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[]){
	FILE *rptrA, *rptrB, *wptrC;
	
	//open file for A
	rptrA = fopen(argv[1], "r");
	
	//open file for B
	rptrB = fopen(argv[2], "r");
	
	//read array size from commandline args
	int arraysize = atoi(argv[4]);

	int **matrix1;//matrix A
	int **matrix2;//matrix B
	int **matrix3;//matrix C
	
	int i, j, k;

	//initialize the first dimension of the matrices
	matrix1 = (int **)malloc(sizeof(int *) * arraysize);
	matrix2 = (int **)malloc(sizeof(int *) * arraysize);
	matrix3 = (int **)malloc(sizeof(int *) * arraysize);
	
	for(i = 0; i<arraysize; i++){
		//initialize the second domension of matrices
		matrix1[i] = (int *)malloc(sizeof(int) * arraysize);
		matrix2[i] = (int *)malloc(sizeof(int) * arraysize);
		matrix3[i] = (int *)malloc(sizeof(int) * arraysize);
	}

	//read values of A and B into matrix1 and matrix2 from the path given in commandline args
	for(i = 0; i<arraysize; i++){
		for(j=0; j<arraysize; j++){
			fscanf(rptrA, "%d ", &matrix1[i][j]);
			fscanf(rptrB, "%d ", &matrix2[i][j]);
		}
	}
	
	//close pointers for the files for A and B
	fclose(rptrA);
	fclose(rptrB);

	//do matrix multiplication
	for(i = 0; i< arraysize; i++){
		for(j = 0; j< arraysize; j++){
			for(k = 0; k<arraysize; k++){
				 matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
			}
			
			//sleep for 10 microseconds
			usleep(10);
		}
	}

	//open file for C for writing
	wptrC = fopen(argv[3], "wb");
	
	//write matrix C
	for(i = 0; i < arraysize; i++){
		for(j = 0; j < arraysize; j++){
			fprintf(wptrC, "%d ", matrix3[i][j]);
		}
	}
	
	//close file for C
	fclose(wptrC);

}
