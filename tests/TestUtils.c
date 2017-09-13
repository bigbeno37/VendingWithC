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