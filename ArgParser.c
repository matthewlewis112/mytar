#include "Project.h"

int isVerbose(char *argv)
{
  return lookForChar(argv, 'v');
}

int isStrict(char *argv)
{
  return lookForChar(argv, 'S');
}

int lookForChar(char *argv, char l)
{
  int c, i = strlen(argv);

  for (c = 0; c < i; c++)
  {
    if (argv[c] == l)
      return TRUE;
  }
  return FALSE;
}
