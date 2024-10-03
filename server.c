#include "util.h"
#include<stdbool.h>
#include <unistd.h>
#include <pthread.h>

int main(){

    int serversocketFD = createIPv4Socket();
    struct sockaddr_in *serveraddress = createIPv4Address("127.0.0.1",5000);

    
   

    int result = bind(serversocketFD,(struct sockaddr*)serveraddress, sizeof(*serveraddress));
    if(result == 0){
        printf("Socket was bound successfully\n");
    }
    
    int listeresult = listen(serversocketFD,10);

    //struct of client address FD
    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(clientAddress);
    //accept() will return the file descriptor from client
    int clientSocketFD = accept(serversocketFD,(struct sockaddr*)&clientAddress,&clientAddressSize);

    char buffer[1024];
    while(true){
      ssize_t bRecieved = recv(clientSocketFD,buffer,1024,0);

      if(bRecieved>0){
        //buffer[bRecieved] = 0;
        printf("Response was:\n %s\n",buffer);
      } 
      if(bRecieved==0){
        break;
      }      
    }

    close(clientSocketFD);
    shutdown(serversocketFD,SHUT_RDWR);
      
     return 0;
}

