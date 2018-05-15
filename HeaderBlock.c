#include "Project.h"

int headerName(char *inputfile, char *buffer)
{
  int c, sum = 0;

  for (c = 0; c < 100; c++)
  {
    if (c < strlen(inputfile))
    {
      buffer[c] = inputfile[c];
      sum += inputfile[c];
    }
    else
    {
      buffer[c] = '\0';
      sum += '\0';
    }
  }
  return sum;
}

void writeToTarfile(char *inputfile, int tarfile)
{
  int size, fileDes;
  char buffer[100];

  if (-1 == (fileDes = open(inputfile, O_RDONLY)))
  {
    perror("Cannot open file");
    exit(-1);
  }

  while((size = read(fileDes, buffer, 100)) > 0)
  {
    if (-1 == write(tarfile, buffer, size))
    {
      perror("writeToTarfile: Cannot write to tarfile");
      exit(-1);
    }
  }
  if (size == -1)
  {
    perror("Cannot read file in write to tarfile");
    exit(-1);
  }
  if (-1 == close(fileDes))
  {
    perror("Cannot close file");
    exit(-1);
  }
}
