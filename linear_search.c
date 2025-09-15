//to search for a key in a given array using linear search
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int count;                

int linearSearch(int *arr, int n, int key)
{
	count=0;
	for(int i=0; i<n; i++)
	{
		count++;                  
		if(*(arr+i)==key)
		{
			return i+1;
		}
	}
	return -1;
}

void tester()
{
	int *arr, n, key;
	int result;
	
	printf("Enter the number of elements :");
	scanf("%d", &n);
	
	arr=(int *)malloc(n*sizeof(int));
	
	printf("Enter the array elements: ");
	
	for(int i=0; i<n; i++)
	{
		scanf("%d", &arr[i]);	
	}
	
	printf("Enter the key element: ");
	scanf("%d", &key);
	
	result= linearSearch(arr, n, key);
	
	if(result==-1)
		printf("Element not found\n");

	else
		printf("The element %d is found at position %d\n", key, result);       
}

void plotter()
{
	int *arr, key, res;
	
	FILE *f1= fopen("linear_best.txt", "w");
	FILE *f2= fopen("linear_avg.txt", "w");
	FILE *f3= fopen("linear_worst.txt", "w");
	
	int n=2;                                 
	
	while(n<=1024)
	{
		arr= (int *)malloc(n*sizeof(int));    
		
		//BEST CASE
		for(int i=0; i<n; i++)
		   *(arr+i)=1;
		res= linearSearch(arr, n, 1);
		fprintf(f1, "%d\t%d\n", n, count);      
		
		//AVG CASE
		for(int i=0; i<n; i++)
		   *(arr+i)= rand()%n;
		key= rand()%n;
		
		res= linearSearch(arr, n, key);
		fprintf(f2, "%d\t%d\n", n, count);
		
		//WORST CASE 
		for(int i=0; i<n; i++)
		   *(arr+i)= 0;
		res= linearSearch(arr, n, 1);
		fprintf(f3, "%d\t%d\n", n, count);
		
		n= n*2;                               
		free(arr);                                            
	}
	
	fclose(f1);
	fclose(f2);
	fclose(f3);
}

void main()
{
	int ch;
	for(;;)
	{
		printf("Enter your choice\n1. TEST\n2. PLOT\n3. EXIT");
		scanf("%d", &ch);
		
		switch(ch)
		{
			case 1: tester();
			        break;
			        
			case 2: plotter();
			        break;
			        
			case 3: exit(0);
		}
	}
}