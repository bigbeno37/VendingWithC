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

void printNCharacters(int n, char *string) {
    int i;

    for (i = 0; i < n; i++) {
        printf("%s", string);
    }
}

void printNSpaces(int n) {
    printNCharacters(n, " ");
}

void printNDashes(int n) {
    printNCharacters(n, "-");
}

int getDigits(int n) {
    if (n < 10) {
        return 1;
    }

    return 2;
}

char *getUserInput(int bufferSize) {
    Boolean correctInput = FALSE;
    char *buffer = malloc((size_t) bufferSize+EXTRA_SPACES);

    while ( !correctInput ) {
        correctInput = TRUE;

        /* Get the input and store it in name */
        fgets( buffer, bufferSize+EXTRA_SPACES, stdin );

        /* If name doesn't have a newline character (and thus the input was bigger than 20) */
        /* remove overflowed characters and ask for new input */
        if ( !strchr( buffer, '\n' )) {
            printf( "\nBuffer overflow! Please enter a valid choice: " );
            readRestOfLine();

            correctInput = FALSE;
        }
    }

    buffer[strlen(buffer)-1] = '\0';

    return copyString(buffer);
}