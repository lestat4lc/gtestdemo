#include "func.h"

int func(int n)
{
	if(n<0)
	{
		//throw "n<0";
	  return -1;
	}

	int nRev = 1;
	for(int i=1;i<=n;++i)
	  nRev*=i;

	return nRev;
}


bool IsPrime(int n)
{
	if (n<=1) return false;
	if (n%2 == 0) return n==2;

	for(int i=3;;i+=2)
	{
		if(i>n/i) break;
		if(n%i == 0) return false;
	}

	return true;
}
