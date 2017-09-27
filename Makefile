# **************************************************************
#
# ** Student Name: Ben O'Sullivan
#
# ** Student Number: s3662617
#
# ** Date of submission: Wednesday, 27 Sept 2017
#
# ** Course: COSC1076 / COSC2207, Semester 2, 2017
#
# ***************************************************************

SOURCES=utility.c vm.c vm_coin.c vm_menu.c vm_options.c vm_stock.c
HEADERS=utility.h vm.h vm_coin.h vm_menu.h vm_options.h vm_stock.h vm_system.h
OBJECTS=vm.o vm_menu.o vm_coin.o vm_stock.o vm_options.o utility.o TestCoins.o TestData.o TestLinkedList.o Tests.o TestUtils.o
TEST_SOURCES=tests/TestCoins.c tests/TestLinkedList.c tests/TestData.c tests/Tests.c tests/TestUtils.c
TEST_HEADERS=tests/TestCoins.h tests/TestLinkedList.h tests/TestData.h tests/Tests.h tests/TestUtils.h
PROGRAM=vm
DEBUG=-g
FLAGS=-ansi -pedantic -Wall $(DEBUG)

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	gcc $(FLAGS) -o $(PROGRAM) $(OBJECTS)

vm.o: vm.c $(HEADERS)
	gcc $(FLAGS) -c vm.c

vm_menu.o: vm_menu.c $(HEADERS)
	gcc $(FLAGS) -c vm_menu.c

vm_coin.o: vm_coin.c $(HEADERS)
	gcc $(FLAGS) -c vm_coin.c

vm_stock.o: vm_stock.c $(HEADERS)
	gcc $(FLAGS) -c vm_stock.c

vm_options.o: vm_options.c $(HEADERS)
	gcc $(FLAGS) -c vm_options.c

utility.o: utility.c $(HEADERS)
	gcc $(FLAGS) -c utility.c

TestCoins.o: tests/TestCoins.c $(TEST_HEADERS)
	gcc $(FLAGS) -c tests/TestCoins.c

TestData.o: tests/TestData.c $(TEST_HEADERS)
	gcc $(FLAGS) -c tests/TestData.c

TestLinkedList.o: tests/TestLinkedList.c $(TEST_HEADERS)
	gcc $(FLAGS) -c tests/TestLinkedList.c

Tests.o: tests/Tests.c $(TEST_HEADERS)
	gcc $(FLAGS) -c tests/Tests.c

TestUtils.o: tests/TestUtils.c $(TEST_HEADERS)
	gcc $(FLAGS) -c tests/TestUtils.c

clean:
	rm $(PROGRAM) $(OBJECTS)

archive:
	zip $(USER)-a2 $(SOURCES) $(HEADERS) $(TEST_SOURCES) $(TEST_HEADERS) Makefile
