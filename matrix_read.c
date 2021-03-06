/*
 * This program takes MxN matrix as input from the command line. 
 *  
 */


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

typedef struct Matrix{
	unsigned int row;
	unsigned int column;
}size_of_matrix;

/*
 * Parse the input from command line and creates NxN matrix
 */
void prepare_matrix(char *, unsigned int, int **);

/*
 * converts string to digit
 */
int convert_to_digit(char *, unsigned int);

/*
 * @retunrs power function a^b
 */
unsigned int power(int,int);

/*
 * @returns the lenght of the substring. 
 */
unsigned int find_length(char *, char *);

/*
 * @returns size of input matrix
 */

void find_size_of_matrix(char *, size_of_matrix *);

/*
 * Display the NxN matrix on terminal
 */
void print_matrix(int**, size_of_matrix *size);

/*
 * main function
 */

void matrix_LU(int **, int**, int **, unsigned int , unsigned int );

int main (int argc, char * argv[]){

	unsigned int length =0,size=0;

        size_of_matrix size_ = {0,0};

	int **matrix_2D = NULL;
	int **L = NULL;
	int **U = NULL;
	
	if(argc == 1){
		printf("Number of input parameter =1\n");
		printf("Terminating execution\n");
		return 0;
	}	
         
	
	char *data = argv[2];
	length = strlen(argv[2]);
	
        find_size_of_matrix(data, &size_);

	printf("number of row = %d, number of column = %d\n", size_.row,size_.column);
        
	
	matrix_2D = (int **)malloc(size_.row* sizeof(int*));
        L = (int **)malloc(size_.row * sizeof(int*));
	U = (int **)malloc(size_.row * sizeof(int*));

	for(unsigned int i=0; i<size_.row; i++){
		matrix_2D[i] = (int *)malloc(sizeof(int)*(size_.column));
		L[i] = (int *)malloc(sizeof(int)*(size_.column));
		U[i] = (int *)malloc(sizeof(int)*(size_.column));
	}
	
	prepare_matrix(++data,length, matrix_2D);
        print_matrix(matrix_2D,&size_);

	matrix_LU(matrix_2D, L, U, size_.row, size_.column);
        
	printf("matrix L\n");
	print_matrix(L,&size_);

	/*
	 * Free up the memory
	 */
	for(unsigned int i=0; i<size; i++){
		free(matrix_2D[i]);
	}

	free(matrix_2D);

	return 0;
}

unsigned int find_length(char *start, char *end)
{
	unsigned int len=0;

	while(*start != *end){
	len++;
	start++;
	}

	return len;
}
unsigned int power(int base,int exponent){
    
    if(base == 0)
    {
	return 0;
    }
    else if (exponent == 0 || (exponent < 0))
    {
	return 1;
    }
    else{
        return base*power(base,--exponent);
    }
}

int convert_to_digit(char *temp, unsigned int length){
	
	int number = 0;
	unsigned int i=0;
	unsigned int chr;
	bool neg = false;
	if(((temp-1) != NULL) && (length > (unsigned int)0))
	{
	  while(length>0){
	   
	    chr = *(temp -1 -i);
            if( chr != ' '){
	    if(chr != '-')
	    {
            	chr = chr - '0';
	        number += chr*power(10,i);
	    }
	    else
	    {
	        neg = true;
	    }
	    }
	    length--;
	    i++;

	    }
       }
	//printf("number = %d\n neg= %d\n", number, neg);
	if (neg == true)
	{
	    number = -number;
	}
	return number;
}

void prepare_matrix(char *matrix, unsigned int length, int** matrix_2D){

        char *temp;
	int number;
	unsigned int len;
	unsigned row=0,column=0;
	for(unsigned int i=0; i<length; i++){
		//printf("index=%d, character=%c\n", i, matrix[i]);

		temp = strpbrk(matrix, ",:]");
		if (temp != NULL)
		{
		
		switch(*temp)
		{
			case ']':
			case ',':
			        {
	                        len = find_length(matrix, temp);
				number = convert_to_digit(temp,len);
				matrix_2D[row][column] = number;
				column++;
				break;
				}
			case ':':
				len =find_length(matrix,temp);
				number = convert_to_digit(temp,len);
				matrix_2D[row][column]=number;
				//assert(size->column == (column+1));
				row++;
				column=0;
				break;
			default :
				printf(" default case :%c\n", *temp);
		}

		

		matrix = ++temp;
	       }

	}
}

void find_size_of_matrix(char *start, size_of_matrix *size)
{
	bool column = true;
	bool row =true;
	while(start = strpbrk(start, " ,:"))
	{
	   switch(*start)
	   {
		case ',':
		        if(column){
			size->column++;
			}
			break;
		case ':':
		        column=false;
			size->row++;
			break;
		case ' ':
			break;
	   }

	   start++;
	}
	++size->column;
	++size->row;
}

void print_matrix(int ** matrix_2D, size_of_matrix *size)
{
	for(unsigned int row=0; row<size->row; row++)
	{
		for(unsigned int column=0; column < size->column; column++)
		{
			printf(" %d ", matrix_2D[row][column]);
		}

		printf("\n");
	}

}

void matrix_LU( int **A, int **L, int **U, unsigned int row, unsigned int column){

	
	unsigned int iteration;
	int pivot = 0;
	int fraction =0;
	unsigned int row_local = 0;
	unsigned int column_local = 0;

	for(iteration=0; iteration<(row -1); iteration++)
	{
		printf("iteration = %d\n", iteration);

		pivot = A[iteration][iteration];
		L[iteration][iteration] = 1;
		
		printf("fraction calculation\n");

		for(row_local=iteration+1; row_local<row; row_local++)
		{   
                        printf("(%d, %d) pivot=%d",row_local,iteration,pivot);
			
		        fraction = A[row_local][iteration]/pivot;
                        L[row_local][iteration] = fraction;
			
			printf("\n");
			for(column_local=iteration+1; column_local < column; column_local++)
			{
			   A[row_local][column_local] = A[row_local][column_local] -(fraction*A[row_local][column_local]); 
			}

			printf("\n");

		}
		printf("\n");

	}
}
