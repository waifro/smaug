SOURCE := main.c core.c file_operate.c dir_tree.c dir_operate.c argv_parse.c

ODIR := output
dummy_build_folder := $(shell mkdir $(ODIR))
OUTPUT := $(ODIR)/$(notdir $(CURDIR))

all : $(SOURCE)
	gcc $(SOURCE) -Wall -o $(OUTPUT)
