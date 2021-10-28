/*
 * https://leetcode.com/problems/add-two-numbers/
 *
 * 2. Add Two Numbers
 *
 * You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.
 *
 * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 *
 *  
 *
 *  Example 1:
 *
 *
 *  Input: l1 = [2,4,3], l2 = [5,6,4]
 *  Output: [7,0,8]
 *  Explanation: 342 + 465 = 807.
 *  Example 2:
 *
 *  Input: l1 = [0], l2 = [0]
 *  Output: [0]
 *  Example 3:
 *
 *  Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
 *  Output: [8,9,9,9,0,0,0,1]
 *   
 *
 *   Constraints:
 *
 *   The number of nodes in each linked list is in the range [1, 100].
 *   0 <= Node.val <= 9
 *   It is guaranteed that the list represents a number that does not have leading zeros
 */

#include <stdio.h>
#include <stdlib.h> 

struct ListNode 
{
	int val;
	struct ListNode *next;
};

		
int InsertDigit(struct ListNode **end, int digit)
{
	struct ListNode *temp = (struct ListNode *) malloc (sizeof (struct ListNode));

	if (temp == NULL)
	{
		return 0;
	}

	temp->val = digit;
	temp->next = NULL;

	/* insert to the list */
	if (*end == NULL) 
	{
		*end = temp;
	}
	else
	{
		(*end)->next = temp;
		(*end) = (*end)->next;	
	}

	return 1;
}

void FreeNumber (struct ListNode **l)
{
	struct ListNode *temp_node = NULL, *temp_node2 = NULL;

	if (l == NULL)
		return ;

	temp_node = *l;
	while (temp_node)
	{
		temp_node2 = temp_node;
		temp_node = temp_node->next;
		free(temp_node2);
	}
	*l = NULL;	
}

struct ListNode* CreateNumber (int Number)
{
	int digit;
	struct ListNode *l = NULL, *end = NULL, *temp;

	while (Number)
	{
		digit = Number % 10;
		Number /= 10;

		if (!InsertDigit(&end, digit))
		{
			FreeNumber(&l);
			return NULL;
		}

		/* preserve the head */
		if (l == NULL)
			l = end;
	}
	return l;	
}


int GetNumber (struct ListNode *l)
{
	struct ListNode *temp_node = NULL;
	int num = 0;
	int digit = 1;

	for (temp_node = l; temp_node; temp_node = temp_node->next)
	{
		num += temp_node->val * digit;
		digit *= 10;
	}

	return num;
}

struct ListNode* addTwoNumbers (struct ListNode *l1, struct ListNode *l2)
{
	int carry;
	int sum;
	struct ListNode *l3 = NULL, *end = NULL, *temp = NULL;

	carry = 0;
	while (l1 || l2)
	{
		sum = carry;

		if (l1) {
			sum += l1->val;
			l1 = l1->next;
		}

		if (l2) {
			sum += l2->val;
			l2 = l2->next;
		}

		carry = sum / 10;
		sum %= 10;

		if (!InsertDigit(&end, sum))
		{
			FreeNumber(&l3);
			return NULL;
		}

		if (l3 == NULL)
			l3 = end;
	}

	if (carry)
	{
		/* insert carry */
		if (!InsertDigit(&end, carry))
		{
			FreeNumber(&l3);
			return NULL;
		}
	}

	return l3;
}

int main()
{
	struct ListNode *l1 = CreateNumber(342), *l2 = CreateNumber(465);
	struct ListNode *l3 = addTwoNumbers (l1, l2);

	printf ("\r %d + %d = %d \r\n", 
					GetNumber (l1), GetNumber (l2), GetNumber (l3));

	FreeNumber (&l1);
	FreeNumber (&l2);
	FreeNumber (&l3);

	return 0;
}

