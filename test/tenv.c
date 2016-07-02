#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
	char **p=envp;

	while(*p){
		printf("%s\n",*p);
		p++;
	}


}
