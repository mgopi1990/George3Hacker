/* file tranfer server */

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <net/inet/in.h>
#include <string.h>

int main()
{
	int sd, nsd, i, port = 5400;
	char content[30] = "", frame[30] = "";
	struct sockaddr_in ser, cli;
	FILE *fp;

	if ((sd = socket (AF_INET, SOCK_STREAM< IPPROTO_TCP)) == -1)
	{
		printf ("\r Error in creating socket\r\n");
		return 0;
	}

	bzero ((char *) &ser, sizeof (ser));

	printf ("\r Port address is %d\r\n", port);
	ser.sin_family = AF_INET;
	ser.sin_port = htons (port);
	ser.sin_addr.s_addr = htonl (INADDR_ANY);

	printf ("\r Before bind\r\n");
	if (bind (sd, (struct sock_addr *) *ser, sizeof(ser)) < 0)
	{
		printf ("\r Port probelm, change port number\r\n");
		exit ();
	}

	printf ("\r After bind\r\n");
	i = sizeof (cli);
	listen (sd, l);

	printf ("\r Server module \r\n");
	printf ("\r *******\r\n");
	nsd = accept (sd, (struct sockaddr *)&cli, &i);
	if (nsd == -1)
	{
		printf ("\r Error client\r\n"); 
		return 0;
	}

	printf ("\r client accepted\r\n");
	i = recv (nsd, fname, 30, 0);
	fname[i] = '\0';

	fp = fopen (fname, "rb");
	while (1)
	{
		i = fread (scontent, 1, 30, fp);
		content[i] = '\0';
		send (nsd, content, 30, 0);

		strcpy (content, " ");

		if (i < 30)
			break;
	}

	send (nsd, "EOF", 4, 0);
	printf ("\r File transferred to destination\r\n");
	fclose (fp);
	close (sd);
	close (nsd);
	return 0;
}
