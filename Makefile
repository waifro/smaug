SOURCE := source/mman.c source/main.c source/core.c source/dir_tree.c source/dir_operate.c source/db_core.c source/db_dir.c source/db_file.c source/other.c

# uncomment this line if your on windows
# LIBMMAN := "-L. -lmman"

ODIR := output
dummy_build_folder := $(shell mkdir $(ODIR))
OUTPUT := $(ODIR)/$(notdir $(CURDIR))

all : $(SOURCE)
	gcc $(SOURCE) -g -Wall -Werror $(LIBMMAN) -o $(OUTPUT)
