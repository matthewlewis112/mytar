#include "Project.h"

void addDirToArchive(int tarfile, char *dirname, bool isV)
{
  DIR *dir;
  struct dirent *file;

  if (NULL != (dir = opendir(dirname)))
  {
    chdir(dirname);
    while ((file = readdir(dir)) != NULL)
    {
      if ((strcmp(file -> d_name, "..") != 0)&&
        (strcmp(file -> d_name, ".") != 0))
      addFileToArchive(tarfile, file -> d_name, isV);
    }
    closedir(dir);
    chdir("..");
  }
  else
  {
    perror("Could not store dir");
    exit(-1);
  }
}

void addFileToArchive(int tarfile, char *inputfile, bool isV)
{
  struct stat ifile;
  char nameBuffer[100], modeBuffer[8],
    UIDBuffer[8], GIDBuffer[8], sizeBuffer[12],
    mtimeBuffer[12], flagBuffer[1], linkName[100],
    magicBuffer[6] = "ustar", versionBuffer[2],
    unameBuffer[32], gnameBuffer[32], majorBuffer[8],
    minorBuffer[8], prefixBuffer[155], chksumBuffer[8],
    headerBuffer[512];
  int sum = 0, c, j;

  versionBuffer[0] = '0';
  versionBuffer[1] = '0';

  if (-1 == stat(inputfile, &ifile))
  {
    perror("Cannot open file");
    exit(-1);
  }

  sum += headerName(inputfile, nameBuffer, prefixBuffer);
  sum += headerMode(ifile, modeBuffer);
  sum += headerUID(ifile, UIDBuffer);
  sum += headerGID(ifile, GIDBuffer);
  sum += headerSize(ifile, sizeBuffer);
  sum += headerMTime(ifile, mtimeBuffer);
  sum += headerTypeFlag(ifile, flagBuffer);
  sum += headerLinkName(ifile, inputfile, linkName);
  sum += headerUname(ifile, unameBuffer);
  sum += headerGname(ifile, gnameBuffer);
  sum += headerDevmajor(ifile, majorBuffer);
  sum += headerDevminor(ifile, minorBuffer);
  sum += headerChkSum(sum, chksumBuffer);

  for (c = 0, j = 0; c < 512; c++, j++)
  {
    if (c < 100)
      headerBuffer[c] = nameBuffer[c];
    else if (c < 108)
    {
      if (c == 100)
        j = 0;
      headerBuffer[c] = modeBuffer[j];
    }
    else if (c < 116)
    {
      if (c == 108)
        j = 0;
      headerBuffer[c] = UIDBuffer[j];
    }
    else if (c < 124)
    {
      if (c == 116)
        j = 0;
      headerBuffer[c] = GIDBuffer[j];
    }
    else if (c < 136)
    {
      if (c == 124)
        j = 0;
      headerBuffer[c] = sizeBuffer[j];
    }
    else if (c < 148)
    {
      if (c == 136)
        j = 0;
      headerBuffer[c] = mtimeBuffer[j];
    }
    else if (c < 156)
    {
      if (c == 148)
        j = 0;
      headerBuffer[c] = chksumBuffer[j];
    }
    else if (c < 157)
    {
      if (c == 156)
        j = 0;
      headerBuffer[c] = flagBuffer[j];
    }
    else if (c < 257)
    {
      if (c == 157)
        j = 0;
      headerBuffer[c] = linkName[j];
    }
    else if (c < 263)
    {
      if (c == 257)
        j = 0;
      headerBuffer[c] = magicBuffer[j];
    }
    else if (c < 265)
    {
      if (c == 263)
        j = 0;
      headerBuffer[c] = versionBuffer[j];
    }
    else if (c < 297)
    {
      if (c == 265)
        j = 0;
      headerBuffer[c] = unameBuffer[j];
    }
    else if (c < 329)
    {
      if (c == 297)
        j = 0;
      headerBuffer[c] = gnameBuffer[j];
    }
    else if (c < 337)
    {
      if (c == 337)
        j = 0;
      headerBuffer[c] = majorBuffer[j];
    }
    else if (c < 345)
    {
      if (c == 337)
        j = 0;
      headerBuffer[c] = minorBuffer[j];
    }
    else
    {
      if (c < 345)
        j = 0;
      headerBuffer[c] = prefixBuffer[j];
    }
    if (isV)
      printf("%s\n", inputfile);
  }

  if (-1 == write(tarfile, headerBuffer, 512))
  {
    perror("Cannot write buffer");
  }

  if (S_ISDIR(ifile.st_mode))
  {
    addDirToArchive(tarfile, inputfile);
  }
  else if (S_ISREG(ifile.st_mode))
  {
    writeToTarfile(inputfile, tarfile);
  }
}

void createArchive(bool isV, bool isStrict, char *argv[], int argc)
{
  int i, tarfile;

  if (-1 == (tarfile = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT)))
  {
    perror("Cannot open tarfile");
    exit(-1);
  }

  for (i = 3; i < argc; i++)
  {
    addFileToArchive(tarfile, argv[i], isV);
  }

  if (-1 == close(tarfile))
  {
    perror("Cannot close file");
    exit(-1);
  }
}

void listArchiveTable(bool isVerbsoe, bool isStrict, char *argv[], int argc)
{
  char *tarfilename = argv[2];
  int tarfile;

  if (-1 == (tarfile = open(tarfilename, O_RDONLY)))
  {
    perror("Cannot open tarfile");
    exit(-1);
  }

  printTable(tarfile, isVerbose);

  if (-1 == close(tarfile))
  {
    perror("Cannot close tarfile");
    exit(-1);
  }
  return;
}

void unpackArchive(bool isVerbsoe, bool isStrict, char *argv[], int argc)
{
  char *tarfilename = argv[2];
  int tarfile;

  if (-1 == (tarfile = open(tarfilename, O_RDONLY)))
  {
    perror("Cannot open tarfile");
    exit(-1);
  }

  unpack(tarfile);

  if (-1 == close(tarfile))
  {
    perror("Cannot close tarfile");
    exit(-1);
  }
  return;
}
