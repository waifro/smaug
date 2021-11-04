SOURCE := main.c core.c dir_tree.c dir_operate.c

ODIR := output
dummy_build_folder := $(shell mkdir $(ODIR))
OUTPUT := $(ODIR)/$(notdir $(CURDIR))

all : $(SOURCE)
	gcc $(SOURCE) -Wall -o $(OUTPUT)
