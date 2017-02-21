#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    // check for equal input string lengths
    if (strlen(argv[1]) != strlen(argv[2]))
    {
	fprintf(stderr, "Input string lengths not equal\n");
	exit(1);
    }

    int i;
    int j;
    // check for all distinct chars in 'from' string
    for (i = 0; i < (strlen(argv[1])-1); i++)
    {
	for (j = i+1; j < strlen(argv[1]); j++)
	{
	    if (argv[1][i] == argv[1][j])
	    {
		fprintf(stderr, "Duplicate character in 'from' input\n");
		exit(1);
	    }
	}
    }
    
    int k;
    int replace;   // flag to check if replaced
    char current = getchar();

    while (current != EOF)
    {
	replace = 0;
	for (k = 0; k < strlen(argv[1]); k++)
	{
	    if (current == argv[1][k])
	    {
		replace = 1;
		putchar(argv[2][k]);
	    }
	}

	if (replace == 0)
	    putchar(current);

	current = getchar();
    }

}
