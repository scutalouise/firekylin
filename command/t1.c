#include <sys/unistd.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <math.h>

int print_f(double x)
{
	int i, j;
	if(x<0){
		printf("-");
		x=-x;
	}
	i = (int) x;
	j = (int) ((x - i) * 10000);
	printf("%d.%d", i, j);
}

int main(void)
{
	printf("\n");
	print_f(ldexp(4.5,2.1));
	printf("\n");
	print_f(ldexp(4.5,3.2));
	printf("\n");
	print_f(ldexp(4.5,4.3));
	printf("\n");
}
