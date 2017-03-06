#include <stdio.h>
#include <stdlib.h>

/*
.......................................
.......................................
             4th  
       Matrix Addition
.......................................
.......................................
                                         */      


int main(int argc, char const *argv[])
{
	

    if(argc!=2)
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

    //check if the file exists, but is empty

    fseek(fileptr, 0, SEEK_END);
    if(ftell(fileptr)==0)
    {
    	printf("\n");
    	return 0;
    }
    fseek(fileptr, 0, SEEK_SET);

    int row, col; 
    int bc=fscanf(fileptr, "%d\t%d\n", &row, &col);
    if(bc!=2)
    {
    	printf("error\n");
    	return 0;
    }
    else
    {
    fseek(fileptr, 0, SEEK_SET);

    fscanf(fileptr, "%d\t%d\n", &row, &col);

    if(col<1||row<1)
    {
    	printf("error\n");
    	return 0;
    }
    int **M1=(int**)malloc(sizeof(int *) * row);
    int **M2=(int**)malloc(sizeof(int *) * row);

    //malloc space for each col
    int i;
    for(i=0; i<row; i++)
    {
    	M1[i]=(int *)malloc(sizeof(int)*col);
    	M2[i]=(int *)malloc(sizeof(int)*col);
    }
    int j, add;// down=0;
    //populate both arrays :-)

    
    	for(i=0; i<row; i++)
        {
    		if(col==1)
    	 {
    		fscanf(fileptr, "%d\n", &add );
    		M1[i][0]=add;
    	 }
    	   else
    	   {
    	   	for(j=0; j<col-1; j++)
    		{
    			fscanf(fileptr, "%d\t", &add );
    			M1[i][j]=add;
    		}
    		fscanf(fileptr, "%d\n", &add );
    		M1[i][j]=add;
    	   }
    	}

    	//populate second array
    	for(i=0; i<row; i++)
        {
    		if(col==1)
    	 {
    		fscanf(fileptr, "%d\n", &add );
    		M2[i][0]=add;
    	 }
    	   else
    	   {
    	   	for(j=0; j<col-1; j++)
    		{
    			fscanf(fileptr, "%d\t", &add );
    			M2[i][j]=add;
    		}
    		fscanf(fileptr, "%d\n", &add );
    		M2[i][j]=add;
    	   }
    	}

    	int **M3=(int **)malloc(sizeof(int *)*row);
    	for(i=0; i<row; i++)
    	{
    		M3[i]=(int *)malloc(sizeof(int)*col);
    	}
    	//add matrix and store into m3

    	for(i=0; i<row; i++)
    	{
    		for(j=0; j<col; j++)
    		{
    			M3[i][j]=M1[i][j]+M2[i][j];
    		}
    	}


      

    for(i=0; i<row; i++)
    {
    	for(j=0; j<col; j++)
    	{
    		printf("%d\t", M3[i][j] );
    	}
        printf("\n");
    }

    int *curr;
    for(i=0; i<row; i++)
    {
    	curr=M1[i];
    	free(curr);
    }
     free(M1);
     for(i=0; i<row; i++)
    {
    	curr=M2[i];
    	free(curr);
    }
    free(M2);
     for(i=0; i<row; i++)
    {
    	curr=M3[i];
    	free(curr);
    }
    free(M3); 
    fclose(fileptr);
    return 0;
}
}
