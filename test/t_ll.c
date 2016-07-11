#include <stdio.h>

int main(void)
{
	long long a=-123456565765LL;
	long long b=5657065LL;
	
	unsigned long long ua=123456565765LL;
	unsigned long long ub=5065765LL;
	
	printf("%ld %ld %ld %ld ", a/b, a%b, ua/ub, ua%ub);
	
}