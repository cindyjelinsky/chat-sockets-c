#include "util.h"
#include<stdbool.h>

int main(){

    
    int socketFD = createIPv4Socket();
    struct sockaddr_in *address = createIPv4Address("127.0.0.1",5000);
    

    int result = connect(socketFD,(struct sockaddr*)address,sizeof (*address));

    if(result == 0){
        printf("Connection was successful\n");
    }else{
        ("error connecting",-1);
    }


   char *line = NULL;
    size_t lineSize = 0;
    printf("Type and send (type exit)...\n");

    while (1) {
        ssize_t charCount = getline(&line, &lineSize, stdin);
        
        if (charCount > 0) {
            
            line[charCount - 1] = '\0';

            if (strcmp(line, "exit") == 0) {
                break;
            }

            ssize_t amountSent = send(socketFD, line, strlen(line), 0);
            if (amountSent < 0) {
                perror("Error sending message");
            } else {
                printf("Sent %zd bytes: %s\n", amountSent, line);
            }
        }
    }


   // char* message;
   // message = "What´s going on?";
    //send(socketFD,message,strlen(message),0);

   // char buffer[1024];
    //recv(socketFD,buffer,1024,0);

   // printf("Response was:\n %s\n",buffer);
    

    return 0;

}