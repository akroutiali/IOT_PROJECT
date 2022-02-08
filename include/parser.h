#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>
#include <string.h>

/* parserInit
* @param filename [IN] : jsonfilename to parse
* @return EM_SUCCESS in case of file name is not empty, EM_ERROR in case of empty file name
* @par This function set the value of the parameter fileName
*/
int parserInit(char* inputfile ,char*outputfile);

/* parserGetContent
* @return void 
* @par This function parse the content of json file
*/
void parserGetContent();