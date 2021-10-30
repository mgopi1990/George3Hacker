/*
 * 44. Wildcard Matching
 * 
 * Given an input string (s) and a pattern (p), implement wildcard pattern
 * matching with support for '?' and '*' where:
 * 
 * '?' Matches any single character.
 * '*' Matches any sequence of characters (including the empty sequence).
 * The matching should cover the entire input string (not partial).
 * 
 * 
 * Example 1:
 * 
 *  Input: s = "aa", p = "a"
 *  Output: false
 *  Explanation: "a" does not match the entire string "aa".
 *
 * Example 2:
 * 
 *  Input: s = "aa", p = "*"
 *  Output: true
 *  Explanation: '*' matches any sequence.
 * 
 * Example 3:
 * 
 *  Input: s = "cb", p = "?a"
 *  Output: false
 *  Explanation: '?' matches 'c', but the second letter is 'a', 
 *  which does not match 'b'.
 * 
 * Example 4:
 * 
 *  Input: s = "adceb", p = "*a*b"
 *  Output: true
 *  Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
 * 
 * Example 5:
 * 
 *  Input: s = "acdcb", p = "a*c?b"
 *  Output: false
 *  
 * Constraints:
 * 
 *  0 <= s.length, p.length <= 2000
 *  s contains only lowercase English letters.
 *  p contains only lowercase English letters, '?' or '*'.
 * 
 */

#include <stdio.h>

#define bool 	char
#define true 	1
#define false 	0

#define MAX_STRLEN 2000

typedef struct {
 int sno;
 char s[MAX_STRLEN], p[MAX_STRLEN];
 bool expected_result;
}testcase;

testcase tc[] = {
 {1, "aa", "a", false},
 {2, "aa", "*", true},
 {3, "cb", "?a", false},
 {4, "adceb", "*a*b", true},
 {5, "acdcb", "a*c?b", false}, 
 {6, "acdcb", "*?cb*", true},
 {7, "acdcb", "*?cb*", true},
 {8, "acdcb", "**", true},
 {9, "abcde", "abcde", true},
 {10, "abcde", "abcd", false},
 {11, "abcde", "", false},
 {12, "", "*", true},
 {13, "", "?", false},
 {14, "", "", true},
 {15, "a", "*", true},
 {16, "a", "*?", true},
 {17, "a", "*?*", true},
 {18, "a", "?", true},
 {19, "abcde", "*a*b*c*d*e*", true},
 {20, "abcdeca", "a*c?", true},
 {21, "bbbbbbbabbaabbabbbbaaabbabbabaaabbababbbabbbabaaabaab", 
 		"b*b*ab**ba*b**b***bba", false},
 {22, "mississippi", "m??*ss*?i*pi", false},
 {23, "abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb",
	  "**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb", false},
};

bool isMatch(char *s, char *p);

int main()
{
	int n = sizeof (tc)/sizeof(tc[0]);
    int i;
	bool result;

	for (i = 0; i < n; i++)
	{
		result = isMatch(tc[i].s, tc[i].p);
		printf ("\r TC [%d] result:%s\r\n", tc[i].sno,
					(result == tc[i].expected_result)?"PASS": "FAIL");
	}

	return 0;
}

bool isMatch(char *s, char *p)
{
	int i = 0, j = 0, l, match;

	while(s[i] != '\0')
	{
		if (p[j] == '*')
		{
			/* burn any stray * */
			while(p[j+1] == '*')
			{
				j++;
			}

			do 
			{
				match = 0;
				for (l = 0; ((p[j+l+1] != '\0') && (p[j+l+1] != '*') 
										&& (s[i+l] != '\0')); l++)
				{
					if ((s[i+l] != p[j+l+1]) && (p[j+l+1] != '?'))
					{
						match = 0;
						break;
					}

					/* atleast one char matched */
					match = 1;
				}

				if (match && isMatch (&s[i+l], &p[j+l+1]))
				{
					return true;
				}

			/* exit check to allow processing '\0' as well */ 
			}while (s[i++] != '\0');
			/* do not cross beyond */
			i--;

			/* consume the * */
			j++;
		}
		else if ((s[i] == p[j]) || (p[j] == '?'))
		{
			i++;
			j++;
			continue;
		}
		else 
		{
			/* pattern didnt match */
			return false;
		}
	}

	/* burn any stray * */
	while(p[j] == '*')
	{
		j++;
	}

	if ((s[i] == '\0') && (p[j] == '\0')) 
	{
		/* both the string and pattern are exhausted */
		return true;
	}

	/* pattern didnt match */
	return false;
}
