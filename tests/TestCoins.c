/*
 * Created by bigbeno37 on 13/09/17.
 */

#include "TestCoins.h"
#include "../vm_system.h"
#include "../vm_options.h"
#include "Tests.h"

void isValidDenominationWillDetermineValidDenomination() {
    VmSystem *system = malloc(sizeof(VmSystem));
    loadCoins(system, "");

    assertTrue("5 is a valid denomination", isValidDenomination(5, system));
    assertTrue("10 is a valid denomination", isValidDenomination(10, system));
    assertTrue("20 is a valid denomination", isValidDenomination(20, system));
    assertTrue("50 is a valid denomination", isValidDenomination(50, system));
    assertTrue("100 is a valid denomination", isValidDenomination(100, system));
    assertTrue("200 is a valid denomination", isValidDenomination(200, system));
    assertTrue("500 is a valid denomination", isValidDenomination(500, system));
    assertTrue("1000 is a valid denomination", isValidDenomination(1000, system));
    assertFalse("105 is not a valid denomination", isValidDenomination(105, system));
}