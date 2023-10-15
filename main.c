
#include <dirent.h>
#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
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
void classifyFiles(const char *targetDirectory) {
  DIR *dir;
  struct dirent *entry;

  dir = opendir(targetDirectory);

  regex_t video_regex, photo_regex, document_regex, installer_regex, zip_regex,
      pdf_regex;
  regcomp(&video_regex, ".*\\.(mp4|avi|mov)", REG_EXTENDED | REG_ICASE);
  regcomp(&photo_regex, ".*\\.(jpg|png|gif|jpeg)", REG_EXTENDED | REG_ICASE);
  regcomp(&document_regex, ".*\\.(docs|doc|txt)", REG_EXTENDED | REG_ICASE);
  regcomp(&pdf_regex, ".*\\.(pdf)", REG_EXTENDED | REG_ICASE);
  regcomp(&installer_regex, ".*\\.(deb|exe)", REG_EXTENDED | REG_ICASE);
  regcomp(&zip_regex, ".*\\.(zip|tar|gz)", REG_EXTENDED | REG_ICASE);

  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_type == DT_REG) { // Check if it's a regular file
      if (matchRegex(entry->d_name, &video_regex)) {
        moveFileToDirectory(entry->d_name, targetDirectory, "Videos");
      } else if (matchRegex(entry->d_name, &photo_regex)) {
        moveFileToDirectory(entry->d_name, targetDirectory, "Photos");
      } else if (matchRegex(entry->d_name, &document_regex)) {
        moveFileToDirectory(entry->d_name, targetDirectory, "Documents");
      } else if (matchRegex(entry->d_name, &installer_regex)) {
        moveFileToDirectory(entry->d_name, targetDirectory, "Installers");
      } else if (matchRegex(entry->d_name, &zip_regex)) {
        moveFileToDirectory(entry->d_name, targetDirectory, "Zips");
      } else if (matchRegex(entry->d_name, &pdf_regex)) {
        moveFileToDirectory(entry->d_name, targetDirectory, "Pdfs");
      } else {
        moveFileToDirectory(entry->d_name, targetDirectory, "Others");
      }
    }
  }
  regfree(&video_regex);
  regfree(&video_regex);
  regfree(&photo_regex);
  regfree(&document_regex);
  regfree(&installer_regex);
  regfree(&zip_regex);
  regfree(&pdf_regex);
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
                           "Installers", "Zips",   "Others"};
  for (int i = 0; i < 7; i++) {
    createDirectory(dirName[i], targetDirectory);
  }
  classifyFiles(targetDirectory);
  return EXIT_SUCCESS;
}
