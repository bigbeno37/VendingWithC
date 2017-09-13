#include "vm.h"
#include "tests/Tests.h"

int main(int argc, char ** argv)
{
    Boolean debug = TRUE;
    MenuItem menu[NUMBER_OF_MENU_ITEMS];
    VmSystem *system = malloc(sizeof(VmSystem));
    int i;

    if (debug) {
        run_tests();
    }

    if (argv[1] == NULL) {
        puts("Error! Stock file must be specified!");

        exit(1);
    } else if(!fileExists(argv[1])) {
        puts("Error! Stock file not found!");
        exit(1);
    }

    initMenu(menu);
    systemInit(system);
    loadData(system, argv[1], "coins.dat");

    for (i = 0; i < NUMBER_OF_MENU_ITEMS; i++) {

        if (i == 0) {
            puts("Main Menu:");
        } else if (i == 3) {
            puts("Administrator-Only Menu:");
        }

        printf("%i. %s\n", i+1, menu[i].text);
    }

    while (TRUE) {
        printf("Select your option (1-9): ");
        getMenuChoice(menu)(system);
    }

    return EXIT_SUCCESS;
}
