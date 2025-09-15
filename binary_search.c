#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int count;                      

int binarySearch(int key, int *a, int low, int high)
{
	count++;       
	
	int mid;
	mid=(high+low)/2;
	
	if(low>high)
	  return -1;
	  
	if(*(a+mid)==key)
	   return mid;
	else if(key>*(a+mid))
	   return binarySearch(key, a, mid+1, high);
	else
	  return binarySearch(key, a, low, mid-1);                
}

void tester()
{
	int *a, key, n, res;
	
	printf("Enter the number of elements: ");
	scanf("%d", &n);
	
	printf("Enter elements: ");
	for(int i=0; i<n; i++)
	{
		scanf("%d", (a+i));                           
	}
	
	printf("Enter key to be searched: ");
	scanf("%d", &key);
	
	res= binarySearch(key, a, 0, n-1);
	
	if(res==-1)
	  printf("Key not found\n");
	else
	  printf("Key found at position %d ", res+1);
}

void plotter()
{
	srand(time(NULL));
	
	int *arr;
	int key, n, r;
	
	FILE *f1, *f2, *f3;
	f1= fopen("binary_best.txt", "w");
	f2= fopen("binary_avg.txt", "w");
	f3= fopen("binary_worst.txt", "w");
	
	n=2;
	while(n<=1024)
	{
		arr= (int *)malloc(n*sizeof(int));                
		
		//best case--> mid
		for(int i=0; i<n; i++)
		  *(arr+i)=1;
		int mid= (n-1)/2;
		*(arr+mid)=0;
		
		count=0;                                          
		r= binarySearch(0, arr, 0, n-1);
		fprintf(f1, "%d\t%d\n", n, count);
		
		//avg case
		for(int i=0; i<n; i++)
		  *(arr+i)= i+1;
		
		key= rand()%n+1;                        
		count =0;
		
		r= binarySearch(key, arr, 0, n-1);
		fprintf(f2, "%d\t%d\n", n, count);
		
		//worst case-> not present in array
		for(int i=0; i<n; i++)
		  *(arr+i)= 0;
		count=0;
		r= binarySearch(1, arr, 0, n-1);
		
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
		printf("Enter your choice\n1.TEST\n2.PLOT\n3.EXIT\n");
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