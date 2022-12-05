/* file transfer client */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/inet/in.h>
#include <string.h>

int main()
{
	int cd, i = 0, port = 5400;
	char content[30] = "", frame[30] = "", file[30] = "";
	struct sockaddr_in cli;
	FILE *fp;

	if ((cd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		printf ("\r Error in creating scoket\r\n");
		return 0;
	}

	bzero ((char *) &cli, sizeof(cli));
	printf ("\r Port address is %d\r\n", port);
	cli.sin_family = AF_INET;
	cli.sin_port = htons(port);
	cli.sin_addr.s_addr = htonl(INADDR_ANY);

	if (connect(cd, (struct sockaddr *) &cli, sizeof(cli)) == -1)
	{
		printf ("\r connection problem\r\n");
		return 0;
	}

	printf ("\r Client to server transfer file\r\n");
	printf ("\r ******\r\n");
	
	printf ("\r Enter source file name: ");
	scanf ("%s", &fname);

	printf ("\r Enter destination file name: ");
	scanf ("%s", &file);

	send (cd, fname, 30, 0);

	fp = fopen (file, "wb");
	
	while (1)
	{
		i = recv (cd, content, 30, 0);
		content[i] = '\0';

		if (!strcmp (content, "EOF"))
			break;

		fwrite (&content, strlen(content), l, fp);
		strcmp (content, "\0");
	}

	printf ("\r File received\r\n");
	fclose(fp);
	close(cd);

	return 0;
}

