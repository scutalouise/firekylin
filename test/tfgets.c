#include <stdio.h>
#include <string.h>

int main()
{
	char buf[1024];

	int i=5;
	int len;
	printf("tfgets start \n");
	while(i--){
		fgets(buf,1024,stdin);
		len=strnlen(buf,1024);
		write(0,buf,len);
	}


}
