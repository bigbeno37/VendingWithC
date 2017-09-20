#include "TestCoins.h"
#include "../vm_system.h"
#include "../vm_options.h"
#include "Tests.h"

/*
 * Determine if getDecimalValue will return anticipated value given
 * a Price
 */
void getDecimalValueWillCorrectlyDetermineCorrectValue() {
    Price price, newPrice;
    price.cents = 50;
    price.dollars = 1;

    newPrice.cents = 50;
    newPrice.dollars = 0;

    iAssertThat("$1.50 will equal 150", 150, getDecimalValue(price));
    iAssertThat("$0.50 will equal 50", 50, getDecimalValue(newPrice));
}

/*
 * Determine if getPriceFromValue will return a correctly
 * formatted Price instance
 */
void getPriceFromValueWillCorrectlyReturnPrice() {
    int cash = 378;

    iAssertThat("Given 378 cents, there will be 3 dollars", 3, getPriceFromValue(cash).dollars);
    iAssertThat("Given 378 cents, there will be 78 cents", 78, getPriceFromValue(cash).cents);

    cash = 78;
    iAssertThat("Given 78 cents, there will be 0 dollars", 0, getPriceFromValue(cash).dollars);
    iAssertThat("Given 78 cents, there will be 78 cents", 78, getPriceFromValue(cash).cents);
}

/*
 * Determine if getCoinFromLine will return a correctly
 * instantiated Coin instance
 */
void getCoinFromLineWillCorrectlyReturnCoin() {
    char input[] = "1000,3";
    Coin coin;

    getCoinFromLine(input, &coin);

    iAssertThat("1000,3 will have count 3", 3, coin.count);
    iAssertThat("1000,3 will have denomination TEN_DOLLARS", TEN_DOLLARS, coin.denom);

    strcpy(input, "5,99");
    getCoinFromLine(input, &coin);

    iAssertThat("5,99 will have count 99", 99, coin.count);
    iAssertThat("5,99 will have denomination FIVE_CENTS", FIVE_CENTS, coin.denom);
}