SOURCE := source/main.c source/core.c source/file_tree.c source/file_operate.c source/dir_tree.c source/dir_operate.c source/argv_parse.c

ODIR := output
dummy_build_folder := $(shell mkdir $(ODIR))
OUTPUT := $(ODIR)/$(notdir $(CURDIR))

all : $(SOURCE)
	gcc $(SOURCE) -g -Wall -Werror -fsanitize=undefined -o $(OUTPUT)
