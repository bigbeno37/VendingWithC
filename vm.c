#include "vm.h"
#include "tests/Tests.h"

int main(int argc, char ** argv)
{
    Boolean debug = TRUE;

    if (debug) {
        run_tests();
    }

    MenuItem menu[NUMBER_OF_MENU_ITEMS];
    initMenu(menu);

    for (int i = 0; i < NUMBER_OF_MENU_ITEMS; i++) {

        if (i == 0) {
            puts("Main Menu:");
        } else if (i == 3) {
            puts("Administrator-Only Menu:");
        }

        printf("%i. %s\n", i+1, menu[i].text);
    }

    printf("Select your option (1-9): ");

    return EXIT_SUCCESS;
}
