
#include "parser.h"

#define EM_SUCCESS 1
#define EM_ERROR 0

static char* fileIn=NULL;
static char* fileOut=NULL;

int parserInit(char* inputFile ,char*outputFile)
{

   if(inputFile==NULL || outputFile==NULL)
   {
      printf("Error:filename is null  \n");
      return EM_ERROR;
   }
   else if(!strcmp(inputFile,"") ||!strcmp(outputFile,"") )
   {
       printf("Error:filename is empty  \n");
       return EM_ERROR;
   }
   fileIn=inputFile;
   fileOut=outputFile;

   return EM_SUCCESS;
}
void parserGetContent()
{
   struct json_object *accesspoints_obj, *accesspoints_array, *accesspoints_array_obj, *accesspoints_array_obj_ssid,*accesspoints_array_obj_snr,*accesspoints_array_obj_channel;
   int arraylen=0, i=0;
   FILE*fp;
   fp=fopen(fileOut,"w");
   accesspoints_obj = json_object_from_file(fileIn);
   accesspoints_array = json_object_object_get(accesspoints_obj, "access_points");

   // accesspoints_array is an array of objects
   arraylen = json_object_array_length(accesspoints_array);

   for (i = 0; i < arraylen; i++) {
   // get the i-th object in accesspoints_array
   accesspoints_array_obj = json_object_array_get_idx(accesspoints_array, i);
   accesspoints_array_obj_ssid = json_object_object_get(accesspoints_array_obj, "ssid");
   accesspoints_array_obj_snr = json_object_object_get(accesspoints_array_obj, "snr");
   accesspoints_array_obj_channel = json_object_object_get(accesspoints_array_obj, "channel");
   fprintf(fp,"ssid=%s\n", json_object_get_string(accesspoints_array_obj_ssid));
   fprintf(fp,"snr=%s\n", json_object_get_string(accesspoints_array_obj_snr));
   fprintf(fp,"channel=%s\n", json_object_get_string(accesspoints_array_obj_channel));

   }
   fclose(fp);
}
