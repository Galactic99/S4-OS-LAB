#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/wait.h> // Include header for wait()

#define SHM_NAME "/my_shared_memory"  // Shared Memory Name
#define SEM_NAME "/my_semaphore"      // Semaphore Name

int main() {
    const size_t SHM_SIZE = sizeof(int);  // Size of shared memory (integer type)

    // Create or open a shared memory object
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("Failed to open shared memory");
        exit(EXIT_FAILURE);
    }

    // Set the size of the shared memory object
    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        perror("Failed to set shared memory size");
        exit(EXIT_FAILURE);
    }

    // Map the shared memory object into the address space of this process
    int* shared_memory = (int*)mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_memory == MAP_FAILED) {
        perror("Failed to map shared memory");
        exit(EXIT_FAILURE);
    }

    // Create a semaphore for synchronization
    sem_t* semaphore = sem_open(SEM_NAME, O_CREAT, 0666, 0);
    if (semaphore == SEM_FAILED) {
        perror("Failed to create semaphore");
        exit(EXIT_FAILURE);
    }

    // Forking to create writer and reader processes
    pid_t pid = fork();
    
    // Writer Process: Writes to shared memory
    if (pid == 0) {
        for (int i = 0; i < 5; i++) {
            printf("Writer: Writing value %d to shared memory\n", i);
            *shared_memory = i;  // Write value to shared memory
            sem_post(semaphore); // Signal the reader
            sleep(1);            // Simulate work delay
        }
        exit(0);  // Exit writer process
    }
    
    // Reader Process: Reads from shared memory
    if (pid > 0) {
        for (int i = 0; i < 5; i++) {
            sem_wait(semaphore);  // Wait until the writer posts data
            printf("Reader: Read value %d from shared memory\n", *shared_memory);
        }

        // Wait for writer process to finish
        wait(NULL);

        // Clean up shared memory and semaphore after use
        shm_unlink(SHM_NAME);
        sem_unlink(SEM_NAME);
    }

    // Unmap shared memory and close file descriptor
    munmap(shared_memory, SHM_SIZE);
    close(shm_fd);

    // Close semaphore
    sem_close(semaphore);

    return 0;
}

