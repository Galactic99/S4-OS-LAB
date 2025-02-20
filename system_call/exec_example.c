#include <stdio.h>
#include <unistd.h>

int main(){
	execlp("ls", "ls", "-l", (char*)NULL);
	printf("exec() was not successfull");
}
