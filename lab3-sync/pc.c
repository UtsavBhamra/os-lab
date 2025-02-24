#include<stdio.h>
#include<stdlib.h>

int mutex = 1;
int full = 0;
int empty;
int x=0;

void producer(){
    mutex--;
    full++;
    empty--;
    x++;
    printf("Producer produces item %d\n",x);
    mutex++;
}

void consumer(){
    mutex--;
    full--;
    empty++;
    printf("Consumer consumed item %d\n",x);
    mutex++;
}

int main(){
    int n;

    printf("Enter the buffer size: ");
    scanf("%d",&empty);

    printf("1. Producer");
    printf("\n2. Consumer");
    printf("\n3. Exit\n");

    #pragma omp critical
    while(1){
        printf("Enter your choice: ");
        scanf("%d",&n);

        switch(n) {
            case 1:
                if(mutex==1 && empty!=0){
                    producer();
                }
                else{
                    printf("Buffer is full\n");
                }
                break;
            case 2:
                if(mutex==1 && full!=0){
                    consumer();
                }
                else{
                    printf("Buffer is empty\n");
                }
                break;
            case 3:
                exit(EXIT_SUCCESS);
                break;
            default:
                printf("Invalid Choice \n");
        }
    }
    return 0;
}