#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/sendfile.h>

#define PORT 5050
#define BACKLOG 1
#define BUFF_SIZE 256

int main(void) {
    int server_fd = socket(AF_INET,SOCK_STREAM,0);
    if(server_fd == -1) {
        perror("socket()");
        return 1;
    }

    struct sockaddr_in address = {
        AF_INET,
        htons(PORT),
        INADDR_ANY,
    };

    int addrlength = sizeof(address);
    if(bind(server_fd,(struct sockaddr*)&address,(socklen_t)addrlength)==-1) {
        perror("bind()");
        close(server_fd);
        return 1;
    }

    if(listen(server_fd,BACKLOG)==-1) {
        perror("listen()");
        close(server_fd);
        return 1;
    }
    
    printf("Server is now listening on port 5050...\n");

    int client_fd = accept(server_fd,0,0);
    if(client_fd == -1) {
        perror("accept()");
        close(server_fd);
        return 1;
    }

    char buffer[BUFF_SIZE];
    if(recv(client_fd,buffer,BUFF_SIZE,0)==-1) {
        perror("recv()");
        close(client_fd);
        close(server_fd);
        return 1;
    }

    char *filename = buffer;
    filename += 5; //skips the first 5 characters, that means that is going to skip the GET / and then we can get the filename

    *(strchr(filename,' ')) = '\0'; //this line of code finds the first whitespace and puts a null terminator there so we can keep only the filename

    int file_fd = open(filename,O_RDONLY,0);
    if(file_fd == -1) {
        perror("open()");
        close(client_fd);
        close(server_fd);
        return 1;
    }

    if(sendfile(client_fd,file_fd,0,BUFF_SIZE)==-1) {
        perror("sendfile()");
        close(client_fd);
        close(server_fd);
        return 1;
    }

    close(client_fd);
    close(server_fd);

    return 0;
}
