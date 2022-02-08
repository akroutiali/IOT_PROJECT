#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/un.h>

/* createSocket
* @return EM_SUCCESS in case success, EM_ERROR in case error
* @par This funnction will create AF_UNIX socket to send the modification to application B 
*/
int  createSocket();

/* threadFunc
* @return void 
* @par This funnction will parse the json and monitor file change
*/
void threadFunc();