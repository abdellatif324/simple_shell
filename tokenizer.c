#include "shell.h"
/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
        int a, b, c, f, e = 0;
        char **s;
        if (str == NULL || str[0] == 0)
                return (NULL);
        if (!d)
                d = " ";
        for (a = 0; str[a] != '\0'; a++)
                if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
                        e++;
        if (e == 0)
                return (NULL);
        s = malloc((1 + e) * sizeof(char *));
        if (!s)
                return (NULL);
        for (a = 0, b = 0; b < e; b++)
        {
                while (is_delim(str[a], d))
                        a++;
	       	c = 0;
                while (!is_delim(str[a + c], d) && str[a + c])
                        c++;
                s[b] = malloc((c + 1) * sizeof(char));
                if (!s[b])
                {
                        for (c = 0; c < b; c++)
                                free(s[c]);
                        free(s);
                        return (NULL);
                }
                for (f = 0; f < c; f++)
                        s[b][f] = str[a++];
                s[b][f] = 0;
        }
        s[b] = NULL;
        return (s);
}
/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
        int i, j, k, m, numwords = 0;
        char **s;
        if (str == NULL || str[0] == 0)
                return (NULL);
        for (i = 0; str[i] != '\0'; i++)
                if ((str[i] != d && str[i + 1] == d) ||
                                    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
                        numwords++;
        if (numwords == 0)
                return (NULL);
        s = malloc((1 + numwords) * sizeof(char *));
        if (!s)
                return (NULL);
        for (i = 0, j = 0; j < numwords; j++)
        {
                while (str[i] == d && str[i] != d)
                        i++;
                k = 0;
                while (str[i + k] != d && str[i + k] && str[i + k] != d)
                        k++;
                s[j] = malloc((k + 1) * sizeof(char));
                if (!s[j])
                {
                        for (k = 0; k < j; k++)
                                free(s[k]);
                        free(s);
                        return (NULL);
                }
                for (m = 0; m < k; m++)
                        s[j][m] = str[i++];
                s[j][m] = 0;
        }
        s[j] = NULL;
        return (s);
}

