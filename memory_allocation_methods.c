#include <stdio.h>
#include <stdlib.h>

typedef struct mB {
    int size;
    int allocated;
    struct mB *next;
} mB;

mB *head = NULL;

mB* createMemoryBlock(int size) {
    mB *block = (mB*)malloc(sizeof(mB));
    block->size = size;
    block->allocated = 0;
    block->next = head;
    head = block;
    return block;
}

void print_memory() {
    mB *temp = head;
    while(temp != NULL) {
        printf("Block size: %d, Allocated: %s\n", temp->size, temp->allocated ? "Yes" : "No");
        temp = temp->next;
    }
}

void first_fit(int size) {
    mB *temp = head;
    while(temp != NULL) {
        if(!temp->allocated && temp->size >= size) {
            temp->allocated = 1;
            printf("Allocated %d size using First Fit\n", size);
            return;
        }
        temp = temp->next;
    }
    printf("Not enough memory to allocate %d size using First Fit\n", size);
}

void worst_fit(int size) {
    mB *temp = head;
    mB* worst = NULL;
    
    while(temp != NULL) {
        if(!temp->allocated && temp->size >= size) {
            if(worst == NULL || temp->size > worst->size) {
                worst = temp;
            }
        }
        temp = temp->next;
    }
    
    if(worst != NULL) {
        worst->allocated = 1;
        printf("Allocated %d size using Worst Fit\n", size);
    }
    else {
        printf("Not enough memory to allocate %d size using Worst Fit\n", size);
    }
}

void best_fit(int size) {
    mB *temp = head;
    mB *best = NULL;
    
    while(temp != NULL) {
        if(!temp->allocated && temp->size >= size) {
            if(best == NULL || temp->size < best->size) {
                best = temp;
            }
        }
        temp = temp->next;
    }
    
    if(best != NULL) {
        best->allocated = 1;
        printf("Allocated %d size using Best Fit\n", size);
    }
    else {
        printf("Not enough memory to allocate %d size using Best Fit\n", size);
    }
}

int main() {
    int num_blocks, block_size, allocation_size, choice;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &num_blocks);

    for (int i = 0; i < num_blocks; i++) {
        printf("Enter size of block %d: ", i + 1);
        scanf("%d", &block_size);
        createMemoryBlock(block_size);
    }

    while(1) {
        printf("\nMemory Allocation Menu:\n");
        printf("1. First Fit Allocation\n");
        printf("2. Worst Fit Allocation\n");
        printf("3. Best Fit Allocation\n");
        printf("4. Print Memory\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter the size of memory to allocate (First Fit): ");
                scanf("%d", &allocation_size);
                first_fit(allocation_size);
                break;

            case 2:
                printf("Enter the size of memory to allocate (Worst Fit): ");
                scanf("%d", &allocation_size);
                worst_fit(allocation_size);
                break;

            case 3:
                printf("Enter the size of memory to allocate (Best Fit): ");
                scanf("%d", &allocation_size);
                best_fit(allocation_size);
                break;

            case 4:
                printf("Current memory state:\n");
                print_memory();
                break;

            case 5:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

