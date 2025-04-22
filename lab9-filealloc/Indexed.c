// c program to simulate indexed file allocation
#include <stdio.h>
#include <string.h>
int main()
{
	int f[50],index[50],i,j,k,n,c,count=0,p;
	for(i=0;i<50;i++)
	f[i]=0;
	x:
	printf("Enter index block : ");
	scanf("%d",&p);
	if(f[p]==0)
	{
		f[p]=1;
		printf("Enter no of files on index : ");
		scanf("%d",&n);
	}
	else
	{
		printf("Block already allocated\n");
		goto x;
	}
	for(i=0;i<n;i++)
	scanf("%d",&index[i]);
	for(i=0;i<n;i++)
	if(f[index[i]]==1)
	{
		printf("Block already allocated");
		goto x;
	}
	for(j=0;j<n;j++)
	f[index[j]]=1;
	printf("\nAllocated");
	printf("\nFile Indexed");
	for(k=0;k<n;k++)
	printf("\n%d->%d:%d",p,index[k],f[index[k]]);
	printf("Do you want to continue file allocation (1-Yes/0-No) : ");
	scanf("%d",&c);
	if(c==1)
	goto x;
	return 0;
}
