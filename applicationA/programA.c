#include "parser.h"
#include  "filechangehandler.h"
#include "programA.h"

#define EM_SUCCESS 1
#define EM_ERROR 0

//json file location 
#define JSON_FILE "/tmp/access_points"
//current parsed file location 
#define CURRENT_PARSED_FILE "/tmp/current_parsed_file"
//old parsed file location 
#define OLD_PARSED_FILE "/tmp/old_parsed_file"

#define sock_server "/tmp/sock_programA"
#define sock_client "/tmp/sock_programB"

int fd_server=-1;
struct sockaddr_un serv;
struct sockaddr_un cl;

int  createSocket()
{
    unlink(sock_server);
    fd_server = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (fd_server < 0) 
    {
        printf("Error:: opening datagram socket failed \n");
        return EM_ERROR;
    }
    serv.sun_family = AF_UNIX;
    strcpy(serv.sun_path, sock_server);
    if (bind(fd_server, (struct sockaddr *) &serv, sizeof(struct sockaddr_un))<0)
    {
        printf("Error :bind failed\n");
    }
    return EM_SUCCESS;
}

void threadFunc()
{
    int isFirst=1;
    char buff[100];
    for(;;)
    {
        parserGetContent();
        if(isFirst)
        {
            sprintf(buff,"cp %s %s >/dev/null 2>&1",CURRENT_PARSED_FILE,OLD_PARSED_FILE);
            system(buff);
            isFirst=0;
        }
        //check json file modification and send the result to program B using socket 
        monitorChangedElement();
        monitorAddedElement();
        monitorDeletedElement();
        sleep(30);
        if(!isFirst)
        {
            sprintf(buff,"cp %s %s >/dev/null 2>&1",CURRENT_PARSED_FILE,OLD_PARSED_FILE);
            system(buff);
        }

    }

}

int main(void)
{
    pthread_t threadId;
    createSocket();
    if(!parserInit(JSON_FILE,CURRENT_PARSED_FILE))
       return 0;
    if(!monitorInit(CURRENT_PARSED_FILE,OLD_PARSED_FILE,fd_server))
       return 0;
    int err = pthread_create(&threadId, NULL, &threadFunc, NULL);
    pthread_join(threadId, NULL);
	
    return 0;
}
