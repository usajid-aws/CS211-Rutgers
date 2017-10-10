#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


//will take a number input and will check if number is prime 

bool isPrime(int i){
	//bool prime=false;
	int x=i-1;
	while(x>1)
	{
		if(i%x==0){
			return false;
		}
		x--;
	}
	return true;
}

int main(int argc, char const *argv[])
{   

	if(argc<2)
	{
		printf("error\n");
		return 0;
	}
	
	bool prime=isPrime(atoi(argv[1]));
	if(prime==true)
	{
		printf("yes\n");
		return 0;
	}
	else
	{
        printf("no\n");
        return 0;
	}
	//return 0; 
}