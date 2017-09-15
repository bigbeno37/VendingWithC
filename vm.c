#include "vm.h"
#include "tests/Tests.h"

int main(int argc, char ** argv)
{
    /* Should unit tests be run? */
    Boolean runTests = TRUE;
    /* The Menu array, holding currently available options */
    MenuItem menu[NUMBER_OF_MENU_ITEMS];
    /* The system holding the items linked list, coins, and
     * file locations*/
    VmSystem *system = malloc(sizeof(VmSystem));

    /* If the user didn't supply any arguments, halt the program */
    if (argv[1] == NULL) {
        puts("Error! Stock file must be specified!");

        exit(1);

    /* Otherwise, if the path provided is inaccurate, halt the program */
    } else if(!fileExists(argv[1])) {
        puts("Error! Stock file not found!");
        exit(1);
    }
    /* If there was a path passed in as an argument and the file
     * exists, continue with execution */

    if (runTests) {
        run_tests();
    }

    system->stockFileName = copyString(argv[1]);

    initMenu(menu);
    systemInit(system);
    loadData(system, argv[1], "coins.dat");

    /* The main loop of the program, and is where the user
     * can call the various functions available */
    while (TRUE) {
        displayMenu(menu);
        printf("Select your option (1-9): ");
        getMenuChoice(menu)(system);
        puts("Returning to main menu...");
    }

    return EXIT_SUCCESS;
}
