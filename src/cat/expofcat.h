#ifndef EXPOFKAT_H
#define EXPOFKAT_H

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
typedef struct {  //разобраться с типдеф и 24строкой
  bool b;
  bool Endl;
  bool n;
  bool squeeze;
  bool tab;
  bool printnonprintable;
} Flags;
Flags CRF(int argc, char *argv[]);
void printnonprintable(int *symbol);
void squeeze(FILE *stream);
void openfile(int optind, int argc, char **argv, Flags flags);
void readstream(FILE *fp1, Flags flags);
#endif
