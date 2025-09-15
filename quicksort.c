#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int count;

void swap(int *a, int *b)
{
	int temp= *a;
	*a= *b; 
	*b= temp;
}

int partition(int *arr, int beg, int end)
{
	int pivot= arr[beg];
	int i=beg;
	int j= end+1;              
	
	do
	{
		do
		{
			count++;
			i++;
		} while(arr[i]<pivot);
		
		do
		{
			count++;
			j--;
		} while(arr[j]>pivot);
		
		swap(&arr[i], &arr[j]);
		
	}while(i<j);
	
	swap(&arr[i], &arr[j]);
	swap(&arr[beg], &arr[j]);
	return j;                
}

void quicksort(int *arr, int beg, int end)
{
	if(beg<end)            
	{
		int split= partition(arr, beg, end);
		
		quicksort(arr, beg, split-1);
		quicksort(arr, split+1, end);
	}
}

void tester()
{
	int *arr, n;
	
	printf("Enter the number of elements: ");
	scanf("%d", &n);
	
	arr= (int *)malloc(n*sizeof(int));
	
	printf("Enter the elements: ");
	for(int i=0; i<n;i++)
	{
		scanf("%d", &arr[i]);
	}
	
	quicksort(arr, 0, n-1);
	
	printf("Sorted array: ");
	for(int i=0; i<n; i++)
	  printf("%d ", arr[i]);
	
	printf("\n");
}

void plotter()
{
	int *arr, n;
	
	srand(time(NULL));
	
	FILE *f1, *f2, *f3;
	f1= fopen("quick_best.txt", "w");
	f2= fopen("quick_avg.txt", "w");
	f3= fopen("quick_worst.txt", "w");
	
	n=4;
	
	while(n<=1024)
	{
		arr= (int *)malloc(n*sizeof(int));
		
		//BEST CASE
		for(int i=0; i<n; i++)
		  arr[i]= 5;
		
		count=0;
		quicksort(arr, 0, n-1) ;
		fprintf(f1, "%d\t%d\n", n, count);
		
		//AVG case--> random elements
		for(int i=0; i<n; i++)
		  arr[i]= rand()%n;
	    
	    count=0;
	    quicksort(arr, 0, n-1);
	    fprintf(f2, "%d\t%d\n", n, count);
	    
	    //WORST CASE--> SORTED ARRAY 
	    for(int i=0; i<n; i++)
	      arr[i]= i+1;
	      
	    count=0;
	    quicksort(arr, 0, n-1);
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
		printf("Enter choice\n1.TEST\n2.PLOT\n");
		scanf("%d", &ch);
		switch(ch)
		{
			case 1: tester();
			        break;
			case 2: plotter();
			        break;
			default: exit(0);
		}
	}
}