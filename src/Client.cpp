// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <cstdio>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

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

#define PORT 8080

void error(const char *msg)
{
    perror(msg);
    exit(1);
}
  
int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    
    struct TypeToSend buffer;
    memset(&buffer, 0, sizeof(buffer));
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        error("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    int size = 1;
    
    while(true) {
    
        buffer.buf[0] = 100;
        buffer.buf[1] = -55;
        buffer.buf[2] = 1;
        buffer.buf[3] = 198;
        
        
        send(sock, &size, sizeof(int), 0); 
        
        send(sock , &buffer , sizeof(buffer), 0);
           
        
        size++;
        sleep(1);
    }

    return 0;
}
