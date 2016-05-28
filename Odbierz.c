#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>



struct wiadomosc
{
	long int typ;
	char wyraz[BUFSIZ];
};

int main()
{
	struct tm * info;
	time_t now;
	time(&now);
	info=localtime(&now);
	printf("Dzisiaj jest dzien tygodnia: ");	

	if(info->tm_wday == 0) printf ("niedziela\n");
	if(info->tm_wday == 1) printf ("poniedzialek\n");
	if(info->tm_wday == 2) printf ("wtorek\n");
	if(info->tm_wday == 3) printf ("sroda\n");
	if(info->tm_wday == 4) printf ("czwartek\n");
	if(info->tm_wday == 5) printf ("piatek\n");
	if(info->tm_wday == 6) printf ("sobota\n");

	int msgid;
	struct wiadomosc tekst;
	long int odbierz=0;

	if(info->tm_wday == 5 || info->tm_wday == 6 || info->tm_wday == 0)
	{
		printf("Jest weekend, wiec odbieram z kolejki!\n");

		msgid= msgget((key_t)1234,0666 | IPC_CREAT);

		if(msgid == -1)
		{
			printf("BLAD!\n");
			exit(EXIT_FAILURE);
		}

		if(msgrcv(msgid,(void*)&tekst,BUFSIZ,odbierz,IPC_NOWAIT) == -1)
		{
			printf("Brak komunikatu do odebrania!\n");
			exit(EXIT_FAILURE);
		}

		printf("Napisales: %s",tekst.wyraz);

		if((tekst.wyraz[0] >= 65 && tekst.wyraz[0] <= 90) || (tekst.wyraz[0] >= 97 && tekst.wyraz[0] <= 122))
		{
			printf("Wyraz uznany za poprawny (zaczyna sie od litery), przesylam do aspella!\n"); fflush(stdout);
			execl("./aspell.sh","aspell.sh",tekst.wyraz,(char*)NULL);
		}
		
		else
		{		
			printf("Wyraz nie jest poprawny, nie zaczyna sie od litery\n");
		}
	}

	else
	{
		printf("Aby odbierac z kolejki poczekaj do piatku!\n");
	}
}
