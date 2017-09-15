#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>

typedef enum boolean
{
    FALSE = 0,
    TRUE
} Boolean;

#define NEW_LINE_SPACE 1
#define NULL_SPACE 1

#define CHOICE_SIZE (1 + EXTRA_SPACES)

/**
 * This is used to compensate for the extra character spaces taken up by
 * the '\n' and '\0' when input is read through fgets().
 **/
#define EXTRA_SPACES (NEW_LINE_SPACE + NULL_SPACE)

#define EMPTY_STRING ""

#define LEN(array)  (sizeof(array) / sizeof((array)[0]))

/**
 * Call this function whenever you detect buffer overflow.
 **/
void readRestOfLine();

Boolean fileExists(const char *file);
void printNSpaces(int n);
void printNDashes(int n);
int getDigits(int n);
void getUserInput(char *buffer, int bufferSize);
int toInt(char *string);
void iToString(char *buffer, int num, int digits);
int getValueOfID(char *id);

#endif
