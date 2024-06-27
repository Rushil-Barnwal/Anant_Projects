#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define FILE_NAME "comm.txt"

int main() {
    int fd;
    pid_t pid;

    // Create a file for communication
    fd = open(FILE_NAME, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Fork a child process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) { // Child process
        char buffer[1024];
        int n;
        // Wait for the parent to write
        // Read from the file
        lseek(fd, 0, SEEK_SET);
        n = read(fd, buffer, 1024);
        printf("Child read: %s\n", buffer);
        // Write to the file
        char message[1000];
	printf("Child input\n");
	fgets(message, 1000, stdin);
        write(fd, message, strlen(message));
    } else { // Parent process
        char buffer[1024];
        int n;
        // Write to the file
        char message[1000];
	wait(NULL);
	printf("Parent input\n");
	fgets(message, 1000, stdin);
        write(fd, message, strlen(message));
        // Read from the file
        lseek(fd, 0, SEEK_SET);
	printf("Parent read\n");
        n = read(fd, buffer, 1024);
        printf("Parent read: %s\n", buffer);
    }

    // Close the file descriptor
    close(fd);

    return 0;
}
