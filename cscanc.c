#include<stdio>
void main()
{
int a[20],n,i,j,sum=0,ini􀆟al,temp,ch,k;
prin􀆞("How many requests\n");
scanf("%d",&n);
prin􀆞("Enter the current(ini􀆟al) head posi􀆟on:\n");
scanf("%d",&ini􀆟al);
a[0]=0;
a[1]=ini􀆟al;
prin􀆞("Enter the Request Order:\n");
for(i=2;i<n+2;i++)
{
scanf("%d",&a[i]);
}
a[n+2]=199;
for(j=0;j<n+2;j++)
{
for(i=0;i<n+2;i++)
{
if(a[i]>a[i+1])
{
temp=a[i];
a[i]=a[i+1];
a[i+1]=temp;
}
}
}
for(i=0;i<n+2;i++)
{
if(a[i]==ini􀆟al)
{
k=i;
break;
}
}
prin􀆞("Press 1 to set direc􀆟on to le􀅌 and press 2 to set direc􀆟on to right:\n");
scanf("%d",&ch);
if(ch==1)
{
for(i=0;i<k;i++)
{
sum=sum+abs(a[i]-a[i+1]);
}
sum=sum+abs(a[0]-a[n+2]); //change
for(i=k+1;i<n+2;i++) //change
{
sum=sum+abs(a[i]-a[i+1]);
}
}
else
{
for(i=k;i<n+2;i++)
{
sum=sum+abs(a[i]-a[i+1]);
}
sum=sum+abs(a[n+2]-a[0]); //change
for(i=0;i<k-1;i++) //change
{
sum=sum+abs(a[i]-a[i+1]);
}
}
prin􀆞("\nTotal head movement = %d\n", sum);
}




