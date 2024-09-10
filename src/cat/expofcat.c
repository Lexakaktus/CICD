#include "expofcat.h"

int main(int argc, char *argv[]) {
  Flags flags = CRF(argc, argv);
  openfile(optind, argc, argv, flags);
  // printf("%d, %d", argc, optind);

  return 0;
}

Flags CRF(int argc, char *argv[]) {
  struct option longOptions[] = {{"number-nonblank", 0, NULL, 'b'},
                                 {"number", 0, NULL, 'n'},
                                 {"squeeze-blank", 0, NULL, 's'},
                                 {NULL, 0, NULL, 0}};

  int currentFlag = getopt_long(argc, argv, "+bevEnstT", longOptions, NULL);
  Flags flags = {false, false, false, false, false, false};
  for (; currentFlag != -1;
       currentFlag = getopt_long(argc, argv, "+bevEnstT", longOptions, NULL)) {
    switch (currentFlag) {  //!!!

      case 'b':
        flags.b = true;
        break;
      case 'e':
        flags.Endl = true;
        flags.printnonprintable = true;
        break;
      case 'v':
        flags.printnonprintable = true;
        break;
      case 'E':
        flags.Endl = true;
        break;
      case 'n':
        flags.n = true;
        break;
      case 's':
        flags.squeeze = true;
        break;
      case 't':
        flags.printnonprintable = true;
        flags.tab = true;
        break;
      case 'T':
        flags.tab = true;
        break;
    }
  }
  return flags;
}

void printnonprintable(int *symbol) {
  if (*symbol > 127 && *symbol < 160) printf("m-^");
  if (*symbol <= 31 && *symbol != '\t' && *symbol != '\n') {
    printf("^");
    *symbol += 64;
  }
  if (*symbol == 127) {
    printf("^");
    *symbol = '?';
  }
}
void squeeze(FILE *stream) {
  char c = fgetc(stream);
  while (c == '\n') {
    c = fgetc(stream);
  }
  ungetc(c, stream);
}

void openfile(int optind, int argc, char **argv, Flags flags) {
  for (int i = optind; i <= argc; i++) {
    FILE *fp1;
    if (((optind == argc) && (i == optind)) || (strcmp(argv[i], "-") == 0)) {
      fp1 = stdin;
    } else {
      fp1 = fopen(argv[i], "r");
    }
    if ((fp1) == NULL) {
      fprintf(stderr, "s21_cat: %s: No such file or directory\n", argv[optind]);

    } else {
      readstream(fp1, flags);
    }
    if (i == argc - 1) i += 2;
    fclose(fp1);
  }
}
void readstream(FILE *fp1, Flags flags) {
  int nl = 1;
  int pc = '\n';
  int c;

  while ((c = fgetc(fp1)) != EOF) {
    if ((flags.b) && (pc == '\n')) {
      if (c != '\n') {
        printf("%6d\t", nl);
        nl = nl + 1;
      }
    } else if (flags.n && pc == '\n') {
      printf("%6d\t", nl);
      nl = nl + 1;
    }
    if (flags.Endl && c == '\n') {
      if (flags.b && pc == '\n')
        printf("%6c\t$", ' ');
      else
        printf("$");
    }
    if (flags.squeeze && pc == '\n') {
      squeeze(fp1);
    }
    if (flags.tab) {
      if (c == '\t') {
        printf("^");
        c = 'I';
      }
    }
    if (flags.printnonprintable) {
      printnonprintable(&c);
    }
    printf("%c", c);
    pc = c;
  }
}
