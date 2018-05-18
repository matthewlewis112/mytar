#include "Project.h"

int headerName(char *inputfile, char *buffer, char *leftover)
{
  int c, sum = 0;

  memset(leftover, '\0', 155);

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
  for (; (c < 255); c++)
  {
    if (c < strlen(inputfile))
      leftover[c-100] = inputfile[c];
    sum += leftover[c-100];
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

int headerSize(struct stat ifile, char *buffer)
{
  int c, sum = 0, k = 1, temp = ifile.st_size;

  for (c = 0; c < (sizeof(off_t) -1); c++)
  {
    k *= 10;
  }
  for (c = 0; c < 12; c++)
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

int headerMTime(struct stat ifile, char *buffer)
{
  int c, sum = 0, k = 1,
    tempSec = ifile.st_mtim.tv_sec;

  for (c = 0; c < 12; c++)
  {
    if (tempSec/10 > k)
      k *= 10;
  }
  for (c = 0; c < 12; c++)
  {
    if (k > 0)
    {
      buffer[c] = tempSec / k;
      tempSec -= buffer[c] * k;
      buffer[c] += 48;
      k /= 10;
    }
    else
      buffer[c] = '\0';
    sum += buffer[c];
  }

  return sum;
}

int headerChkSum(int chksum, char *buffer)
{
  int c, sum = 0, k = 1;

  memset(buffer, ' ', 8);

  for (c = 0; c < 8; c++)
  {
    if (chksum/10 > k)
      k *= 10;
  }
  for (c = 0; c < 8; c++)
  {
    if (k > 0)
    {
      buffer[c] = chksum / k;
      chksum -= buffer[c] * k;
      buffer[c] += 48;
      k /= 10;
    }
    sum += buffer[c];
  }

  return sum;
}

int headerTypeFlag(struct stat ifile, char *buffer)
{
  if (S_ISDIR(ifile.st_mode))
  {
    *buffer = '5';
  }
  else if (S_ISLNK(ifile.st_mode))
  {
    *buffer = '2';
  }
  else
  {
    *buffer = '\0';
  }
  return *buffer;
}

int headerLinkName(struct stat ifile, char *pathname, char *buffer)
{
  int c, sum = 0;

  memset(buffer, '\0', sizeof(char)*100);

  if (S_ISLNK(ifile.st_mode))
  {
    if (-1 != (readlink(pathname, buffer, 100)))
    {
      perror("Cannot read symbolic link");
      exit(-1);
    }
  }
  for (c = 0; c < 100; c++)
  {
    sum += buffer[c];
  }
  return sum;
}

int headerUname(struct stat ifile, char *buffer)
{
  int c, sum = 0;
  struct passwd *user;

  if (0 == (user = getpwuid(ifile.st_uid)))
  {
    perror("Cannot get user name");
    exit(-1);
  }

  for (c = 0; c < 32; c++)
  {
    buffer[c] = user -> pw_name[c];
    sum += buffer[c];
  }

  return sum;
}

int headerGname(struct stat ifile, char *buffer)
{
  int c, sum = 0;
  struct group *group;

  if (0 == (group = getgrgid(ifile.st_gid)))
  {
    perror("Cannot get group name");
    exit(-1);
  }

  for (c = 0; c < 32; c++)
  {
    buffer[c] = group -> gr_name[c];
    sum += buffer[c];
  }

  return sum;
}

int headerDevmajor(struct stat ifile, char *buffer)
{
  int c, sum = 0, temp = major(ifile.st_dev), k = 1;

  for (c = 0; c < 8; c++)
  {
    if (temp/10 > k)
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

int headerDevminor(struct stat ifile, char *buffer)
{
  int c, sum = 0, temp = minor(ifile.st_dev), k = 1;

  for (c = 0; c < 8; c++)
  {
    if (temp/10 > k)
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

void printTable(int tarfile)
{
  char header[512];
  int i, size;

  while (read(tarfile, header, 512) > -1)
  {
    if (-1 == write(1, header, 100))
    {
      perror("Cannot write file name");
    }
    putchar('\n');
    if (header[156] == '\0')
    {
      for (i = 124; i < 136; i++)
      {
        if (header[i] != '\0')
          size = size * 10 + (header[i] - 48);
      }
      lseek(tarfile, size, SEEK_CUR);
    }
  }
}

void unpack(int tarfile)
{
  char header[512], name[100];
  char *temp;
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  int i, size, fileDes,
    argsO;

  while (read(tarfile, header, 512) > 0)
  {
    for (i = 0; i < 100; i++)
    {
      name[i] = header[i];
    }
    if (header[156] == '\0')
    {
      argsO = O_WRONLY | O_TRUNC | O_CREAT;
      if (-1 == (fileDes = open(name, argsO, mode)))
      {
        printf("%s\n", name);
        perror("Cannot write new file");
        exit(-1);
      }
      size = 0;
      for (i = 124; i < 136; i++)
      {
        if (header[i] != '\0')
          size = size * 10 + (header[i] - 48);
      }
      temp = malloc(sizeof(char) * size);
      if (-1 == read(tarfile, temp, size))
      {
        printf("%i\n", size);
        perror("Cannot read tarfile");
        exit(-1);
      }
      if (-1 == write(fileDes, temp, size))
      {
        perror("Cannot write file");
        exit(-1);
      }
      free(temp);
      if (-1 == (close(fileDes)))
      {
        perror("Cannot close file");
        exit(-1);
      }
    }
  }
}
