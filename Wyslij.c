#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define max 50

struct wiadomosc
{
	long int typ;
	char wyraz[max];
};

int main()
{
	struct wiadomosc tekst;
	int msgid;
	char bufor[BUFSIZ];

	msgid=msgget((key_t)1234,0666 | IPC_CREAT);

	if (msgid==-1) 
	{
		printf("BLAD!");
		exit(EXIT_FAILURE);
	}

	printf("Podaj wyraz: ");
	fgets(bufor, BUFSIZ, stdin);
	tekst.typ=1;
	strcpy(tekst.wyraz,bufor);

	if(msgsnd(msgid,(void*)&tekst,max,0==-1))
	{
		printf("BLAD!");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
