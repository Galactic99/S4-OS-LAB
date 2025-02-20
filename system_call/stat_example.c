#include <stdio.h>
#include <sys/stat.h>

int main() {
    struct stat st;
    stat("close_example.c", &st); 
    printf("File size: %ld bytes\n", st.st_size);
    return 0;
}

