#include<stdio.h>
#include<stdlib.h>
int main (int argc, char** argv){

	FILE* fp;
	int matrixSize;
	int ** matrix;
	int * matrixsum;
	//int * unique;
	int magic= 1;

	if (argc!= 2){
		printf("not enough arguments");
	}
	fp = fopen(argv[1], "r");

	if (fp ==NULL){
		printf("Error, no input");
		return 0;
	}
	
	fscanf(fp,"%d", &matrixSize);
	matrix = (int**) malloc(matrixSize * sizeof(int*)); // matrix allocated

	for(int i=0; i< matrixSize; i++){
		matrix[i] = (int *) malloc(matrixSize * sizeof(int));
	}

	for(int i=0; i< matrixSize; i++){
		for(int j=0; j< matrixSize; j++){
			fscanf(fp, "%d", &matrix[i][j]);
		}
	}

// allocate sum array:
	int sumsize = 2*matrixSize +2;
	matrixsum = (int *) malloc(sumsize * sizeof(int));

//error check + make sure its valid input/format
	//check if numbers are within matrix size ex: 3x3 shouldnt contain 12	or be negative
	for (int i=0; i<matrixSize; i++){
		for(int j =0; j< matrixSize; j++){
			if(matrix[i][j] > matrixSize*matrixSize || matrix[i][j]<=0){
				magic = 0;
				break;
			}
		}
	}
	//check if all the numbers are unique
	for (int i=1; i<matrixSize; i++){
		for(int j =1; j< matrixSize; j++){
			if(matrix[0][0] == matrix[i][j]){
				magic= 0;
				break;
			}
		}
	}

if(magic == 1){

//summing the matrix:
	
//sum rows
	int sum=0;
	
	for(int j=0; j< matrixSize; j++){
		for(int i=0; i< matrixSize; i++){
			sum+= matrix[j][i];
		}
	matrixsum[j] = sum;
		//printf("sum rows is: %d\n", sum );
		sum=0;
	}
//sum columns
sum =0;
	for(int i=0; i< matrixSize; i++){
		for(int j=0; j< matrixSize; j++){
			sum+= matrix[i][j];
		}
		matrixsum[i+ matrixSize] = sum;
		//printf("sum columnn is: %d\n", sum );
		sum=0;
	}
//sum diagonal left to right
	sum =0;
		for(int i=0; i< matrixSize; i++){
			sum+= matrix[i][i];
		}
		matrixsum[2*matrixSize] = sum;
		sum=0;
    
//sum diagonal right to left
	int j = matrixSize - 1;
	int i=0;
	while (j>=0){
		sum+=matrix[i][j];
		i++;
		j--;
	}
	matrixsum[1+2*matrixSize]=sum;
	sum = 0;

//traverse sum array and checking if all sums are equal
	for(int i =0; i< 2*matrixSize+2; i++){
		if(matrixsum[0] != matrixsum[i]){

			magic =0;
		}
		else{
		magic = 1;
		}
	}
}


// output the verdict
	if(magic == 0){
	printf("not-magic");
	}
	if(magic == 1){
	printf("magic");
	}

// free matrix and matrixsum
	for(int i=0; i< matrixSize; i++){
		free(matrix[i]);
	}
	free(matrix);
	free(matrixsum);

//close file
	fclose(fp);

	return 0;
}

