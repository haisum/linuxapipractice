#include <mysocket.h>

int main(int argvc, char * argv[]){

	int sfd, cfd;
	struct sockaddr_un addr;
	ssize_t num_read;
	char buf[BUFSIZE];
	
	if(remove(SOCKPATH) == -1 && errno != ENOENT){
		printf("Error in removing socket file %s.\n", SOCKPATH);
		return -1;
	}

	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sfd == -1){
		printf("Error occured in creating socket.\n");
		return 1;
	}

	memset(&addr, 0, sizeof(struct sockaddr_un) - 1);
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCKPATH, sizeof(addr.sun_path) - 1);

	if(bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1){
		printf("Error occured  in binding.\n");
		return 1;
	}

	if(listen(sfd, BACKLOG) == -1){
		printf("Listen error.\n");
		return 1;
	}

	for(;;){
		printf("Accepting\n");
		cfd = accept(sfd, NULL, NULL);
		printf("Got Packet\n");
		if(cfd == -1){
			printf("Error in accepting.\n");
			return 1;
		}
		while((num_read = read(cfd, buf, BUFSIZE)) > 0){
			if(write(STDOUT_FILENO, buf, num_read) != num_read){
				printf("Error in writing.\n");
				return 1;		
			}
		}

	}

	return 0;
}