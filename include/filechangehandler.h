#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* monitorInit
* @param newFile [IN] : name of the new file
* @param newFile [IN] : name of the old file
* @param fd_server [IN] : socket file descriptor
* @return EM_SUCCESS in case of file name are   valid , EM_ERROR in case of filename are invalid
* @par This function initialise the lib  filechangehandlet
*/
int  monitorInit(const char*newFile,const char* oldFile,int fd_server);

/* monitorChangedElement
* @return void
* @par This function manage the modification of the changed  element and send the modified content to the program B using AF_UNIX socket 
*/
void monitorChangedElement();

/* monitorDeletedElement
* @return void
* @par This function monitor the deleted element and send the result to  the program B using AF_UNIX socket
*/
void monitorDeletedElement();

/* monitorAddedElement
* @return void
* @par This function monitor  the added element and send the result to program B using AF_UNIX socket 
*/
void monitorAddedElement();


