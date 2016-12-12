#include "puremd5.h"

void usage(void)
{
  fprintf(stderr, "puremd5_test \"STRING\" - prints md5 of STRING to the stdout\n");
  exit(1);
}

int main(int argc, char**argv)
{
  if(argc <= 1 )
    usage();

  struct md5_sg s[] = {
    { .buf = argv[1], .len = strlen(argv[1]) },
    {0,0}
  };

  md5_digest d;

  md5(s,d);
  md5_fprint(stdout, d);

  printf("\n");
  return 0;
}
