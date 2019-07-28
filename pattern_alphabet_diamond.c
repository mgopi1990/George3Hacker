
/*

Does this awesome thing :-P 

-----------------------------o-----------------------------
---------------------------o-n-o---------------------------
-------------------------o-n-m-n-o-------------------------
-----------------------o-n-m-l-m-n-o-----------------------
---------------------o-n-m-l-k-l-m-n-o---------------------
-------------------o-n-m-l-k-j-k-l-m-n-o-------------------
-----------------o-n-m-l-k-j-i-j-k-l-m-n-o-----------------
---------------o-n-m-l-k-j-i-h-i-j-k-l-m-n-o---------------
-------------o-n-m-l-k-j-i-h-g-h-i-j-k-l-m-n-o-------------
-----------o-n-m-l-k-j-i-h-g-f-g-h-i-j-k-l-m-n-o-----------
---------o-n-m-l-k-j-i-h-g-f-e-f-g-h-i-j-k-l-m-n-o---------
-------o-n-m-l-k-j-i-h-g-f-e-d-e-f-g-h-i-j-k-l-m-n-o-------
-----o-n-m-l-k-j-i-h-g-f-e-d-c-d-e-f-g-h-i-j-k-l-m-n-o-----
---o-n-m-l-k-j-i-h-g-f-e-d-c-b-c-d-e-f-g-h-i-j-k-l-m-n-o---
-o-n-m-l-k-j-i-h-g-f-e-d-c-b-a-b-c-d-e-f-g-h-i-j-k-l-m-n-o-
---o-n-m-l-k-j-i-h-g-f-e-d-c-b-c-d-e-f-g-h-i-j-k-l-m-n-o---
-----o-n-m-l-k-j-i-h-g-f-e-d-c-d-e-f-g-h-i-j-k-l-m-n-o-----
-------o-n-m-l-k-j-i-h-g-f-e-d-e-f-g-h-i-j-k-l-m-n-o-------
---------o-n-m-l-k-j-i-h-g-f-e-f-g-h-i-j-k-l-m-n-o---------
-----------o-n-m-l-k-j-i-h-g-f-g-h-i-j-k-l-m-n-o-----------
-------------o-n-m-l-k-j-i-h-g-h-i-j-k-l-m-n-o-------------
---------------o-n-m-l-k-j-i-h-i-j-k-l-m-n-o---------------
-----------------o-n-m-l-k-j-i-j-k-l-m-n-o-----------------
-------------------o-n-m-l-k-j-k-l-m-n-o-------------------
---------------------o-n-m-l-k-l-m-n-o---------------------
-----------------------o-n-m-l-m-n-o-----------------------
-------------------------o-n-m-n-o-------------------------
---------------------------o-n-o---------------------------
-----------------------------o-----------------------------

*/

#include<stdio.h>

void main()
{
	int i,j,n,s,in,dn,ind,dnd;

	printf("enter the number: ");
	scanf("%d",&n);

	for(i=1;i<=n;i++)
	{
		printf("\n");
		
		for(s=i;s<=n*2-i;s++)
		{
			printf("-");
		}
		
		for(dn=n;dn>=n-i+1;dn--)
		{
			printf("%c-",'a'+dn-1);
		}

		
		for(in=n-i+2;in<=n;in++)
		{
			printf("%c-",'a'+ in-1);
		}
		
		for(s=i;s<n*2-i;s++)
		{
			printf("-");
		}
	}
	
	for(j=n;j>1;j--)
	{
		printf("\n");	
		for(s=j;s<=n*2-j+2;s++)
		{
			printf("-");
		}
		
		for(dnd=n;dnd>n-j+1;dnd--)
		{
			printf("%c-",'a'+ dnd-1);
		}   
		
		for(ind=n-j+3;ind<=n;ind++)
		{
			  printf("%c-",'a'+ ind-1);
		}
		
		for(s=j-1;s<=n*2-j;s++)
		{
			printf("-");
		}
	}
	printf("\n\n");
}
