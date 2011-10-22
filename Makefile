PROG			= main
TESTPROG		= nmeatest
CC				= msp430-gcc
CXX				= msp430-g++
OBJDUMP		= msp430-objdump
SIZE			= msp430-size
MSPDEBUG	= mspdebug
CFLAGS		= -Os -Wall -g -mmcu=msp430x2012 

OBJS=$(PROG).o
TESTOBJS=$(TESTPROG).o

all: main test

main: $(PROG).elf $(PROG).lst
	$(SIZE) $(PROG).elf

test: $(TESTPROG).elf $(TESTPROG).lst
	$(SIZE) $(TESTPROG).elf

.PHONY: all

$(PROG).elf: $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG).elf $(OBJS)

$(TESTPROG).elf: $(TESTOBJS)
	$(CC) $(CFLAGS) -o $(TESTPROG).elf $(TESTOBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.lst: %.elf
	$(OBJDUMP) -d $< >$@

clean:
	rm -fr *.elf *.lst $(OBJS) $(TESTOBJS)

install: $(PROG).elf
	$(MSPDEBUG) rf2500 "prog $(PROG).elf"

install-test: $(TESTPROG).elf
	$(MSPDEBUG) rf2500 "prog $(TESTPROG).elf"
