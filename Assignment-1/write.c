#include<unistd.h>
#include<stdio.h>
#include<string.h>
int main()
{
	//fd=0 ->standard input device: keyboard
	//fd=1 ->standard output device: display
	//fd=2 ->standard error device
	//system call on failure returns -1
	char str[]="This is our first lab assignment\n";
	int length=strlen(str);
	int count=write(1,str,length); 
	printf("Total bytes written: %d\n",count);
}
