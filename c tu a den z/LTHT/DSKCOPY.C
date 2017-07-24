#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <malloc.h>
#include <process.h>

#define TRUE 1
#define FALSE 0

char	    *pSource;
size_t    nBufSize;
int	      errno;
int	      nNumFiles;
char	    szSyntaxMsg [] = "Cu phap: DSKCOPY <O nguon:> <O dich:> -NoPrompt \n\n",
	        szMsg[80] = "\n";

union REGS inregs, outregs;
struct SREGS segregs;
unsigned _osversion;

main(int argc, char * argv[] )
{
  int bPrompt, bCheck, bFormat, n;
  struct drvinfo_t drv1, drv2;
  int crterror = 0;
  char szDrive1 [10], szDrive2 [10];

  errno = EINVAL;

  strcpy (szDrive1, " :\\*.*");
  strcpy (szDrive2, " :");
  if (argc < 3)
    ErrExit("");
  szDrive1 [0] = toupper(*argv [1]);
  szDrive2 [0] = toupper(*argv [2]);

  /* Kiem tra xem co o nguon va dich co la 1 khong */
  if (szDrive1 [0] == szDrive2 [0])
    ErrExit("Sourcedrive = Targetdrive");

  bPrompt = TRUE;
  bCheck  = TRUE;
  bFormat = FALSE;
  for (n = 3; n < argc; n++)
  {
    if (argv [n] [0] == '-' || argv [n] [0] == '/')
	  switch ( toupper(argv [n] [1]) )
	  {
	    case 'N':
	       bPrompt = FALSE;
	       break;
	    case 'X':
	       bCheck = FALSE;
	       break;
	    case 'F':
	       bFormat = TRUE;
	  }
  }
  setint24 (&crterror);

  while ( !drvinfo(szDrive1 [0] - '@', &drv1))
  {
    if (!crterror)
	  {
	    sprintf (szMsg, "O dia %c: khong hop le", *szDrive1);
	    ErrExit (szMsg);
	  }
    crterror = 0;
    printf("\r\7Khong doc duoc dia %c:  Thu lai? (Y/N)  \b", *szDrive1);
    if (toupper (getche()) != 'Y')
	    ErrExit ("");
  }

  /* perform media check on target drive */
  while ( !drvinfo(szDrive2 [0] - '@', &drv2))
  {
    if (!crterror)
	  {
	    sprintf (szMsg, "O dia %c: khong hop le", *szDrive2);
	    ErrExit (szMsg);
	  }

    if (!bFormat)
	  {
	    printf("\r\7Khong the doc duoc o %c:  Thu lai? (Y/N)  \b", *szDrive2);
	      if (toupper (getche()) == 'Y')
	    continue;
      printf ("\rBan co muon format dia %c: khong? (Y/N) ",*szDrive2);
	    bFormat = (toupper (getche()) == 'Y');
	  }

    if (crterror && bFormat)
	  {
	    switch (LOBYTE(_osversion))
	    {
	      case 3:
	         strcpy(szMsg, "/H");
	         break;
        case 4:
	         strcpy(szMsg, "/AUTOTEST");
	         break;
	      default:
	         szMsg[0] = '\0';
	    }
	    printf("\rFormatting %s                                     \n", szDrive2);
	    spawnlp(P_WAIT,"format.com", "format.com", szDrive2, szMsg, NULL);
	  }
    else
	  {
	    ErrExit("");
	  }
    crterror = 0;
    bFormat = FALSE;
  }
  restint24 ();

  if (bCheck)
  {
    if (drv2.type == 0x0f8)
	  {
	    errno = EACCES;
	    sprintf(szMsg, "O dia %c: is a o dia cung", *szDrive2);
	    ErrExit(szMsg);
	  }

    if (drv1.lDataSize > drv2.lDiskSpace)
	  {
	    sprintf (szMsg, "O dia nguon %c: co du lieu nhieu hon dung luong cua o dich %c",
			   *szDrive1, *szDrive2);
	    ErrExit(szMsg);
	  }
  }

  if (bPrompt)
  {
    printf ("\rKHUYEN CAO: Tat ca du lieu tren o %c se bi xoa. Ban co muon tien hanh khong? (Y/N) ", *szDrive2);
    if (toupper (getche()) != 'Y')
	    exit(1);
  }

  volcopy (szDrive1[0] - '@', szDrive2 [0] - '@');

  printf ("\rXoa tat ca cac file va thu muc tren o %c:");
  printf ("                                     \r", *szDrive2);
  strcat (szDrive2, "\\");
  chdir (szDrive2);
  strcat (szDrive2, "*.*");
  DelAll(szDrive2, _A_NORMAL | _A_RDONLY | _A_HIDDEN | _A_SYSTEM);

  nBufSize = _memmax();
  pSource = malloc (nBufSize);

  if (pSource == NULL)
  {
    ErrExit ("Insufficient memory available");
  }

  nNumFiles = 0;
  szDrive1 [2] = '\0';
  szDrive2 [2] = '\0';
  printf ("Sao chep tap tin va thu muc tu o %c: den %c:\n%s\\\n", *szDrive1, *szDrive2, szDrive2);
  strcat (szDrive1, "\\*.*");
  strcat (szDrive2, "\\*.*");
  CopyAll(szDrive1, szDrive2, _A_NORMAL | _A_RDONLY | _A_HIDDEN | _A_SYSTEM);
  free(pSource);
  printf(" %d file(s) copied                            \n", nNumFiles);
}

void ErrExit (char *msg)
{
  fprintf(stderr, "\nLoi %d--%s%s", errno, _strerror(msg), szSyntaxMsg);
  exit(errno);
}


BOOL DelAll(PSTR szFileSpec,WORD wAttributes)
{
  BOOL     bContinue;
  WORD     wEntry, wDirEntries;
  struct find_t     DirEntry;
  char szPath[64], szSpec[64], szEntry[64], szCurFile [64], szCurDir [64];

  bContinue = TRUE;
  wDirEntries = 0;

  for (wEntry=strlen(szFileSpec)-1; szFileSpec[wEntry]!='\\'; wEntry-- );

  strcpy( szPath, szFileSpec );
  szPath[wEntry] = 0;
  strcpy( szCurFile, szFileSpec );
  szCurFile[wEntry + 1] = 0;

  strcpy( szSpec, &szFileSpec[wEntry+1] );

  if ( _dos_findfirst(szFileSpec,wAttributes,&DirEntry) == 0 )
  {
    do {
	    szCurFile[wEntry + 1] = 0;
	    strcat (szCurFile, DirEntry.name);
	    if (DirEntry.attrib != _A_NORMAL || DirEntry.attrib != _A_ARCH)
	      _dos_setfileattr (szCurFile, _A_NORMAL);
	    unlink (szCurFile);
	  } while ( _dos_findnext(&DirEntry) == 0 );
  }

  sprintf( szEntry, "%s\\*.*", szPath );
  if ( _dos_findfirst(szEntry,_A_SUBDIR | _A_NORMAL | _A_RDONLY | _A_HIDDEN | _A_SYSTEM, &DirEntry) == 0 )
  {
    do {
	    if ( (DirEntry.attrib & _A_SUBDIR) && (DirEntry.name[0]!='.') )
	    {
	      sprintf( szEntry, "%s\\%s\\%s", szPath, DirEntry.name, szSpec );
	      sprintf( szCurDir, "%s\\%s", szPath, DirEntry.name);
	      bContinue = DelAll( szEntry, wAttributes );
	      rmdir (szCurDir);
 	    }
	   } while ( (bContinue)&&(_dos_findnext(&DirEntry) == 0) );
  }

  return( bContinue );
}

BOOL CopyAll(PSTR szFileSpec1,PSTR szFileSpec2,WORD wAttributes)
{
  BOOL     bContinue;
  WORD     wEntry, wDirEntries;

  struct find_t  DirEntry;
  struct find_t near *pDirEntry;
  char near	  *pPos;
  int	hSource, hTarget;
  size_t nRead, nWrite, nNumRead, nNumWrite;
  long lTotRead, lTotWrite;
  int	n, nFiles;

  char szPath[64], szSpec[64], szEntry[64], szCurFile [68], szNewFile [68], szNewDir [64];


  bContinue = TRUE;
  wDirEntries = 0;

  for (wEntry=strlen(szFileSpec1)-1; szFileSpec1[wEntry]!='\\'; wEntry-- );

  strcpy( szPath, szFileSpec1 );
  szPath[wEntry] = 0;
  strcpy( szCurFile, szFileSpec1 );
  szCurFile[wEntry + 1] = 0;

  strcpy( szNewFile, szFileSpec1 );
  szNewFile[wEntry + 1] = 0;
  szNewFile[0] = szFileSpec2[0];

  strcpy( szSpec, &szFileSpec1[wEntry+1] );
  lTotRead = 0L;
  lTotWrite = 0;

  if ( _dos_findfirst(szFileSpec1,wAttributes,&DirEntry) == 0 )
  {
    do {
	    nFiles = 0;
	    pPos = pSource;
      while (pPos + (sizeof (DirEntry) * 2) < pSource + nBufSize)
	    {
	      memcpy (pPos, &DirEntry, sizeof (DirEntry) );
	      pDirEntry = pPos;
	      pPos += sizeof (DirEntry);

	      szCurFile[wEntry + 1] = '\0';
	      strcat (szCurFile, DirEntry.name);
	      if (lTotRead == 0L)
	      {
	        if (_dos_open (szCurFile, O_RDONLY, &hSource) != 0)
		      {
		        sprintf (szMsg, "Could not open file %s", szCurFile);
		        ErrExit(szMsg);
		      }
	      }

	      if(_dos_read(hSource, pPos, nBufSize - (pPos - pSource), &nNumRead) != 0)
	      {
	        sprintf (szMsg, "Error reading file %s", szCurFile);
	        ErrExit (szMsg);
	      }

	      pPos += nNumRead;
	      lTotRead += (long) nNumRead;
	      nFiles++;
	      printf(" %-12s %7ld bytes read   \r", pDirEntry->name, lTotRead);

	      if (lTotRead == DirEntry.size)
	      {
	        _dos_close (hSource);
	        lTotRead = 0L;
	        if (_dos_findnext(&DirEntry) != 0)
		      break;
	      }
	      else
	        break;
	    }

	    pDirEntry = pSource;
	    pPos = pSource + sizeof (DirEntry);
	    for (n = 0; n < nFiles; n++)
	    {
	      if (lTotWrite == 0)
	      {
	        szNewFile[wEntry + 1] = '\0';
	        strcat (szNewFile, pDirEntry->name);

	        if (_dos_creat (szNewFile, pDirEntry->attrib, &hTarget) != 0)
		      {
		        sprintf (szMsg, "Could not create file %s", szNewFile);
            ErrExit (szMsg);
		      }
	      }

	      if (pDirEntry->size > nBufSize - (pPos - pSource))
	        nWrite = nBufSize - (pPos - pSource);
	      else
	        nWrite = pDirEntry->size;

	      if ( (pDirEntry->size - lTotWrite) < nWrite)
	        nWrite = (unsigned int) (pDirEntry->size - lTotWrite);

	      if ( _dos_write (hTarget, pPos, nWrite, &nNumWrite) != 0 )
	      {
	        sprintf (szMsg, "Error writing file %s", szNewFile);
	        ErrExit (szMsg);
	      }
	      if (nNumWrite != nWrite)
	      {
	        sprintf (szMsg, "Error writing file %s", szNewFile);
	        ErrExit (szMsg);
	      }

	      lTotWrite += (long) nNumWrite;

	      pPos += (unsigned long) nWrite;

	      printf(" %-12s %7ld bytes written\r", pDirEntry->name, lTotWrite);

	      if (lTotWrite == pDirEntry->size)
	      {
	        lTotWrite = 0L;
	        _dos_setftime( hTarget, pDirEntry->wr_date, pDirEntry->wr_time);
	        _dos_close (hTarget);
	        nNumFiles++;
	      }

	      pDirEntry = pPos;
	      pPos += sizeof (DirEntry);
	    }

	  } while ( lTotRead != 0L || _dos_findnext(&DirEntry) == 0 );
  }

   sprintf( szEntry, "%s\\*.*", szPath );
   if ( _dos_findfirst(szEntry,_A_SUBDIR | _A_NORMAL | _A_RDONLY | _A_HIDDEN | _A_SYSTEM, &DirEntry) == 0 )
      {
      do {
	 if ( (DirEntry.attrib & _A_SUBDIR) && (DirEntry.name[0]!='.') )
	    {
	    sprintf( szEntry, "%s\\%s\\%s", szPath, DirEntry.name, szSpec );
	    sprintf( szNewDir, "%s\\%s", szPath, DirEntry.name);

	    szNewDir [0] = szFileSpec2 [0];
	    mkdir (szNewDir);
	    _dos_setfileattr(szNewDir, DirEntry.attrib);

	    printf("%s%s\n", szNewDir, "                                          ");
	    bContinue = CopyAll( szEntry,szFileSpec2, wAttributes );
	    }
	 } while ( (bContinue)&&(_dos_findnext(&DirEntry) == 0) );
  }

  return( bContinue );
}
