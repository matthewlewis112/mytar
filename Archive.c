#include "Project.h"

void addDirToArchive(int tarfile, char *dirname)
{
  return;
}

void addFileToArchive(int tarfile, char *inputfile)
{
  struct stat ifile;

  if (-1 == stat(inputfile, &ifile))
  {
    perror("Cannot open file");
    exit(-1);
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

void createArchive(bool isVerbsoe, bool isStrict, char *argv[], int argc)
{
  int i, tarfile;

  if (-1 == (tarfile = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT)))
  {
    perror("Cannot open file");
    exit(-1);
  }

  for (i = 3; i < argc; i++)
  {
    addFileToArchive(tarfile, argv[i]);
  }

  if (-1 == close(tarfile))
  {
    perror("Cannot close file");
    exit(-1);
  }
}

void listArchiveTable(bool isVerbsoe, bool isStrict, char *argv[], int argc)
{
  /*
  char *tarfilename = argv[2];
  int i, tarfile;

  if (-1 == (tarfile = open(argv[i], O_RDONLY)))
  {
    perror("Cannot open file");
    exit(-1);
  }

  if (-1 == close(tarfile))
  {
    perror("Cannot close file");
    exit(-1);
  }*/
  return;
}
