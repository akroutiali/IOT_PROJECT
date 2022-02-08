#include "filechangehandler.h"
#include <sys/socket.h>
#include <sys/un.h>

#define EM_SUCCESS 1
#define EM_ERROR 0
#define sock_client "/tmp/sock_programB"

const char*nFile;
const char*oFile;
struct sockaddr_un cl;
int sock_fd=-1;


int  monitorInit(const char*newFile,const char* oldFile,int fd_server)
{
    if(newFile==NULL || oldFile==NULL)
    {
        printf("Error null pointer ");
        return EM_ERROR;
    }
   else if(!strcmp(newFile,"") ||!strcmp(oldFile,"") )
   {
       printf("Error:filename is empty  \n");
       return EM_ERROR;
   }
   nFile=newFile;
   oFile=oldFile;
   cl.sun_family = AF_UNIX;
   strcpy(cl.sun_path, sock_client);
   sock_fd=fd_server;
   return EM_SUCCESS;
}

void extractData(char*Line,char*data)
{
    char*p=Line; 
    if((p=strchr(Line,'=')))
    {
       size_t len = strlen (++p);
       snprintf (data,len,"%s", p);
    }
}

void monitorChangedElement()
{
    FILE*nFp=NULL,*oFp=NULL;
    char nLine[50];
    char oLine[50];
    char ssid[20];
    char oldNsr[20];
    char newNsr[20];
    char oldChannel[20];
    char newChannel[20];
    char out[100];
    int isfound=0;
    nFp=fopen(nFile,"r");
    while(fgets(nLine,sizeof(nLine),nFp))
    {
        isfound=0;
        oFp=fopen(oFile,"r");
        while(fgets(oLine,sizeof(oLine),oFp))
        {
            if(!strcmp(nLine,oLine))
            {
                extractData(nLine,ssid);
                isfound=1;
                for(int i=0;i<2;i++)
                {
                    fgets(nLine,sizeof(nLine),nFp);
                    fgets(oLine,sizeof(oLine),oFp);
                    if(strcmp(nLine,oLine) && (i==0))
                    {
                        extractData(nLine,newNsr);
                        extractData(oLine,oldNsr);
                        sprintf(out,"%s's SNR has changed from %s to %s",ssid,oldNsr,newNsr);
                        if (sendto(sock_fd, out, sizeof(out), 0, (struct sockaddr *)&cl,sizeof(struct sockaddr_un)) < 0)
                        {
                            printf("failed to send datagram message\n");
                        }
                    }
                    else if(strcmp(nLine,oLine) && (i==1))
                    {
                        extractData(nLine,newChannel);
                        extractData(oLine,oldChannel);
                        sprintf(out,"%s's channel has changed from %s to %s",ssid,oldChannel,newChannel);
                        if (sendto(sock_fd, out, sizeof(out), 0, (struct sockaddr *)&cl,sizeof(struct sockaddr_un)) < 0)
                        {
                            printf("failed to send datagram message\n");
                        }
                    }
                }
                break;
            }
        }
        if(!isfound)
        {
            //if ssid is not found in the old file pass to next ssid 
            for(int i=0;i<2;i++)
            {
               fgets(nLine,sizeof(nLine),nFp);
            }
        }
    }
    fclose(nFp);
    fclose(oFp);
}

void monitorAddedElement()
{
    FILE*nFp=NULL,*oFp=NULL;
    char nLine[50];
    char oLine[50];
    char ssid[20];
    char snr[20];
    char channel [20];
    char out [200];
    int isfound=0;
    nFp=fopen(nFile,"r");
    while(fgets(nLine,sizeof(nLine),nFp))
    {
        isfound=0;
        oFp=fopen(oFile,"r");
        while(fgets(oLine,sizeof(oLine),oFp))
        {
            if(!strcmp(nLine,oLine))
            {
                isfound=1;
                break;
            }
        }
        if(!isfound)
        {
            extractData(nLine,ssid);
            fgets(nLine,sizeof(nLine),nFp);
            extractData(nLine,snr);
            fgets(nLine,sizeof(nLine),nFp);
            extractData(nLine,channel);
            sprintf(out,"%s is added to the list with SNR %s and channel %s",ssid,snr,channel);
            if (sendto(sock_fd, out, sizeof(out), 0, (struct sockaddr *)&cl,sizeof(struct sockaddr_un)) < 0)
            {
                printf("failed to send datagram message\n");
            }
        }
        else
        {
            // element is found pass to next
            for(int i=0;i<2;i++)
            {
                fgets(nLine,sizeof(nLine),nFp);
            }
        }
    }
    fclose(nFp);
    fclose(oFp);
}

void monitorDeletedElement()
{
    FILE*oFp=NULL,*nFp=NULL;
    char nLine[50];
    char oLine[50];
    char ssid[20];
    char out[100];
    int isfound=0;
    oFp=fopen(oFile,"r");
    while(fgets(oLine,sizeof(nLine),oFp))
    {
        isfound=0;
        nFp=fopen(nFile,"r");
        while(fgets(nLine,sizeof(nLine),nFp))
        {
            if(!strcmp(nLine,oLine))
            {
                isfound=1;
                break;
            }
        }
        if(!isfound)
        {
            extractData(oLine,ssid);
            sprintf(out,"%s is removed from the list ",ssid);
            if (sendto(sock_fd, out, sizeof(out), 0, (struct sockaddr *)&cl,sizeof(struct sockaddr_un)) < 0)
            {
                printf("failed to send datagram message\n");
            }
        }
            //if ssid is not found in the new file  pass to next ssid 
        for(int i=0;i<2;i++)
        {
            fgets(oLine,sizeof(oLine),oFp);
        }
    }
    fclose(nFp);
    fclose(oFp);
}
