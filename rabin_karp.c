#include <stdio.h>
#include <string.h>
#include <math.h>

#define prime 3
#define string char *
int val(char c)
{
    return c - 'a' + 1;
}
int calcSingleHash(string txt)
{
    int hash = 0, i;
    for (i = 0; i < strlen(txt); i++)
        hash += val(txt[i]) * pow(prime, i);
    printf("%d ", hash);
    return hash;
}
int *calculateHashes(string text, string pattern)
{
    static int hashes[100];
    int n = strlen(text),
        lastHash = calcSingleHash(pattern),
        patternLength = strlen(pattern),
        i, k = 0;

    hashes[k++] = lastHash;
    for (i = 1; i < n - patternLength + 1; i++)
    {
        lastHash = (lastHash - val(text[i - 1])) / prime;
        lastHash += val(text[i + patternLength - 1]) * pow(prime, patternLength - 1);
        hashes[k++] = lastHash;
    }
    return hashes;
}

int find(string text, string pattern)
{
    int *hashes = calculateHashes(text, pattern);
    int hashesLength = strlen(text) - strlen(pattern) + 1;

    int patternHash = 0, i;
    for (i = 0; i < strlen(pattern); i++)
        patternHash += val(pattern[i]) * pow(prime, i);

    for (i = 0; i < hashesLength; i++)
        if (patternHash == hashes[i])
            return i;

    return -1;
}

int main()
{
    string text = "rafettopcu";
    string pattern = "etto";

    int index = find(text, pattern);
    if (index > -1)
        printf("Found in index %d", index);
    else
        printf("'%s' not found in the text.", pattern);
    return 0;
}
