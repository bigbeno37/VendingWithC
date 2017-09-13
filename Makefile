SOURCES=utility.c vm.c vm_coin.c vm_linkedlist.c vm_menu.c vm_options.c vm_stock.c
HEADERS=utility.h vm.h vm_coin.h vm_linkedlist.h vm_menu.h vm_options.h vm_stock.h vm_system.h
TEST_SOURCES=tests/TestCoins.c tests/TestLinkedList.c tests/TestLoadData.c tests/Tests.c tests/TestUtils.c
TEST_HEADERS=tests/TestCoins.h tests/TestLinkedList.h tests/TestLoadData.h tests/Tests.h tests/TestUtils.h
PROGRAM=vm
DEBUG=-g
FLAGS=-ansi -pedantic -Wall $(DEBUG)

all:
	gcc $(FLAGS) -o $(PROGRAM) $(SOURCES) $(TEST_SOURCES)

clean:
	rm $(PROGRAM)

archive:
	zip $(USER)-a2 $(SOURCES) $(HEADERS) Makefile
