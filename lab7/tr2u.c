#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main (int argc, char *argv[])
{
    // check for same input string lengths
    if (strlen(argv[1]) != strlen(argv[2]))
    {
	fprintf(stderr, "Input string lengths not equal\n");
	exit(1);
    }

    int i;
    int j;
    // check for all distinct 'from' string
    for (i = 0; i < (strlen(argv[1])-1); i++)
    {
	for (j = i + 1; j < strlen(argv[1]); j++)
	{
	    if (argv[1][i] == argv[1][j])
	    {
		fprintf(stderr, "Duplicate character in 'from' input\n");
		exit(1);
	    }
	}
    }
    
    int k;
    int replace;
    char current;
    int test;
    
    test = read(0, &current, 1);
    
    if (test == -1)
    {
	fprintf(stderr, "Read failed");
	exit(1);
    }
    
    while (test > 0)
    {
	replace = 0;
	for (k = 0; k < strlen(argv[1]); k++)
	{
	    if (current == argv[1][k])
	    {
		replace = 1;
		char tmp = argv[2][k];
		write(1, &tmp, 1);
	    }
	}

	if (replace == 0)
	    write(1, &current, 1);

	test = read(0, &current, 1);
    }
}
