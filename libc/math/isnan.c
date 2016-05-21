/*
 *  port form minix
 *  don't understand
 */

int isnan(double d)
{
	float f = d;

	if ((*((long *) &f) & 0x7f800000) == 0x7f800000
			&& (*((long *) &f) & 0x007fffff) != 0)
		return 1;

	return 0;
}
