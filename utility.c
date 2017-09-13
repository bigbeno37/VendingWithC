#include "utility.h"

/**
 * Function required to be used when clearing the buffer. It simply reads
 * each char from the buffer until the buffer is empty again. Please refer
 * to the materials on string and buffer handling in the course for more
 * information.
 **/
void readRestOfLine()
{
    int ch;
    while(ch = getc(stdin), ch != EOF && ch != '\n')
    { } /* Gobble each character. */

    /* Reset the error status of the stream. */
    clearerr(stdin);
}

char *copyString(char *string) {
    int i;
    char *toBeCopied = malloc(strlen(string)+1);

    for(i = 0; i < strlen(string)+1; i++) {
        toBeCopied[i] = string[i];
    }

    return toBeCopied;
}

Boolean fileExists(char *path) {
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        return FALSE;
    }

    return TRUE;
}