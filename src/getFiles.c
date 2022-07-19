#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <msap.h>
#include "getFiles.h"

void getFiles (char *file, sa *files)
{
	sa s;

	// open file
	FILE *fp = fopen(file, "r");

	// get file size
	fseek(fp, 0, SEEK_END);
	const size_t size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	// read file
	char *data = (char*)malloc(size * sizeof(char));

	fread(data, size, 1, fp);

	// close file
	fclose(fp);

	// split data
	s = saSplit(data, '\n');
	free(data);

	// get hash includes
	ssize_t *hashs = saSubSearch(s, "#include \"", -1);
	char *hold;
	size_t plus;

	// move file names into files structure
	for (register ssize_t i = 0; hashs[i]!=-1; i++)
	{
		plus = 1;

		// make a pointer short cut
		hold = s.items[hashs[i]];

		// remove last char
		hold[strlen(hold)-1] = (char)0;

		// get value shift ro remove "#include"
		for (register size_t j = 0; hold[j]!=0 && hold[j]!='\"'; j++)
		{
			plus++;
		}

		// push onto files structure with out
		// "#include"
		saPush(files, hold+plus);
	}

	// free data
	free(hashs);
	saFree(s);
}
