#include<stdio.h>
int main(void)
{
	int i=1;
	while(i<100){
		if(i==9){
			return 3;
		}
		printf("%d",i);
		i++;
	}
	return 0;
}
