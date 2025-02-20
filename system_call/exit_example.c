#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int x;
	printf("Enter 1 or 2: ");
	scanf("%d", &x);
	if(x==1){
		printf("You pressed 1!");
	}
	else{
		exit(0);
	}
}
