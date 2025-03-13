#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int full = 0, item = 0, mutex = 1, empty = 3;

int wait(int s) {
    return (--s);
}

int signal(int s) {
    return (++s);
}

void *Producer(void *arg) {
    while (1) {
        mutex = wait(mutex);
        if (empty != 0) {
            empty = wait(empty);
            full = signal(full);
            item++;
            printf("\nProducer produced item %d", item);
            sleep(rand() % 3);
        } else {
            printf("\nBuffer is full");
            mutex = signal(mutex);
            break;
        }
        mutex = signal(mutex);
    }
    pthread_exit(NULL);
}

void *Consumer(void *arg) {
    while (1) {
        mutex = wait(mutex);
        if (full != 0) {
            full = wait(full);
            empty = signal(empty);
            printf("\nConsumer consumed item %d", item);
            item--;
            sleep(rand() % 3);
        } else {
            printf("\nBuffer is empty");
            mutex = signal(mutex);
            break;
        }
        mutex = signal(mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    srand(time(0));

    if (pthread_create(&producer_thread, NULL, Producer, NULL)) {
        printf("\nError creating producer thread");
        return 1;
    }
    if (pthread_create(&consumer_thread, NULL, Consumer, NULL)) {
        printf("\nError creating consumer thread");
        return 1;
    }

    if (pthread_join(producer_thread, NULL)) {
        printf("\nError joining producer thread");
        return 1;
    }
    if (pthread_join(consumer_thread, NULL)) {
        printf("\nError joining consumer thread");
        return 1;
    }

    return 0;
}


/* #include  <stdio.h>
#include <stdlib.h>

int full = 0, item = 0, mutex = 1, empty = 3;

int wait(int s){
	return (--s);
}

int signal(int s){
	return (++s);
}

void Producer(){
	mutex = wait(mutex);
	full = signal(full);
	empty = wait(empty);
	item++;
	printf("\nProducer produced %d item", item);
	mutex = signal(mutex);
}

void Consumer(){
	mutex = wait(mutex);
	full = wait(full);
	empty = signal(empty);
	printf("\nConsumer consumed %d item", item);
	item--;
	mutex = signal(mutex);
}

int main(){
	int ch;
	
	while(1){
			 printf("\nMenu\n1.Produce Item\n2.Consume Item\n3.Exit\nEnter Your Choice:");
			 scanf("%d",&ch);
			 switch(ch){
			 	case 1:
			 		if((mutex == 1) && (empty != 0)){
			 			Producer();
			 		}
			 		else{
			 			printf("\nBuffer is full");
			 		}
			 		break;
			 	case 2:
			 		if((mutex == 1) && (full != 0)){
			 			Consumer();
			 		}
			 		else{
			 			printf("\nBuffer is empty");
			 		}
			 		break;
			 	case 3:
			 		exit(0);
			 		break;
			 	default :
			 		printf("Enter a valid option");
			 		break;
			 }
		}
} */
