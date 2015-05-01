#include <mysocket.h>

void printError(char *message){
	printf("Error occured: %s\n", message);
	exit(EXIT_FAILURE);
}

void printSuccess(char *message){
	printf("Success: %s\n", message);
	exit(EXIT_SUCCESS);
}