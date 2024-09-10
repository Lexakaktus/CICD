#include "s21_grep.h"

int main(int argc, char *argv[]) {
  int i = 0;
  Flags flags = CRF(argc, argv, &i);

  if (*flags.pattern == 0) {
    // printf("tet");
    strcpy(flags.pattern, argv[optind]);
    optind++;
  }

  regex_t regex = {0};
  int vyr;
  // printf(flags.pattern);
  if (flags.i) {
    vyr = regcomp(&regex, flags.pattern, REG_ICASE);
  } else {
    vyr = regcomp(&regex, flags.pattern, REG_EXTENDED);
  }

  if ((vyr == 0)) {
    for (int i = optind; i < argc; i++) {
      openfile(i, flags, &regex, argc, argv, vyr);
      // } printf("\n");
    }

  } else {
    if (!flags.s) {
      // printf("%d", vyr);
      fprintf(stderr, "can't compile regex");
    }
  }
  regfree(&regex);
  return 0;
}

Flags CRF(int argc, char *argv[], int *i) {
  struct option longOptions[] = {{"regexp", 1, NULL, 'e'},
                                 {"file", 1, NULL, 'f'},
                                 {"ignore-case", 0, NULL, 'i'},
                                 {"no-message", 0, NULL, 's'},
                                 {"invert-match", 0, NULL, 'v'},
                                 {"line-number", 0, NULL, 'n'},
                                 {"no-filename", 0, NULL, 'h'},
                                 {"only-matching", 0, NULL, 'o'},
                                 {"files-with-matches", 0, NULL, 'l'},
                                 {"count", 0, NULL, 'c'},
                                 {"help", 0, NULL, '0'},
                                 {NULL, 0, NULL, 0}};

  int currentFlag = getopt_long(argc, argv, "e:f:isvnholc", longOptions, NULL);
  Flags flags = {0};

  for (; currentFlag != -1;
       currentFlag =
           getopt_long(argc, argv, "e:f:isvnholc", longOptions, NULL)) {
    switch (currentFlag) {  //!!!

      case 'e':
        flags.e = true;
        if (*i > 0) strcat(flags.pattern, "|");
        strcat(flags.pattern, optarg);
        *i = *i + 1;
        break;
      case 'f':
        flags.f = true;
        flags = flagF(i, flags);
        break;
      case 'i':
        flags.i = true;
        break;
      case 's':
        flags.s = true;
        break;
      case 'v':
        flags.v = true;
        break;
      case 'n':
        flags.n = true;
        break;
      case 'h':
        flags.h = true;
        break;
      case 'o':
        flags.o = true;
        break;
      case 'l':
        flags.l = true;
        break;
      case 'c':
        flags.c = true;
        break;
    }
  }
  return flags;
}

Flags flagF(int *i, Flags flags) {
  char buffer[9000];
  FILE *fp2;
  if ((fp2 = (fopen(optarg, "r")))) {
    while (fgets(buffer, 9000 - 1, fp2) != NULL) {
      if (buffer[strlen(buffer) - 1] == '\n') buffer[strlen(buffer) - 1] = '\0';
      if (*i > 0) strcat(flags.pattern, "|");
      strcat(flags.pattern, buffer);
      // printf(flags.pattern);
      *i = *i + 1;
    }
    fclose(fp2);
  } else if (!flags.s) {
    fprintf(stderr, "s21_grep: %s: No such file or directory\n", optarg);
  }

  return flags;
}
void sravnenie(Flags flags, int argc, char **argv, int *nm, FILE *fp1,
               regex_t *regex, int vyr, int i) {
  char line[10000];

  int numbline = 0;
  while (fgets(line, sizeof(line), fp1)) {
    if (flags.v) {
      vyr = !(regexec(regex, line, 0, NULL, 0));
    } else {
      vyr = regexec(regex, line, 0, NULL, 0);
    }
    if (!vyr) {
      *nm = *nm + 1;
    }
    numbline++;
    prnclh(vyr, flags, argc, argv, numbline, line, i);
  }
}
void prnclh(int vyr, Flags flags, int argc, char **argv, int numbline,
            char *line, int i) {
  if ((!vyr) && (!flags.l)) {
    if (((argc - optind) >= 2) && !flags.h && (!flags.c)) {
      printf("%s", argv[i]);
      printf(":");
    }
  }

  if ((!vyr) && (!flags.c) && (!flags.l)) {
    flags.n ? printf("%d:%s", numbline, line) : printf("%s", line);
    if (line[strlen(line) - 1] != '\n') {
      printf("\n");
    }
  }
}
void openfile(int i, Flags flags, regex_t *regex, int argc, char **argv,
              int vyr) {
  FILE *fp1 = fopen(argv[i], "r");
  // printf("\n%s", argv[i]);
  // printf("%d", argc);
  if ((fp1)) {
    int nm = 0;

    sravnenie(flags, argc, argv, &nm, fp1, regex, vyr, i);

    if (flags.c) {
      if (flags.l && nm > 1) nm = 1;

      ((argc - optind) < 2 || flags.h) ? printf("%d\n", nm)
                                       : printf("%s:%d\n", argv[i], nm);
    }
    if ((nm >= 1) && (flags.l)) {
      printf("%s\n", argv[i]);
      // printf("\n");
    }
    if (nm > 0 && !flags.c) {
      // printf("\n");
    }
    fclose(fp1);
  } else {
    if (!flags.s) {
      fprintf(stderr, "s21_grep: %s: No such file or directory", argv[optind]);
    }
  }
}
