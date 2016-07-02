#include <setjmp.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
	jmp_buf buf;

	int i;

	switch(setjmp(buf)){
	case 0:
		printf("setjmp 0\n");
		longjmp(buf,1);
		break ;
	case 1:
		printf("setjmp 1\n");
		longjmp(buf,2);
		break ;
	case 2:
		printf("setjmp 2\n");
		break;
	}

	return 0;
}
