/*
**			DFIX Copyright (C) 1985, 1986  Howard Rumsey Jr.
**
**	DFIX disk fix utility. Reads the whole DOS partion on a disk (floppy,
**	hard disk, ramdisk) and, if directed, marks bad clusters in the FAT(s).
**
**	Usage:
**			dfix [d:]
**
**		d: is an optional device specifier. If not specified DFIX will
**			use the default device.
**
**	If DFIX finds a bad cluster already allocated to a file this will
**	be reported and no further action taken.  If DFIX finds an unallocated
**	cluster it marks it's local copy of the FAT. At the end of the testing
**	the user is asked if he wishes to permanently mark the cluster as BAD.
**	
*/

/*
**
**	DFIX is a substitute for the disktest program included with Version 3
**	of The Norton Utilities (tm). The Norton package contains many other
**	useful tools. I wrote this program and am placing it in public domain
**	because of it's (sometimes) critical value.
**
**	This program may be freely copied and used for any non-commercial
**	purpose.
**
**				Howard Rumsey
**				Caltech
**				Pasadena, CA 91125
**
**				CompuServe [72426,3722]
**				December 10, 1986
**
**	v1.2 Toad Hall Tweak, 7 May 91
	Slight touches for Turbo C compile.
	Reformatted to a "normal" indentation, etc., ala K&R.
	No functional changes.
*/

#include <stdio.h>
#include <ctype.h>

#define DOS12 4086		/* FAT 12 or 16 bit MAGIC NUMBER */

typedef unsigned int uint;

#define BSIZE (14+2*8)	/* Should be the size of the following structure */
struct bootsec {		/* BOOT sector structure */
	char jump[3];		/* jump around this stuff */
	char oem[8];		/* OEM name, version */
	uint bytpsec;		/* bytes per sector */
	char secpclu;		/* sectors per cluster */
	uint fatsec;		/* no. reserved sectors = FAT start */
	char nfats;			/* number of FATs */
	uint ndir;			/* number of ROOT directory entries */
	uint totsec;		/* number of sectors in this partition */
	char meddes;		/* media descriptor byte */
	uint fatcnt;		/* number of sectors in a single FAT */
	uint secptrk;		/* sectors per track */
	uint nheads;		/* number of heads this device */
	uint hidsec;		/* number of hidden sectors */
} *boot;

int fat12;			/* TRUE if 12 bit FAT entries */
int badmark;		/* FAT flag used to mark a bad cluster ... */
					/* 0xff7 for 12 bit FATs, 0xfff7 for 16 bit FATs */
int rdsize;			/* ROOT directory size in sectors */
char *fattab;		/* pointer to local copy of FAT */
char *clubuf;		/* points to cluster input buffer */

extern struct {		/* communicate area for device allocation data */
	int d;			/* device number A=0,... */
	char mb;		/* media byte */
	char spc;		/* sectors per cluster */
	uint nc;		/* number clusters */
	uint ss;		/* sector size */
} ALLOCTAB;

#ifdef __TURBOC__
#include <stdlib.h>		/* malloc() */
/* prototypes (I like prototypes!) */
void show_usage(void);
void errexit(char *str);
char *plural(int n);
void doOpen(int dev);
void doDisk(int dev);
int fatstat(unsigned c);
void pokefat(unsigned c,unsigned bm);
extern int defaultdev(void);
extern void devAlloc(void);
extern int rdDevice(int dev, int startsec, int nrsecs, char *buffaddr);
extern int wrDevice(int dev, int startsec, int nrsecs, char *buffaddr);

#else
char *malloc(), *gets();
#endif

main(ac,av) char *av[]; {
	int dev;

	printf("DFIX Version 1.2 Copyright (C) 1986 Howard Rumsey Jr.\n\n");
#ifdef __TURBOC__
	if(_osmajor < 2)
#else
	if((dosVersion() & 0xff) < 2)
#endif
		errexit("Must have DOS 2.0 or higher.\n");

	if(ac == 1) {
		show_usage();
		dev = defaultdev();
	}
	else {
		if(av[1][1] != ':' || !isalpha(av[1][0])) {
			show_usage();
			exit(1);
		}
		dev = toupper(av[1][0])-'A';
	}
	doOpen(dev);
	doDisk(dev);
	return 0;
}

void show_usage(void)
{
	fprintf(stderr, "DFIX will test the whole DOS partition.\n");
	fprintf(stderr, "If you wish, it will mark bad sectors in the FAT.\n");
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "  dfix [d:]\n");
	fprintf(stderr, "where d: is a device specifier.\n");
}

void errexit(str) char *str;
{
	fputs(str, stderr);
	exit(-1);
}

char *plural(n) int n;
{
	return n>1 ? (char *)"s" : (char *)"";
}

void doOpen(dev) int dev;
{
	/* Check the size of bootsec to avoid a mismatch between
		"C" and DOS data allocation */
	if(sizeof(struct bootsec) != BSIZE)
		errexit("BOOT sector data problem. Sorry!\n");

	/* Gather and print the device parameters */

	ALLOCTAB.d = dev;
	devAlloc();		/* build the device allocation table */
	boot = (struct bootsec *) malloc(ALLOCTAB.ss);
	if(boot == NULL)
		errexit("Can't allocate BOOT buffer\n");
	if(rdDevice(dev, 0, 1, (char *) boot) != 0)
		errexit("Can't read BOOT sector\n");

	/* test for compatibility of BOOT sector and ALLOCTAB */
	if(ALLOCTAB.mb  != boot->meddes ||
	   ALLOCTAB.spc != boot->secpclu ||
	   ALLOCTAB.ss  != boot->bytpsec )
		errexit("BOOT sector information error. Possibly non-DOS 2+ media.\n");

	/* do we have 12 bit FAT entries? */
	fat12 = (ALLOCTAB.nc <= DOS12);
	badmark = fat12 ? 0xff7 : 0xfff7;
	/* compute ROOT directory size */
	rdsize = (int) ((boot->ndir * 32L)/boot->bytpsec);

	/* print the device information */
	printf("\nInformation for Device %c:\n",'A'+dev);
	printf("  OEM name: %8s\n",boot->oem);
	printf("  There are %d bytes per sector.\n",boot->bytpsec);
	if(boot->secpclu == 1)
		printf("  There is one sector per cluster.\n");
	else
		printf("  There are %d sectors per cluster.\n",boot->secpclu);
	printf("  There are %d clusters numbered from 2.\n", ALLOCTAB.nc);
	if(boot->nfats == 1)
		printf("  There is one FAT, %d sector%s long.\n",
				boot->fatcnt, plural(boot->fatcnt));
	else
		printf("  There are %d FATs, each %d sector%s long.\n",
				boot->nfats, boot->fatcnt, plural(boot->fatcnt));
	printf("  The ROOT directory can hold %d entries and is %d sectors long.\n",
			boot->ndir, rdsize);
}


void doDisk(dev) int dev;
/* read the FATs, ROOT-dir, and clusters */
{
	int lsec;					/* logical sector number */
	int jf, kf;
	int nbad, newbad, nbadf; 	/* counters for bad clusters */
	char yesno[80];				/* answer 'update' question */

	/* get space for one FAT and one cluster */
	fattab = malloc(boot->fatcnt * boot->bytpsec);
	if(fattab == NULL)
		errexit("Unable to allocate memory for a FAT.\n");
	clubuf = malloc(boot->bytpsec * boot->secpclu);
	if(clubuf == NULL)
		errexit("Unable to allocate memory for reading clusters.\n");

	printf("Reading the first FAT.\n");
	if(rdDevice(dev, boot->fatsec, boot->fatcnt, fattab) != 0)
		errexit("Can't read first FAT. Device unusable.\n");

	/* read the rest, one sector at a time */
	lsec = boot->fatsec + boot->fatcnt;
	for(jf=1; jf<boot->nfats; jf++) {
		printf("Reading the next FAT.\n");
		for(kf=0; kf<boot->fatcnt; kf++) {
			if(rdDevice(dev, lsec++, 1, clubuf) != 0)
				errexit("Error reading second (or later) FAT.\n");
			/* should compair FATs */
		}
	}

	printf("Reading the ROOT directory.\n");
	for(jf=0; jf<rdsize; jf++)
		if(rdDevice(dev, lsec++, 1, clubuf) != 0)
			errexit("Error reading the ROOT directory. Device unusable.\n");

	nbad = newbad = nbadf = 0;
	printf("Checking the clusters now.\n");
	printf("Cluster      ");
	for(jf=2; jf<ALLOCTAB.nc+2; jf++) {
		printf("\b\b\b\b\b%5d",jf);
		if(fatstat(jf) == badmark) {
			nbad++;
			printf(" is bad.  Already marked as bad.\n");
			printf("Cluster      ");
		}
		else if(rdDevice(dev, lsec, boot->secpclu, clubuf) != 0) {
			nbad++;
			printf(" is bad.  ");
			if(fatstat(jf)) {
				nbadf++;
				printf("\007Included in some file.  Not marked.\n");
			}
			else {
				newbad++;
				printf("\007Unallocated.\n");
				pokefat(jf,badmark);
			}
			printf("Cluster      ");
		}
		lsec += boot->secpclu;
	}
	printf("\b\b\b\b\b\b\b\b\b\b\b\b\b");
	if(nbad == 0) {
		printf("No bad clusters were found.\n");
		return;
	}
	printf("The number of bad clusters found was %d.\n",nbad);
	if(nbadf != 0) {
		if(nbad == 1) printf("Some file has a bad cluster.\n");
		else printf("One or more files have bad clusters.");
		printf("The DOS command:\n  copy *.* nul\n");
		printf("will check all the files in the default directory.\n");
		printf("Use the DOS 'RECOVER' utility to repair bad files.\n");
		printf("Then erase the bad files and run DFIX again.\n");
	}
	if(newbad == 0) {
		printf("No %s bad clusters were found.",
				nbadf ? "repairable" : "new");
		return;
	}
	printf("The number of repairable bad clusters is %d.\n", newbad);
	printf("Do you wish to update the FAT? (y/N) ");
	if(gets(yesno) && toupper(*yesno) == 'Y') {
		for(jf=0, lsec=boot->fatsec; jf<boot->nfats; jf++, lsec += boot->fatcnt)
		  if(wrDevice(dev, lsec, boot->fatcnt, fattab) != 0)
		    errexit("Can't write new FAT. Device maybe unusable\n");
		printf("FAT updated.\n");
	}
	else printf("FAT not updated.\n");
}

fatstat(c) unsigned c;
/* Return the FAT entry for cluster "c". */
{
	int *jj;
	if(fat12) {			/* 12 bit FAT entries */
		jj = (int *) (fattab+((c+c+c) >> 1));
		if(c&1) return((*jj >> 4) & 0xfff);
		return *jj & 0xfff;
	}
	return ((int *) fattab)[c];	/* 16 bit FAT entries */
}

void pokefat(c,bm) unsigned c, bm;
/* Set the FAT entry for cluster "c" to bm. */
/* Changes the copy of the FAT in MEMORY only! */
{
	int *jj;
	if(fat12) {
		jj = (int *) (fattab+((c+c+c) >> 1));
		if(c&1) {
			*jj = (*jj & 0xf) | (bm << 4);
			return;
		}
		*jj = (*jj & 0xf000) | (bm & 0xfff);
		return;
	}
	/* else 16 bit FAT entries */
	((int *) fattab)[c] = (int) bm;
}
