#Sidney Robinson
#Simrobin 1643731
#CMPS12B/M
#Makefile with macros
#------------------------------------------------------------------------------
# Makefile for Dictionary with Hash Table Implementation and test Client
#------------------------------------------------------------------------------

ADT_NAME  =  Dictionary
SOURCES   = $(ADT_NAME).c    $(ADT_NAME)Client.c
OBJECTS   = $(ADT_NAME).o    $(ADT_NAME)Client.o
HEADERS   = $(ADT_NAME).h  
EXEBIN    = DictionaryTest
FLAGS     = -std=c99 -Wall

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES) $(HEADERS)
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm -f $(EXEBIN) $(OBJECTS)

check:
	valgrind --leak-check=full $(EXEBIN) 
