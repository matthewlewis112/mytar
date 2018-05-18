#include "Project.h"

int main (int argc, char *argv[])
{
  bool isValid = FALSE;
  if (argc > 1 && lookForChar(argv[1], 'f'))
  {
    if (lookForChar(argv[1], 'c'))
    {
      createArchive(isVerbose(argv[1]), isStrict(argv[1]), argv, argc);
      isValid = TRUE;
    }
    if (lookForChar(argv[1], 't'))
    {
      listArchiveTable(isVerbose(argv[1]), isStrict(argv[1]), argv, argc);
      isValid = TRUE;
    }
    if (lookForChar(argv[1], 'x'))
    {
      unpackArchive(isVerbose(argv[1]), isStrict(argv[1]), argv, argc);
      isValid = TRUE;
    }
  }

  if (!isValid)
  {
    perror("usage error: ");
    exit(-1);
  }

  return 0;
}
