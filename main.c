#include <dirent.h> 
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <ftw.h>
#include "lib/linked_list.h"

#define GREEN_COLOR "\x1B[32m"
#define WHITE_COLOR "\x1B[37m"

/* global variable for nftw() */
static char* text;

/**
 * @brief Get the arguments object
 * 
 * @param argc Number of passed arguments
 * @param argv Pointer array to each argument passed to the program
 * @param f Path argument
 * @param t Text argument
 */
void get_arguments(int argc, char **argv, char **f, char **t) {
    int c;
    while ((c = getopt(argc, argv, "f:t:")) != -1) {
        switch (c) {
        case 'f':
            *f = optarg;
            break;
        case 't':
            *t = optarg;
            break;
        default:
            fprintf(stderr, "Usage:  programa -f <directory> -f <text_to_find>\n");
            exit(EXIT_FAILURE);
        }
    }
}

/**
 * @brief Check for text in the file provided by arguments
 * 
 * @param path File path
 * @param t Text to check for 
 */
void check_for_text(const char *path, char *t){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(path, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int line_nr = 1; 
    int found = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        if(strstr(line, t) != NULL) {
          if (found == 0) {
            printf("\n%sFile: %s\n", GREEN_COLOR, path);
            found = 1;
          }
          printf("%sLine: %d\n", WHITE_COLOR, line_nr);
        }
        line_nr++;
    }

    fclose(fp);
    if (line)
      free(line);
}

/**
 * @brief Function for nftw() which is executed on every file in the tree
 * 
 * @param fpath File path
 * @param sb Pointer to the stat structure
 * @param tflag Flags for file type
 * @param ftwbuf Pointer to the FTW structure
 * @return int Return 0 to continue nftw()
 */
int check_file(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf)
{
    if(tflag == FTW_F) {
      check_for_text(fpath, text);
    }
    return 0;
}

int main(int argc, char **argv) {
    // get arguments
    char *f = NULL;
    char *t = NULL;

    // get command line arguments
    get_arguments(argc, argv, &f, &t);

    if (f == NULL || t == NULL) {
      fprintf(stderr, "Usage:  programa -f <directory> -f <text_to_find>\n");
      exit(EXIT_FAILURE);
    }
    
    text = t;

    printf("\n%sFolder: %s%s\n", WHITE_COLOR, GREEN_COLOR, f);
    printf("%sText: %s%s\n", WHITE_COLOR, GREEN_COLOR, t);

    int flags = 0;
    if (nftw(f, check_file, 20, flags) == -1) {
        fprintf(stderr, "nftw() failed!\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}