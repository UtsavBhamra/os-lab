#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
	pid_t p = fork();
	if(p<0){
		printf("fork failed;\n");
	}
	else{
		if(p==0){
			printf("hello from child process with pid %d\n",getpid());
		}
	        else{
		    printf("hello from parent process with pid=%d\n",getpid());
        	}
	}
	return 0;
}
