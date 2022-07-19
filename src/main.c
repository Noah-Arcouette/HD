#include <stdio.h>
#include "info.h"
#include <macsv.h>
#include <stdlib.h>
#include <msap.h>

int main ()
{
	sa s;
	sa files = { NULL, 0 };


	FILE *fp = fopen("test.c", "r");

	fseek(fp, 0, SEEK_END);
	const size_t size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char *data = (char*)malloc(size * sizeof(char));

	fread(data, size, 1, fp);
	fclose(fp);

	s = saSplit(data, '\n');
	free(data);

	ssize_t *hashs = saSubSearch(s, "#include \"", -1);
	char *hold;

	for (register ssize_t i = 0; hashs[i]!=-1; i++)
	{
		hold = s.items[hashs[i]];
		hold[strlen(hold)-1] = (char)0;
		saPush(&files, hold+10);
	}

	free(hashs);
	saFree(s);

	for (register size_t i = 0; i<files.size; i++)
	{
		puts(files.items[i]);
	}

	saFree(files);

	return 0;
}
