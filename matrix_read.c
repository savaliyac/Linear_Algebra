/*
 * This program takes NxN matrix as input from the command line. 
 *  
 */


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>


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

unsigned int find_size_of_matrix(char *);

/*
 * Display the NxN matrix on terminal
 */
void print_matrix(int**, unsigned int);

/*
 * main function
 */

int main (int argc, char * argv[]){
        
	unsigned int length =0,size=0;


	int **matrix_2D = NULL;
	
	if(argc == 1){
		printf("Number of input parameter =1\n");
		printf("Terminating execution\n");
		return 0;
	}
	
	else if (argc >=2){
	char * stack = (char*)malloc(atoi(argv[1]));

}
          
	  char *data = argv[2];
	  length = strlen(argv[2]);

       

	
        size = find_size_of_matrix(data);

	matrix_2D = (int **)malloc(size * sizeof(int*));

	for(unsigned int i=0; i<size; i++)
		matrix_2D[i] = (int *)malloc(sizeof(int)*size);
	
	prepare_matrix(++data,length, matrix_2D);
        print_matrix(matrix_2D,size);
	
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
    
    //unsigned int value;
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

unsigned int find_size_of_matrix(char *start)
{
	unsigned int size=0;
	bool finish = true;
	while((start = strpbrk(start, " ,:")) && finish)
	{
	   switch(*start)
	   {
		case ',':
			size++;
			break;
		case ':':
		        finish=false;
			break;
		case ' ':
			break;
	   }

	   start++;
	}

	return (size+1);
}

void print_matrix(int ** matrix_2D, unsigned int size)
{
	for(unsigned int row=0; row<size; row++)
	{
		for(unsigned int column=0; column < size; column++)
		{
			printf(" %d ", matrix_2D[row][column]);
		}

		printf("\n");
	}

}
