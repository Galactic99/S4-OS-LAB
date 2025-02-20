#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	fork();
	printf("HEllo\n");
	if(fork() == 0){
		sleep(1);
		return 0;
	}else{
		wait(NULL);
	}
}
		
