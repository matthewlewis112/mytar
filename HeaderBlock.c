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

int headerMode(struct stat ifile, char *buffer)
{
  int c, sum = 0;

  strcpy(buffer, "00000");
  buffer[5] = buffer[6] = buffer[7] = '\0';

  if (S_ISUID & ifile.st_mode)
  {
    buffer[1] = '4';
  }
  else if (S_ISGID & ifile.st_mode)
  {
    buffer[1] = '2';
  }
  else if (S_ISVTX & ifile.st_mode)
  {
    buffer[1] = '1';
  }

  if (S_IRUSR & ifile.st_mode)
  {
    buffer[2] = '4';
  }
  else if (S_IWUSR & ifile.st_mode)
  {
    buffer[2] = '2';
  }
  else if (S_IXUSR & ifile.st_mode)
  {
    buffer[2] = '1';
  }

  if (S_IRGRP & ifile.st_mode)
  {
    buffer[3] = '4';
  }
  else if (S_IWGRP & ifile.st_mode)
  {
    buffer[3] = '2';
  }
  else if (S_IXGRP & ifile.st_mode)
  {
    buffer[3] = '1';
  }

  if (S_IROTH & ifile.st_mode)
  {
    buffer[4] = '4';
  }
  else if (S_IWOTH & ifile.st_mode)
  {
    buffer[4] = '2';
  }
  else if (S_IXOTH & ifile.st_mode)
  {
    buffer[4] = '1';
  }

  for (c = 0; c < 8; c++)
  {
    sum += buffer[c];
  }

  return sum;
}

int headerUID(struct stat ifile, char *buffer)
{
  int c, sum = 0, k = 1, temp = ifile.st_uid;

  for (c = 0; c < (sizeof(uid_t) -1); c++)
  {
    k *= 10;
  }
  for (c = 0; c < 8; c++)
  {
    if (k > 0)
    {
      buffer[c] = temp / k;
      temp -= buffer[c] * k;
      buffer[c] += 48;
      k /= 10;
    }
    else
      buffer[c] = '\0';
    sum += buffer[c];
  }

  return sum;
}

int headerGID(struct stat ifile, char *buffer)
{
  int c, sum = 0, k = 1, temp = ifile.st_gid;

  for (c = 0; c < (sizeof(gid_t) -1); c++)
  {
    k *= 10;
  }
  for (c = 0; c < 8; c++)
  {
    if (k > 0)
    {
      buffer[c] = temp / k;
      temp -= buffer[c] * k;
      buffer[c] += 48;
      k /= 10;
    }
    else
      buffer[c] = '\0';
    sum += buffer[c];
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
