#ifndef S21_grep_H
#define S21_grep_H
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  bool e;  //
  bool f;  //
  bool i;  //
  bool l;  //
  bool n;  //
  bool s;  //
  bool v;  //
  bool c;
  bool o;  //
  bool h;  //
  char pattern[10000];

} Flags;
Flags CRF(int argc, char *argv[], int *i);
Flags flagF(int *i, Flags flags);
void sravnenie(Flags flags, int argc, char **argv, int *nm, FILE *fp1,
               regex_t *regex, int vyr, int i);
void openfile(int i, Flags flags, regex_t *regex, int argc, char **argv,
              int vyr);
void prnclh(int vyr, Flags flags, int argc, char **argv, int numbline,
            char *line, int i);

#endif
