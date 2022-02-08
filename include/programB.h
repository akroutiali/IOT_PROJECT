#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/socket.h>


/* createSocket
* @return EM_SUCCESS in case success, EM_ERROR in case error
* @par This funnction will create AF_UNIX socket to listen the message sent from APPLICATION A 
*/
int  createSocket();

/* threadFunc
* @return void 
* @par This funnction will display the message recieved from application A
*/
void threadFunc();