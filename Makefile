SOURCE := source/main.c source/ras.c source/rsd.c

ODIR := output
dummy_build_folder := $(shell mkdir $(ODIR))
OUTPUT := $(ODIR)/$(notdir $(CURDIR))

all : $(SOURCE)
	gcc $(SOURCE) -Wall -Wextra -o $(OUTPUT)
