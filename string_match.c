#include<stdio.h>
#include<stdlib.h>

#include<string.h>
#include<stdbool.h>

#include<time.h>

int count;

bool strmatch(char *pattern, char *text, int m, int n)      
{
	count=0;
	for(int i=0; i<=n-m; i++)       
	{
		int j=0;
		while(j<m)
		{
			count++;
			if(pattern[j]!=text[i+j])
			   break;
			j++;
		}
		if(j==m)
		   return true;
	}
	
	return false;
}

void tester()
{
	int m, n;
	char text[1000], pattern[1000];
	
	printf("Enter the text length: ");
	scanf("%d", &n);
	getchar();                                   
	
	printf("Enter the text: ");
	fgets(text, sizeof(text), stdin);
	text[strcspn(text, "\n")]=0;      
	// or n= strlen(text);
	
	printf("Enter pattern length: ");
	scanf("%d", &m);
	getchar();
	
	printf("Enter the pattern");
	fgets(pattern, sizeof(pattern), stdin);
	pattern[strcspn(pattern, "\n")]=0;
	// or m= strlen(pattern);
	
	bool ans= strmatch(pattern, text, m, n);
	
	if(ans)
	  printf("String found\n");
	else
	  printf("String not found\n");
}

void plotter()
{
	srand(time(NULL));
	
	FILE *f1, *f2, *f3;
	f1= fopen("str_best.txt", "w");
	f2= fopen("str_avg.txt", "w");
	f3= fopen("str_worst.txt", "w");

	int n=1000;
	
	char *text = (char *)malloc(1000*sizeof(char));
	
	for(int i=0; i<n; i++)
	{
		text[i]= 'a' ;
	}
	
	for(int m=10; m<=1000; m +=10)
	{
		char *pattern;
		pattern= (char *)malloc((m+1)*sizeof(char));         
		
		for(int i=0; i<m; i++)
		  pattern[i]= 'a';
		
		//best case
		pattern[m]= '\0';                
		strmatch(pattern, text, m, n);
		fprintf(f1, "%d\t%d\n", m, count);                   
		
		//WORST case
		pattern[m-1]= 'b';                                 
		strmatch(pattern, text, m, n);
		fprintf(f3, "%d\t%d\n", m, count);
		
		//avg case
		for(int i=0; i<m; i++)
		  pattern[i]= 'a'+rand()%3;
		pattern[m]= '\0';                                  
		strmatch(pattern, text, m, n);
		fprintf(f2, "%d\t%d\n", m, count);
		
		free(pattern);                                     
	}
	free(text);                                           
	
	fclose(f1);
	fclose(f2);
	fclose(f3);
}

void main()
{
	int ch;
	for(;;)
	{
		printf("Enter choice:\n1.TEST\n2.PLOT\n");
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