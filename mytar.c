#include "Project.h"

int main (int argc, char *argv[])
{
  if (argc > 1 && lookForChar(argv[1], 'f'))
  {
    if (lookForChar(argv[1], 'c'))
    {
      createArchive(isVerbose(argv[1]), isStrict(argv[1]), argv, argc);
    }
    if (lookForChar(argv[1], 't'))
    {
      listArchiveTable(isVerbose(argv[1]), isStrict(argv[1]), argv, argc);
    }
  }

  return 0;
}
