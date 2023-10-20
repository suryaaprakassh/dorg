
#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct {
  char folder[256];
  regex_t pattern;
} FilePair;

int matchRegex(const char *string, regex_t *pattern) {
  return regexec(pattern, string, 0, NULL, 0) == 0;
}

void printHelp() {
  printf("Usage:\n\n");
  printf("Organize Current Directory:\t");
  printf("dorg\n\n");
  printf("Organize targetDirectory:\t");
  printf("dorg <targetDirectory>\n\n");
}

void moveFileToDirectory(const char *filename, const char *targetDirectory,
                         const char *dirName) {
  char targetPath[1024];
  char sourcePath[1024];
  snprintf(targetPath, sizeof(targetPath), "%s/%s", targetDirectory, filename);
  snprintf(sourcePath, sizeof(sourcePath), "%s/%s/%s", targetDirectory, dirName,
           filename);
  if (rename(targetPath, sourcePath) == 0) {
    printf("Moved file: %s to %s\n", filename, targetPath);
  } else {
    printf("From:%s\nTo:%s\n", targetPath, sourcePath);
    perror("Error moving file ");
  }
}
void classifyFiles(const char *targetDirectory, FilePair *filePatterns,
                   int len) {
  DIR *dir;
  struct dirent *entry;

  dir = opendir(targetDirectory);

  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_type == DT_REG) { // Check if it's a regular file
      int moved = 0;
      for (int i = 0; i < len; i++) {
        if (matchRegex(entry->d_name, &(filePatterns[i].pattern))) {
          moveFileToDirectory(entry->d_name, targetDirectory,
                              filePatterns[i].folder);
          moved = 1;
          break;
        }
      }
      if (!moved) {
        moveFileToDirectory(entry->d_name, targetDirectory, "Others");
      }
    }
  }
  closedir(dir);
}

void createDirectory(const char *dirName, const char *targetDirectory) {
  char dirBuffer[1024];
  snprintf(dirBuffer, sizeof(dirBuffer), "%s/%s", targetDirectory, dirName);
  if (mkdir(dirBuffer, 0700) == 0) {
    printf("directory created successfully!\n");
  } else {
    if (errno != EEXIST) {
      perror("Error Bro!");
    }
  }
}

void createFilePatterns(FilePair *pattern, const char *dirNames[],
                        const char *regexPatterns[], int len) {
  for (int i = 0; i < len; i++) {
    strcpy(pattern[i].folder, dirNames[i]);
    regcomp(&pattern[i].pattern, regexPatterns[i], REG_EXTENDED | REG_ICASE);
  }
}

void freePatterns(FilePair *pattern, int len) {
  for (int i = 0; i < len; i++) {
    regfree(&pattern[i].pattern);
  }
}

int main(int argc, char *argv[]) {
  const char *targetDirectory;

  if (argc < 2) {
    targetDirectory = ".";
  } else {
    targetDirectory = argv[1];
  }

  if (strcmp(targetDirectory, "-h") == 0) {
    printHelp();
    return EXIT_SUCCESS;
  };

  if (access(targetDirectory, F_OK) != 0) {
    fprintf(stderr, "Target directory does not exist.\n");
    return EXIT_FAILURE;
  }
  const char *dirName[] = {"Videos",     "Photos", "Documents", "Pdfs",
                           "Installers", "Zips",   "Music",     "Others"};
  const char *regexPatterns[] = {
      ".*\\.(mp4|avi|mov)", ".*\\.(jpg|png|gif|jpeg)", ".*\\.(docs|doc|txt)",
      ".*\\.(pdf)",         ".*\\.(deb|exe)",          ".*\\.(zip|tar|gz)",
      ".*\\.(mp3)"};

  int sizeOfPatterns = sizeof(regexPatterns) / sizeof(regexPatterns[0]);
  FilePair filePatterns[sizeOfPatterns];
  createFilePatterns(filePatterns, dirName, regexPatterns, sizeOfPatterns);
  // extra one for others
  for (int i = 0; i <= sizeOfPatterns; i++) {
    createDirectory(dirName[i], targetDirectory);
  }
  classifyFiles(targetDirectory, filePatterns, sizeOfPatterns);
  freePatterns(filePatterns, sizeOfPatterns);
  return EXIT_SUCCESS;
}
