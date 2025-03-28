#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node
{
	char fname[25];
	int length,start;
	struct node *next;
}NODE;

NODE *first,*last;
int n,bit[300],fb;

void init()
{	
	printf("How many blocks:");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		bit[i]=1;
	fb=n;
}

void show_bit_vector()
{
	for(int i=0;i<n;i++)
	printf("%d\t",bit[i]);
}

void create()
{
	NODE *f;
	int i,j;
	char fname[25];
	int len;
	printf("Enter name and length of file:\t");
	scanf("%s%d",&fname,&len);
	
	f=(NODE *)malloc(sizeof(NODE));
	
	if(fb > len)
	{
		strcpy(f->fname,fname);
		f->length=len;
		
		for(i=0;i<n;i++)
		{
			if(bit[i]==1)
				break;
		}
		
		f->start=i;
		f->next=NULL;
		
		if(first==NULL)
			first=f;
		else
			last->next=f;
		
		last=f;
		fb-=len;
		j=i+1;
		
		while(len>0)
		{
			if(bit[i]==1)
			{
				bit[i]=0;
				len--;
				i=j;
			}	
			j++;
		}
		
		bit[i]=f->start+f->length;
		printf("File Created SuccessFully...");
		
		
	}
	else
	{
		printf("File not Created :(");
	}
	
	
}

void show_dir()
{
	NODE *f;
	f=first;
	printf("File\tStart\tLength\n");
	while(f->next!=NULL)
	{
		printf("%s\t%d\t%d\n",f->fname,f->start,f->length);
		f=f->next;
	}
}



int main()
{
	int ch;
	init();
	printf("1.Show Bit Vector\n");
	printf("2.Show Dir\n");
	printf("3.Create File\n");
	printf("4.Exit\n");
	printf("Enter your Choice:");
	scanf("%d",&ch);
	if(ch==1)
		show_bit_vector();
	else if(ch==2)
		show_dir();
	else if(ch==3)
		create();
	else if(ch==4)
		exit(0);
	else 
		printf("Invalid choise...");
}




    