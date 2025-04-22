#include<stdio.h>

int mem_size;

int main(){
    printf("Enter size of memory: ");
    scanf("%d",mem_size);

    printf("Enter the no of processes")

    int process_size;
    printf("Enter the size of process: ");
    scanf("%d",&process_size);

    if(process_size<=mem_size){
        mem_size -= process_size;
        printf("Process was allocated memory successfully\n");
    }
    else{
        "Memory not available\n";
    }
}