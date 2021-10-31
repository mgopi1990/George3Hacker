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
int MatchWildStr (char *s, char *p);

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

/* returns -1 if not matching 
 * returns number of matching char if match is found */
int MatchWildStr (char *s, char *p)
{
	int i;

	for (i = 0; (p[i] != '\0') && (p[i] != '*'); i++)
	{
		if ((s[i] != p[i]) && (p[i] != '?' || s[i] == '\0'))
		{
			/* string didnt match */
			return -1;
		}
	}

	if (p[i] == '\0' && s[i] != '\0')
		return -1;

	/* returns number of matching chars */
	return i;
}

bool isMatch(char *s, char *p)
{
	int i, j, k, l;

	/* Match string from the beginning */
	i = MatchWildStr (s, p);
	j = 0;
	if (i == -1)
		return false;
	
	j = i;
	while (s[i] != '\0')
	{
		/* burn repeated * */
		while (p[j] == '*')
			j++;

		/* assume * consumes k characters */
		for (k = 0; (l = MatchWildStr(&s[i+k], &p[j])) == -1; k++)
		{
			if (s[i+k] == '\0')
			{
				/* we have checked the whole s, but no luck */
				return false;
			}
		}

		i += k + l;
		j += l;
	}

	/* burn all * */
	while (p[j] == '*')
		j++;
	
	if (s[i] == '\0' && p[j] == '\0')
		return true;

	/* last char is *; would match s till end*/
	if (p[j-1] == '*' && p[j] == '\0')
		return true;
	
	return false;
}

