#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int frobcmp(char const* a, char const* b);
int cmpfrob(const void* a, const void* b);

int main()
{
  char* file = malloc(1024 * sizeof(char));

  if (file == NULL)
  {
      fprintf(stderr, "Failed to allocate memory");
      exit(1);
  }

  int memoryX = 1; // memory multiplier
  int numOfChars = 0;
  int current = getchar();

  if (current == EOF)
  {
      fprintf(stderr, "Empty file");
      exit(1);
  }   
 
  while (current != EOF)
  {
      if (numOfChars == memoryX * 1024)
      {
	  memoryX++;
	  file = realloc(file, memoryX * 1024 * sizeof(char));
	  if (file == NULL)
	  {
	      fprintf(stderr, "Failed to allocate memory");
	      exit(1);
	  }
      }

      file[numOfChars] = current;
      current = getchar();
      numOfChars++;
  }

  if (file[numOfChars-1] != ' ') 
  {
      if (numOfChars == memoryX * 1024)
      {
	  memoryX++;
	  file = realloc(file, memoryX * 1024 * sizeof(char));
	  if (file == NULL)
	  {
	      fprintf(stderr, "Failed to allocate memory");
	      exit(1);
	  }
      }
      
      file[numOfChars] = ' '; // makes sure array ends on a space
      numOfChars++;
  }

  int i = 0;
  char** lines = malloc(1024 * sizeof(char*));

  if (lines == NULL)
  {
      fprintf(stderr, "Failed to allocate memory");
      exit(1);
  }
  
  char* head = &file[0];
  int memX = 1; // another memory multiplier
  int count = 0;

  while (i < numOfChars)
  {
      if (count == memX * 1024)
      {
	  memX++;
	  lines = realloc(lines, memX * 1024 * sizeof(char*));
	  if (lines == NULL)
	  {
	      fprintf(stderr, "Failed to allocate memory");
	      exit(1);
	  }
      }

      if (file[i] == ' ')
      {
	  lines[count] = head;
	  count++;
	  head = &file[i+1];
      }

      i++;
  }

  qsort(lines, count, sizeof(char*), cmpfrob);

  for (int a = 0; a < count; a++)
  { 
      int b = 0;
      while (lines[a][b] != ' ')
      {
	  putChar(lines[a][b]);
	  b++;
      }
      putChar(' ');
   
  }

  i = 0;
  
  while (i < count)
  {
      if (lines[i] != NULL)
	  free(lines[i]);
      i++;
  }

  free(file);
  free(lines);
  
  return 1;
}

int cmpfrob (const void *a, const void *b)
{
    return frobcmp(*(const char **)a, *(const char **)y);
}

int frobcmp (char const *a, char const *b)
{
    
  int index = 0;
  
  while (a[index] != ' ' && b[index] != ' ')
  {
      if (a[index] ^ 42 == b[index] ^ 42)
      {
	  index++;
      }
      else if (a[index] ^ 42 > b[index] ^ 42)
      {
	  return 1;
      }
      else
      {
	  return -1;
      }
  }

  if (a[index] == ' ' && b[index] == ' ')
  {
      return 0;
  }
  else if (a[index] == ' ')
  {
      return -1;
  }
  else
  {
      return 1;
  }
}
