#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <malloc.h>
#include <string.h>

#define BLOCKSIZE ((unsigned int)1024)

static char tmpfn[] = "zerodisk.tmp";

int main(int argc, char *argv[])
{
	char *buf, *tmppath;
	FILE *fp;
	int output;

	if (argc > 2)
  {
		fprintf(stderr, "Usage: zerodisk [device]");
		exit(-1);
	}
	if ((buf = (char *)calloc(BLOCKSIZE, sizeof(char))) == 0)
  {
		fprintf(stderr, "zerodisk: cannot calloc %u bytes.\n" , BLOCKSIZE);
		exit(-1);
	}
	if (argc == 2)
  {
		unsigned int l = strlen(argv[1]) + strlen(tmpfn) + 1;
		if ((tmppath = (char *)malloc(l)) == 0)
    {
			fprintf(stderr, "zerodisk: cannot malloc %u bytes.\n", l);
			exit(-1);
		}
		sprintf(tmppath, "%s%s%c", argv[1], tmpfn, (char)0);
	}
  else
    sprintf(tmppath, "%s%c", tmpfn, (char)0);
	if ((fp = fopen(tmppath, "wb")) == 0)
  {
		fprintf(stderr, "zerodisk: cannot open %s.", tmppath);
		exit(-1);
	}
	output = fileno(fp);
	while (write(output, buf, BLOCKSIZE) >= 0) ;
	(void)fclose(fp);
	unlink(tmppath);
	return 0;
}
