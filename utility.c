#include "utility.h"
#include "vm_system.h"

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

/*
 * Determines if a file exists given a specific path
 */
Boolean fileExists(const char *path) {
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        return FALSE;
    }

    fclose(file);

    return TRUE;
}

/*
 * Prints N amounts of the character passed in
 */
void printNCharacters(int n, char *string) {
    int i;

    for (i = 0; i < n; i++) {
        printf("%s", string);
    }
}

/*
 * Utilising the method above, print N amounts of dashes
 */
void printNDashes(int n) {
    printNCharacters(n, "-");
}

/*
 * Get the amount of digits of a number 'n'
 */
int getDigits(int n) {
    if (n < 10) {
        return 1;
    } else if (n < 100) {
        return 2;
    } else if (n < 1000) {
        return 3;
    } else if (n < 10000) {
        return 4;
    }

    return 0;
}

/*
 * Return the user input to 'bufferSize' characters
 */
void getUserInput( char *buffer, int charsToRead ) {
    strcpy(buffer, "");

    while (TRUE) {
        /* Get the input and store it in name */
        fgets(buffer, charsToRead+EXTRA_SPACES, stdin);

        /* If name doesn't have a newline character (and thus the input was bigger than 20) */
        /* remove overflowed characters and ask for new input */
        if (!strchr( buffer, '\n' )) {
            printf( "Buffer overflow! Please enter fewer characters: " );
            readRestOfLine();

            continue;
        }

        break;
    }

    buffer[strlen(buffer) - 1] = '\0';
}

/*
 * Converts a string to an int using strtol
 */
int toInt(char *string) {
    return (int) strtol(string, NULL, 10);
}

/*
 * Converts an int to string
 */
void iToString(char *buffer, int num, int digits) {
    sprintf(buffer, "%0*d", digits, num);
}

/*
 * Converts an ID into an int representation of that ID
 */
int getValueOfID(char *id) {
    char newID[ID_LEN];
    strcpy(newID, id);

    newID[0] = '0';

    return toInt(newID);
}