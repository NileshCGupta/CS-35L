#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int comparisons = 0;
int frobcmp(char const* a, char const* b);
int _frobcmp(const void* a, const void* b);

int main()
{
  struct stat filestats;
  fstat(0, &filestats);

  int filesize = filestats.st_size;
  
  if (filesize == 0)
      filesize = 1024;
  
  char* file = malloc(filesize * sizeof(char));

  if (file == NULL)
  {
      fprintf(stderr, "Failed to allocate memory\n");
      exit(1);
  }

  int memoryX = 1; // memory multiplier
  int numOfChars = 0;
  int test;
  char current;
  
  test = read(0, &current, 1);

  if (test == -1)
  {
      fprintf(stderr, "Empty file\n");
      exit(1);
  }   

  // fill char array
  while (test > 0)
  {
      if (numOfChars == memoryX * filesize)
      {
	  memoryX++;
	  file = realloc(file, memoryX * filesize * sizeof(char));
	  if (file == NULL)
	  {
	      fprintf(stderr, "Failed to allocate memory\n");
	      exit(1);
	  }
      }

      file[numOfChars] = current;
      test = read(0, &current, 1);
      numOfChars++;
  }

  if (file[numOfChars-1] != ' ') 
  {
      if (numOfChars == memoryX * filesize)
      {
	  memoryX++;
	  file = realloc(file, memoryX * filesize * sizeof(char));
	  if (file == NULL)
	  {
	      fprintf(stderr, "Failed to allocate memory\n");
	      exit(1);
	  }
      }
      
      0file[numOfChars] = ' '; // makes sure array ends on a space
      numOfChars++;
  }

  char** lines = malloc(filesize * sizeof(char*));

  if (lines == NULL)
  {
      fprintf(stderr, "Failed to allocate memory");
      exit(1);
  }

  int i = 0;
  int count = 0;
  int memX = 1; // another memory multiplier
  char* head = &file[0]; // tracks the start of every line
  
  while (i < numOfChars)
  {
      if (count == memX * filesize)
      {
	  memX++;
	  lines = realloc(lines, memX * filesize * sizeof(char*));
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

  qsort(lines, count, sizeof(char*), _frobcmp);

  int a;
  char space = ' ';
  
  for (a = 0; a < count; a++)
  { 
      int b = 0;
      while (lines[a][b] != ' ')
      {
	  char tmp = lines[a][b];
	  write(1, &tmp, 1);
	  b++;
      }
      
      write(1, &space, 1);
  }
  
  free(file);
  free(lines);

  fprintf(stderr, "\n%s %d\n", "Comparisons:", comparisons);
  return 1;
}

int _frobcmp (const void *a, const void *b)
{
    return frobcmp(*(const char **)a, *(const char **)b);
}

int frobcmp (char const *a, char const *b)
{
    comparisons++;
    int index = 0;
    while (a[index] != ' ' && b[index] != ' ')
    {
	if ((a[index] ^ 42) == (b[index] ^ 42))
	{
	    index++;
	}
	else if ((a[index] ^ 42) > (b[index] ^ 42))
	{
	    return 1;
	}
	else
	{
	    return -1;
	}
    }

    if ((a[index] == ' ') && (b[index] == ' '))
    {
	return 0;
    }
    else if (a[index] != ' ')
    {
	return 1;
    }
    else
    {
	return -1;
    }

}
