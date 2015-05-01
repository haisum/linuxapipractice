#include <mysocket.h>

int main(int argvc, char * argv[]){

	int sfd, cfd;
	struct sockaddr_un addr;
	ssize_t num_read;
	char buf[BUFSIZE];
	
	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sfd == -1){
		printError("Error occured in creating socket.\n");
	}

	memset(&addr, 0, sizeof(struct sockaddr_un) - 1);
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCKPATH, sizeof(addr.sun_path) - 1);

	if(connect(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1){
		printError("Error occured  in connecting.\n");
	}

	while((num_read = read(STDIN_FILENO, buf, BUFSIZE)) > 0){
		if(write(sfd, buf, num_read) != num_read){
			printError("Error in writing.\n");	
		}
	}

	printSuccess("Suck sex");

	return 0;
}