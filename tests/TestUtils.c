/*
 * Created by bigbeno37 on 13/09/17.
 */

#include "TestUtils.h"
#include "Tests.h"
#include "../utility.h"

void copyStringCorrectlyCopiesString() {
    char *message = "Hello world!";
    char *newMessage = copyString(message);

    sAssertThat("The copied string should be equal to Hello World", "Hello world!", newMessage);
}