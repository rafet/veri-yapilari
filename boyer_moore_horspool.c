#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define string char *

int *generateBadMatchTable(string pattern)
{
    static int table[26];
    int i, l = strlen(pattern);

    for (i = 0; i < l - 1; i++)
        table[pattern[i] - 'a'] = l - i - 1;

    for (i = 0; i < 26; i++)
        if (table[i] == 0)
            table[i] = l;

    return table;
}
int search(string text, string pattern)
{
    int *badMatch = generateBadMatchTable(pattern),
        n = strlen(text),
        m = strlen(pattern),
        i = m - 1,
        j, k;
    while (i < n)
    {
        k = i;
        j = m - 1;
        while (k >= 0 && j >= 0 && text[k] == pattern[j])
        {
            k--;
            j--;
        }
        if (j < 0)
            return k + 1;
        i += badMatch[text[i] - 'a'];
    }
    return -1;
}
// ./a.out tooth
int main(int argc, char *argv[])
{
    string text = "trusthardtoothbrushes";
    string pattern = argv[1];
    int index = search(text, pattern);
    if (index > -1)
        printf("Found in index %d", index);
    else
        printf("'%s' not found in the text.", pattern);
    return 0;
}
