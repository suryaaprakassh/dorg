#include "parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int getConfigLength() {
  char *homeDir = getenv("HOME");
  char configPath[256];
  snprintf(configPath, 256, "%s/.dorg.conf", homeDir);

  FILE *config = fopen(configPath, "r");

  if (config == NULL) {
    fprintf(stderr, "Error: Config File Not found");
    // TODO: make a default config file
    exit(1);
  }
  char line[256];
  int noOfLines = 0;
  while (fgets(line, sizeof(line), config) != NULL) {
    noOfLines += 1;
  }
  return noOfLines;
}

void readConfig(char *dirNames[], char *regexPatterns[]) {
  char *homeDir = getenv("HOME");
  char configPath[256];
  snprintf(configPath, 256, "%s/.dorg.conf", homeDir);
  FILE *config = fopen(configPath, "r");
  char ch;
  char line[256];
  char pattern[256];
  int currentLine = 0;
  while (fgets(line, sizeof(line), config) != NULL) {
    char *delimiter = strtok(line, "=");

    if (delimiter == NULL) {
      fprintf(stderr, "Ivalid Syntax in Config file");
      exit(1);
    }
    dirNames[currentLine] = strndup(delimiter, strlen(delimiter));
    delimiter = strtok(NULL, "=");
    char *ch = delimiter;
    while (ch && *ch != '\0') {
      if (*ch == ' ' || *ch == '\n') {
        *ch = '\0';
        break;
      }
      ch++;
    }
    if (delimiter[0] == '(' && delimiter[strlen(delimiter) - 1] == ')') {
      snprintf(pattern, 256, ".*\\.%s", delimiter);
    } else {
      int curr = 0;
      ch = delimiter;
      for (; *ch != '\0'; ch++) {
        if (*ch == '/') {
          continue;
        }
        delimiter[curr++] = (*ch);
      }
      delimiter[curr] = '\0';
      snprintf(pattern, 256, "%s", delimiter);
    }
    regexPatterns[currentLine] = strndup(pattern, strlen(pattern));
    currentLine++;
  }
}
