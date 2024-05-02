CONTIKI_PROJECT = ml-example
all: $(CONTIKI_PROJECT)

MODULES_REL += /home/user/.local/lib/python3.10/site-packages/emlearn 

TARGET_LIBFILES += -lm

INC += /home/user/.local/lib/python3.10/site-packages/emlearn

CONTIKI = ../..
include $(CONTIKI)/Makefile.include
