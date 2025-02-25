#include <stdio.h>
#include <stdlib.h>

typedef struct Process
{
	int pid;
	int arrival;
	int burst;
	int done;
} Process;

static int time=0;

int compare(const void * p1,const void* p2)
{
	return ((Process*)p1)->arrival>((Process*)p2)->arrival;
}

int main()
{
	int n;
	printf("Enter number of processes: ");
	scanf("%d",&n);
	printf("Enter pid arrival and burst:\n");
	Process processes[n];

	for(int i=0;i<n;i++)
	{
		scanf("%d %d %d",&processes[i].pid,&processes[i].arrival,&processes[i].burst);
		processes[i].done=0;
	}

	qsort(processes,n,sizeof(Process),compare);

	int done=0;
	int order[n];
	time=processes[0].arrival;
	while(done<n)
	{
		int proc=0;
		int min=999999;
		int found=0;
		for(int i=0;i<n;i++)
		{
			if(!processes[i].done && processes[i].arrival<=time && processes[i].burst<min)
			{
				proc=i;
				min=processes[i].burst;
				found=1;
			}	
		}

		if(processes[proc].done)
		{
			printf("%d %d\n",time,done);
			time++;
			continue;
		}

		printf("%d %d\n",proc,time);
		time+=processes[proc].burst;
		order[done++]=processes[proc].pid;
		processes[proc].done=1;

	}

	for(int i=0;i<n;i++)
	{
		printf("%d ",order[i]);
	}
	printf("\n");

}