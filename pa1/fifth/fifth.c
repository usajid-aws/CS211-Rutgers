#include <stdio.h>
#include <stdlib.h>



int main(int argc, char const *argv[])
{
	if(argc<2)
	{
		printf("error\n");
		return 0;
	}

    FILE *fileptr=fopen(argv[1], "r");
    if(fileptr==NULL)
    {
    	printf("error\n");
    	return 0;
    }
    //checking for empty file
    fseek(fileptr, 0, SEEK_END);
    if(ftell(fileptr)==0)
    {
    	printf("\n");
    	return 0;
    }
    fseek(fileptr, 0, SEEK_SET);


    int row1, col1, row2, col2; 
    //first matrix
    fscanf(fileptr, "%d\t%d", &row1, &col1);

    if(col1<1||row1<1)
    {
    	printf("error\n");
    	return 0;
    }
    int **matrix1=(int **)malloc(sizeof(int *)*row1);

    int i;
    for(i=0; i<row1; i++)
    {
    	matrix1[i]=(int *)malloc(sizeof(int)*col1);
    }

    //populate first array 
    int j, add;
    for(i=0; i<row1; i++)
    {
    	if(col1==1)
    	{
            fscanf(fileptr, "%d\n", &add);
            matrix1[i][0]=add;
    }
    	else 
    	{
    		for(j=0; j<col1-1; j++)
    		{
    			fscanf(fileptr, "%d\t", &add );
    			matrix1[i][j]=add;
    		}
    		fscanf(fileptr, "%d\n", &add );
    		matrix1[i][j]=add;
    	}
    }
    //create and populate second array
    
    fscanf(fileptr, "%d\t%d", &row2, &col2);
    if(col2<1||row2<1)
    {
    	printf("error\n");
    	return 0;
    }
    int **matrix2=(int **)malloc(sizeof(int *)*row2);

   
    for(i=0; i<row2; i++)
    {
    	matrix2[i]=(int *)malloc(sizeof(int)*col2);
    }

    for(i=0; i<row2; i++)
    {
    	if(col2==1)
    	{
            fscanf(fileptr, "%d\n", &add);
            matrix2[i][0]=add;
    }
    	else 
    	{
    		for(j=0; j<col2-1; j++)
    		{
    			fscanf(fileptr, "%d\t", &add );
    			matrix2[i][j]=add;
    		}
    		fscanf(fileptr, "%d\n", &add );
    		matrix2[i][j]=add;
    	}
    }

    

    int **matrix3=(int **)malloc(sizeof(int *)*row1);

    for(i=0; i<row1; i++)
    {
    	matrix3[i]=(int *)malloc(sizeof(int)*col2);
    }

    //multiply m1 and m2 and populate m3
    //check if col1 and row2 are equal
    int down, r1, r2;
    if(col1==row2) //matrices are capable to be multiplied 
    {
    	
    	for(i=0; i<row1; i++)
    	{
    		for(j=0; j<col2; j++)
    		{
    			for(down=0; down<col1; down++)
    			{
    				r1=matrix1[i][down];
    				r2=matrix2[down][j];
    				matrix3[i][j]+=r1*r2;
    			}
    		}
    	}

    }
    else
    {
    	printf("error\n");
    	return 0;
    }

    //print matrix   
   // printf("%d\n", matrix3[0][0]);

    	for(i=0; i<row1; i++)
      {
    	for(j=0; j<col2-1; j++)
    	{
    		printf("%i\t", matrix3[i][j] );
    	}
    	printf("%d\n", matrix3[i][j] );
      }
    
    //free all matrices
    int *curr;
    for(i=0; i<row1; i++)
    {
    	curr=matrix1[i];
    	free(curr);
    }
     free(matrix1);
     for(i=0; i<row2; i++)
    {
    	curr=matrix2[i];
    	free(curr);
    }
    free(matrix2);
     for(i=0; i<row1; i++)
    {
    	curr=matrix3[i];
    	free(curr);
    }
    free(matrix3);
    fclose(fileptr);
    return 0;


return 0;
}
