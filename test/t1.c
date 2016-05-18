#include <sys/unistd.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <math.h>

int print_f(double x){
	int i,j;
	i=(int)x;
	j=(int)((x-i)*10000);
	printf("%d.%d",i,j);
}

int main(void){

	double x;
	x=fabs(-1.32432);
	print_f(x);
	printf("\n");
	print_f(fabs(-2.0));
	printf("\n");
	print_f(fabs(-1.2));
	printf("\n");
	print_f(fabs(-0.0));
	printf("\n");
	print_f(fabs(1.0));
	printf("\n");
	print_f(sin(30.0/180.0*M_PI));
	printf("\n");
	print_f(cos(60.0/180.0*M_PI));
	printf("\n");
	print_f(tan(45.0/180.0*M_PI));
	printf("\n");
	print_f(tan(60.0/180.0*M_PI));
	printf("\n");
	print_f(sqrt(2));
	printf("\n");
	print_f(sqrt(3));
	printf("\n");
	print_f(sqrt(4));
	printf("\nfloor_test:\n");
	print_f(floor(4.34));
	printf("\nhreer");
	print_f(floor(5.6));
	printf("\nher");
	printf("\nceil_test:\n");
	print_f(ceil(4.34));
	printf("\nhreer");
	print_f(ceil(5.6));
	printf("\nher");
}
