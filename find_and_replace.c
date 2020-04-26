#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 10000
#define true 1
#define false 0
#define string char *

// Case Sensitive özelliği için  A-Z harflerinin a-z değerlerini,
// A-Z dışındaki karakterlerin kendi değerlerini döndürür.
int charVal(char c, int caseSensitive)
{
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ? (caseSensitive ? c : (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c) : c;
}

// Dosyayı okur ve dinamik bir diziye aktarır. İhtiyaç oldukça dizide yer açılır.
string readFromFile(string filename)
{
  FILE *file = fopen(filename, "r");
  int size = 1000, // dizi için başlangıç boyutu belirledik
      i = 0;
  string text = (string)malloc(sizeof(char) * size); // bellekte dizi için yer açtık
  while (!feof(file))
  {
    *(text + i++) = fgetc(file); // dosyayı karakter karakter okuyup diziye ekledik ve
                                 // her ekleme işleminden sonra indexi 1 artırdık
    if (i >= size)               // index değeri dizinin  boyutunu aştıysa, bellekte 1000 karakterlik yer daha açarız
    {
      size += 1000;
      text = (string)realloc(text, size * sizeof(char));
    }
  }
  text[i] = 0;  // terminalde print sorunu çıktığı için text'in son karakterini \0 yaparız
  fclose(file); // dosya ile işimz bittiği için dosyayı kapatırız
  return text;
}

// Boyer-Moore-Horspool alogritması için Bad Match Table oluşturur.
int *generateBadMatchTable(string pattern, int caseSensitive)
{
  static int table[256];
  int i, l = strlen(pattern);

  for (i = 0; i < l - 1; i++)
    table[charVal(pattern[i], caseSensitive)] = l - i - 1; // length - index - 1

  for (i = 0; i < 256; i++)
    if (table[i] == 0)
      table[i] = l;
  return table;
}

// Verilen text içinde find değerini arar ve bulunan indexleri int* olarak geri döndürür.
// Indexlerin sayısını geri döndürmek için findCount pointer'ına indexlerin sayısını yazarız
// Aramayı Boyer-Moore-Horspool algoritması kullanarak yapıyoruz.
int *findText(string find, string text, int caseSensitive, int *findCount)
{
  int *badMatch = generateBadMatchTable(find, caseSensitive),
      textLen = strlen(text),
      findLen = strlen(find),
      i = findLen - 1,
      j, k, counter = 0;
  int *indexes = (int *)malloc(1000 * sizeof(int));
  while (i < textLen - 1)
  {
    k = i;
    j = findLen - 1;
    while (k >= 0 && j >= 0 && charVal(text[k], caseSensitive) == charVal(find[j], caseSensitive))
    {
      k--;
      j--;
    }
    // Burada içi içe geçmiş olan stringlerin kontrolünü yapıyoruz.
    // Örneğin elimizde xxyxxyxxyxxyx gibi bir string varsa ve xxyx yerine a yokmak istiyorsak
    // bu stringde 4 tane xxyx var fakat ilk xxyx yerine a koyduğumuz zaman ikinci xxyx 'i kaybediyoruz
    // dolayısıyla eğer yeni bulunan index bi önceki indexin içinde bulunuyorsa, o indexi dahil etmiyoruz.
    if (j < 0 && (counter == 0 || (k + 1 - indexes[counter - 1] >= findLen)))
      indexes[counter++] = k + 1;
    i += badMatch[charVal(text[i], caseSensitive)];
  }
  *findCount = counter;
  return indexes;
}

// Yeni text'i aynı dosyanın üstüne yazar.
void writeToFile(string filename, string text)
{
  FILE *file = fopen(filename, "w");
  int i = 0, len = strlen(text);
  while (text[i] && i < len - 1)
    fputc(text[i++], file);
  fclose(file);
}
//
string replace(string filename, string find, string rep, int caseSensitive)
{
  int count;
  string text = readFromFile(filename);
  printf("Find: %s\nReplace: %s\nOption: %s\n", find, rep, (caseSensitive ? "Case sensitive" : "Not case sensitive"));
  printf("Text: %s\n", text);
  int *indexes = findText(find, text, caseSensitive, &count);
  if (count > 0)
  {
    int k = count - 1,
        textLen = strlen(text),
        repLen = strlen(rep),
        findLen = strlen(find),
        i, j;

    if (findLen <= repLen)
    {
      for (i = textLen - 1; i > indexes[0]; i--)
      {
        if (k >= 0 && i > indexes[k])
          *(text + i + (repLen - findLen) * (k + 1)) = *(text + i);
        else
          k--;
      }
    }
    else
    {
      k = 1;
      for (i = indexes[0] + repLen; i < textLen; i++)
      {
        if (k < count && indexes[k] == i + (findLen - repLen) * k)
          k++;
        *(text + i) = *(text + i + (findLen - repLen) * k);
      }
    }
    for (i = 0; i < count; i++)
      for (j = 0; j < repLen; j++)
        *(text + indexes[i] + j + (repLen - findLen) * i) = *(rep + j);
    writeToFile(filename, text);
  }

  printf("New Text: %s\n", text);
  printf("Found and Replaced: %d\n", count);
  return text;
}
int main()
{
  clock_t start, end;
  double executionTime;
  start = clock();

  char filename[SIZE] = "find.txt";
  char find[SIZE] = "do";
  char rep[SIZE] = "think about";
  int caseSensitive = true;

  string text = replace(filename, find, rep, caseSensitive);

  end = clock();
  executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Running Time: %f miliseconds", executionTime);
  return 0;
}
