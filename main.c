#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

static void sighandler(int signo){
	if (signo == SIGINT){
		int fd = open("signal.txt", O_WRONLY| O_CREAT, 0666);
		
		if (fd == -1){
			printf("Error: %s\n", strerror(errno));
			exit(0);
		}
		
		write(fd, "program exited due to SIGINT\n", 32);
		close(fd);
		exit(0);
	}
	
	if (signo == SIGUSR1){
		printf("PID of parent process: %d\n", getppid());
	}
}


int main(){
	signal(SIGINT, sighandler);
	
	int i = 1;
	while(i){
		printf("PID: %d\n", getpid());
		sleep(1);
	}
	
}

