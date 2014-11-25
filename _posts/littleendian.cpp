#include <stdio.h>
int main(int argc, char const *argv[])
{
	int v = -12345;
	unsigned int uv = (unsigned int) v;
	printf("v= %X, uv= %X \n", v,uv);
	printf("v= %d, uv= %u \n", v,uv);
	return 0;
}