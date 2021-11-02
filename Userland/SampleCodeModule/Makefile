include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard *.c)
SOURCES_ASM=$(wildcard library/*.asm)
SOURCES_LIBRARY=$(wildcard library/*.c)
SOURCES_USER=$(wildcard shell/*.c)

OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS_LIBRARY=$(SOURCES_LIBRARY:.c=.o)
OBJECTS_USER=$(SOURCES_USER:.c=.o)

all: $(MODULE)

$(MODULE): $(SOURCES) $(OBJECTS) $(OBJECTS_ASM) $(OBJECTS_LIBRARY) $(OBJECTS_USER)
	$(LD) -T sampleCodeModule.ld  $(OBJECTS)  $(OBJECTS_ASM) $(OBJECTS_LIBRARY) $(OBJECTS_USER) -o ../$(MODULE)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $<  -o $@

%.o:%.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o library/*.o  shell/*.o

.PHONY: all clean print
