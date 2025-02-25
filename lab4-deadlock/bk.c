#include<stdio.h>

int allocated[100][100];
int maximum[100][100];
int need[100][100];
int available[100];
int finished[100];

int issafe(int p,int r){
    int work[100];
    for(int i=0;i<r;i++){
        work[i] = available[i];
    }

    for(int i=0;i<p;i++){
        finished[i]=0;
    }

    int safesequence[p];
    int count=0;

    while(count<p){
        int found=0;
        for(int i=0;i<p;i++){
            if(!finished[i]){
                int j;
                for(j=0;j<r;j++){
                    if(need[i][j]>work[j]){
                        break;
                    }
                }
                if(j==r){
                    for(int k=0;k<r;k++){
                        work[k] += allocated[i][k];
                    }
                    safesequence[count++] = i;
                    finished[i]=1;
                    found =1;
                }
            }
        }
        if(!found){
            printf("No safe sequence\n");
            return 0;
        }
    }

    printf("Safe sequence- \n");
    for(int i=0;i<p;i++){
        printf("%d ",safesequence[i]);
    }
    printf("\n");
    return 1;
}

int main(){
    int p,r;
    printf("Enter the no of processes: ");
    scanf("%d",&p);

    printf("Enter the number of resources: ");
    scanf("%d",&r);

    printf("Enter the allocation matrix: \n");
    for(int i=0;i<p;i++){
        for(int j=0;j<r;j++){
            scanf("%d",&allocated[i][j]);
        }
    }

    printf("Enter the maximum matrix: ");
    for(int i=0;i<p;i++){
        for(int j=0;j<r;j++){
            scanf("%d",&maximum[i][j]);
        }
    }

    printf("Enter the available resources: ");
    for(int i=0;i<r;i++){
        scanf("%d",&available[i]);
    }

    for(int i=0;i<p;i++){
        for(int j=0;j<r;j++){
            need[i][j] = maximum[i][j] - allocated[i][j];
        }
    }

    issafe(p,r);
    return 0;
}