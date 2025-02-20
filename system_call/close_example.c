#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	int fd = open("fork_example.c", O_CREAT | O_WRONLY, 0644);
	printf("%d", fd);
	close(fd);
}
