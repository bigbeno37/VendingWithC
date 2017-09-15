#include "TestUtils.h"
#include "Tests.h"
#include "../utility.h"

/*
 * Determine if copyString correctly copies the string passed in
 */
void copyStringCorrectlyCopiesString() {
    char *message = "Hello world!";
    char *newMessage = copyString(message);

    sAssertThat("The copied string should be equal to Hello World", "Hello world!", newMessage);
}

/*
 * Determine if iToString will correctly return a string with
 * the number passed in
 */
void iToStringCorrectlyReturnsNumber() {
    sAssertThat("3 should return '3'", "3", iToString(3, 1));
    sAssertThat("12 should return '12'", "12", iToString(12, 2));
}

/*
 * Determine if getValueOfID will correctly translate an ID
 * of format IXXXX where X is a number into an int
 */
void getValueOfIDCorrectlyReturnsValue() {
    iAssertThat("I0001 will return a value of 1", 1, getValueOfID("I0001"));
    iAssertThat("I9999 will return a value of 9999", 9999, getValueOfID("I9999"));
}