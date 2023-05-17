#include "shell.h"

/**
 * **string_word - splits a string into words. Repeat delimiters are ignored
 * @strng: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **string_word(char *strng, char *d)
{
	int a, b; 
	int k, num_words = 0, n;
	char **z;

	if (strng == NULL || strng[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; strng[a] != '\0'; a++)
		if (!_isdelim(strng[a], d) && (_isdelim(strng[a + 1], d) || !strng[a + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	z = malloc((1 + num_words) * sizeof(char *));
	if (!z)
		return (NULL);
	for (a = 0, b = 0; b < num_words; b++)
	{
		while (_isdelim(strng[a], d))
			a++;
		k = 0;
		while (!_isdelim(strng[a + k], d) && strng[a + k])
			k++;
		z[b] = malloc((k + 1) * sizeof(char));
		if (!z[b])
		{
			for (k = 0; k < b; k++)
				free(z[k]);
			free(z);
			return (NULL);
		}
		for (n = 0; n < k; n++)
			z[b][n] = strng[a++];
		z[b][n] = 0;
	}
	z[j] = NULL;
	return (z);
}

/**
 * **string_word2 - string into words
 * @strng: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **string_word2(char *strng, char d)
{
	int a, b;
	int k, num_words = 0, m;
	char **z;

	if (strng == NULL || strng[0] == 0)
		return (NULL);
	for (a = 0; strng[a] != '\0'; a++)
		if ((strng[a] != d && strng[a + 1] == d) ||
				    (strng[a] != d && !strng[a + 1]) || strng[a + 1] == d)
			num_words++;
	if (num_words == 0)
		return (NULL);
	z = malloc((1 + num_words) * sizeof(char *));
	if (!z)
		return (NULL);
	for (a = 0, b = 0; b < num_words; b++)
	{
		while (strng[a] == d && strng[a] != d)
			a++;
		k = 0;
		while (strng[a + k] != d && strng[a + k] && strng[a + k] != d)
			k++;
		z[b] = malloc((k + 1) * sizeof(char));
		if (!z[b])
		{
			for (k = 0; k < b; k++)
				free(z[k]);
			free(z);
			return (NULL);
		}
		for (n = 0; n < k; n++)
			z[b][m] = strng[a++];
		z[b][n] = 0;
	}
	z[b] = NULL;
	return (z);
}
