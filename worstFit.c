#include <stdio.h>
#include <stdlib.h>

struct memory_block{
    int size;
    int proc_size;
    int is_free;
    struct memory_block* next;
};

struct memory_block* head = NULL;

void create_memory(int size){
    struct memory_block* new_block = (struct memory_block*)malloc(sizeof(struct memory_block));
    new_block->size = size;
    new_block->is_free = 1;
    
    if(head == NULL){
        head = new_block;
        new_block->next = NULL;
    }
    else {
        new_block->next = head;
        head = new_block;
    }
}

int allocate_memory(int block_size){
    struct memory_block* ptr = head;
    struct memory_block* best = NULL;
    
    while(ptr){
        if(ptr->is_free && ptr->size >= block_size){
            if(best == NULL || ptr->size > best->size){
                best = ptr;
            }
        }
        ptr = ptr->next;
    }
    
    if(best){
        best->is_free = 0;
        best->proc_size = block_size;
    }
}

void print_memory(){
    struct memory_block * ptr = head;
    while(ptr){
        printf("Block Size: %d\t\t Process Size: %d\t\t Status: %d\n", ptr->size, ptr->proc_size, ptr->is_free);
        ptr = ptr->next;
    }
}

void main(){
    create_memory(100);
	create_memory(500);
	create_memory(250);
	create_memory(50);
	create_memory(600);
	
	int ch = 1, size;
	
	while(ch){
	    printf("Enter the size of the memory to be allocated: ");
		scanf("%d",&size);
		allocate_memory(size);
		print_memory();
		printf("Enter 1 to continue, To exit enter 0: ");
		scanf("%d",&ch);
	}
}
