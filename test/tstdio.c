#include <stdio.h>

extern void dump_iotab(void);

void pause(void)
{
	char c;
	read(0,&c,1);
}

int main(void)
{
	FILE *f1,*f2,*f3,*f4,*f5;

//	dump_iotab();
//	f1=fopen("/bin/ls", " ");
//	dump_iotab();
//	pause();
//	f2=fopen("/bin/sh", " ");
//	dump_iotab();
//	pause();
//	f3=fopen("/bin/cat"," ");
//	dump_iotab();
//	pause();
//	fclose(f1);
//	dump_iotab();
//	pause();
//	fclose(f2);
//	dump_iotab();
//	pause();
//	f2=fopen("/bin/init"," ");
//	dump_iotab();
//	pause();

//	f4=fopen("/home/test1.txt", " ");
////	dump_iotab();
////	printf("come here");
//	int c;
//	while ((c=fgetc(f4))!=EOF){
//		printf("%c",c);
//	}

	char *s1="this is a test\n line 2";
	f5=fopen("/home/test", " ");

	fputs(s1,f5);
	fclose(f5);

}
