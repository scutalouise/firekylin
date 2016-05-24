#include <stdio.h>
#include <sys/unistd.h>
#include <sys/fcntl.h>

int main(void)
{
	char buf[100];
	char *argv[7]={
		"/dev/tty1",
		"/dev/tty2",
		"/dev/tty3",
		"/dev/tty4",
		"/dev/tty5",
		"/dev/tty6",
		"/dev/tty7",
	};
	printf("vegin");
	int fd,size;
	for(int i=0;i<7;i++){
		printf("%s\n",argv[i]);
		fd=open(argv[i],O_RDWR,0);
		size=sprintf(buf,"This is %s",argv[i]);
		write(fd,buf,size);
	}
}
