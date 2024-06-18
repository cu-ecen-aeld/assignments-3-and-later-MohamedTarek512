#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <syslog.h>
#include <signal.h>
#include <fcntl.h>
#include <arpa/inet.h>

#define PORT "9000"
#define BACKLOG 10
#define FILE_PATH "/var/tmp/aesdsocketdata"
#define BUFFER_SIZE 1024

int server_socket, client_socket;
int running = 1;

void handle_signal(int signal) {
    syslog(LOG_INFO, "Caught signal, exiting");
    running = 0;
    close(server_socket);
    close(client_socket);
    remove(FILE_PATH);
    exit(0);
}

void setup_signal_handler() {
    struct sigaction sa;
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
}

int main(int argc, char *argv[]) {
       printf("Hello from main");
/*    openlog("aesdsocket", LOG_PID, LOG_USER);
 
    struct addrinfo hints, *res;
    struct sockaddr_storage client_addr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];
    char client_ip[INET_ADDRSTRLEN];
    int bytes_received, file_fd;

    setup_signal_handler();

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, PORT, &hints, &res);

    server_socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (server_socket == -1) {
        syslog(LOG_ERR, "Socket creation failed");
        exit(1);
    }

    if (bind(server_socket, res->ai_addr, res->ai_addrlen) == -1) {
        syslog(LOG_ERR, "Bind failed");
        close(server_socket);
        exit(1);
    }

    freeaddrinfo(res);

    if (listen(server_socket, BACKLOG) == -1) {
        syslog(LOG_ERR, "Listen failed");
        close(server_socket);
        exit(1);
    }

    while (running) {
        addr_size = sizeof client_addr;
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
        if (client_socket == -1) {
            if (!running) break;
            syslog(LOG_ERR, "Accept failed");
            continue;
        }

        inet_ntop(client_addr.ss_family, &((struct sockaddr_in *)&client_addr)->sin_addr, client_ip, sizeof client_ip);
        syslog(LOG_INFO, "Accepted connection from %s", client_ip);

        file_fd = open(FILE_PATH, O_CREAT | O_APPEND | O_RDWR, 0644);
        if (file_fd == -1) {
            syslog(LOG_ERR, "File open failed");
            close(client_socket);
            continue;
        }

        while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
            buffer[bytes_received] = '\0';
            write(file_fd, buffer, bytes_received);

            if (strchr(buffer, '\n') != NULL) {
                lseek(file_fd, 0, SEEK_SET);
                while ((bytes_received = read(file_fd, buffer, BUFFER_SIZE)) > 0) {
                    send(client_socket, buffer, bytes_received, 0);
                }
            }
        }

        close(file_fd);
        close(client_socket);
        syslog(LOG_INFO, "Closed connection from %s", client_ip);
    }

    closelog(); */
    return 0;
}

