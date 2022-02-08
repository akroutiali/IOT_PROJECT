*************Solution Design ******************

1-Develop  shared library "libparser.so" to parse json file and save the content  in text file .

2-Develop shared library "libhandler.so" to monitor  json file modification and send the modification to programB. 

3-Develop applicationA :link to the two shared library to manage jsonfile modification and inform programB

4-Develop applicationB :listen to the message sent from applicationA and print them .

5-prepare the Makefile the manage the compilation phase.

-IPC :the IPC used is socket since those two application will run on the same Device the efficient methode is to use AF_UNIX socket .


-the project directory is as follows : 

applicationA :the applicatonA directory contains the code of the applicationA

applicationB :the applicatonB directory contains the code of the applicationB

lib :the lib directory contains the code of the libparser and libhandler

include :the include directory contains the header file .

bin :the bin directory contains the applicationA and applicationB binary and shared library 

obj :the obj directory contains the obj file 


*NOTE :applicationA will check file change evry 30 s .this parameter is treated in the callback function"void threadFunc()" of the thread applicationA in file programA.c we can modify as we want depends to the requirement 