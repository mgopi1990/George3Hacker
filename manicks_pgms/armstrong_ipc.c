/* 
 * Finds armstrong number on parent as well as child
 */

#include <stdio.h>
#include <math.h>

int main()
{
	void arm (int n);
	int m, forkid, n;

	printf ("\r Enter no:");
	scanf ("%d", &m);
	forid = fork();
	if (forkid)
	{
		printf ("\r From parent process: id:%d status:%d\r\n", getpid(), forkid);
		arm (m);
	}
	else 
	{
		printf ("\r From child process: id:%d parent:%d status:%d\r\n", 
						getpid(), getppid(), forkid);
		arm (m);
	}
}

void arm(int n)
{
	int s = 0, i, a, m, t;
	for (i = 1, i <= n; i++)
	{
		s = 0;
		m = i;
		t = i;
		while (t > 0)
		{
			a = t % 10;
			s += a * a * a;
			t = t / 10;
		}

		if (m == s)
			printf ("%d", m);
	}
}
		
