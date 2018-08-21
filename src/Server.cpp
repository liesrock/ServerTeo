
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <arpa/inet.h>

#include <BufType.h>

using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd = -1;
    int newsockfd = -1;
    int portno;
    int n;
    socklen_t clilen;
    
    struct TypeToSend buffer;
    int num_to_recv = 0;
    string argvPassed;
    struct sockaddr_in serv_addr, cli_addr;

    memset(&buffer, 0, sizeof(buffer));

    for (int i = 0; i < argc; i++) {
        argvPassed += argv[i];
    }
    if (argvPassed.find("tcp") != string::npos) {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
    }

    // [ON] check it
    else if (argvPassed.find("udp") != string::npos) {
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    }

    if (sockfd < 0) {
        error("ERROR opening socket");
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[3]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }
    
    listen(sockfd, 5);
    
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,
                       (struct sockaddr *) &cli_addr,
                       &clilen);
    
    if (newsockfd < 0) {
        error("ERROR on accept");
    }
    
    while (true) {
    
        bzero(&buffer, sizeof(TypeToSend));
        num_to_recv = 0;
        
        n = read(newsockfd, &num_to_recv, sizeof(int));

        if (n < 0) { 
            error("ERROR reading from socket");
        }
        
        n = read(newsockfd, &buffer, sizeof(buffer));

        if (n < 0) { 
            error("ERROR writing to socket");
        }

        for (int i = 0; i < num_to_recv; i++) {
            cout << buffer.buf[i] << endl;
        }

        
    }
    
    close(newsockfd);
    close(sockfd);
    return 0;
}
