#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        printf("Child process (PID: %d)\n", getpid());
        char *args[] = {"ls", NULL};
        execvp(args[0], args);
        perror("Exec failed");
        exit(EXIT_FAILURE);
    } else {
        printf("Parent process (PID: %d)\n", getpid());
        wait(NULL);
        printf("Child process finished\n");

        int fd = open("testfile.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
        if (fd == -1) {
            perror("File open failed");
            exit(EXIT_FAILURE);
        }
        write(fd, "Hello, World!\n", 14);
        close(fd);

        struct stat file_stat;
        stat("testfile.txt", &file_stat);
        printf("File size: %ld bytes\n", file_stat.st_size);

        DIR *dir = opendir(".");
        if (dir) {
            struct dirent *entry;
            while ((entry = readdir(dir)) != NULL) {
                printf("Found file: %s\n", entry->d_name);
            }
            closedir(dir);
        } else {
            perror("opendir failed");
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}

