CC = gcc
CFLAGS = -Wall --pedantic --std=c99
SOURCE_FOLDER = src
OUT_FOLDER = bin
SOURCE_FILES = $(SOURCE_FOLDER)/*.c
LIB_NAME = libhistory.a
DEPENDENCIES_FOLDER = dependencies

BARE_BONES_HISTORY = BareBonesHistory

all: target_dir compile_lib copy_headers

compile_lib: target_dir 
	@ echo "Compiling lib..."
	@ $(CC) -I$(DEPENDENCIES_FOLDER) $(CFLAGS) $(SOURCE_FILES) -c
	@ ar rs $(LIB_NAME) *.o
	@ cp $(LIB_NAME) bin/libs
	@ rm *.o $(LIB_NAME)

copy_headers: target_dir
	@ echo "Copying headers..."
	@ cp $(SOURCE_FOLDER)/*.h $(OUT_FOLDER)/headers/

target_dir:
	@ echo "Creating folder structure..."
	@ mkdir -p bin/headers
	@ mkdir -p bin/libs

clean:
	@ echo "Cleaning..."
	@ rm -rf bin/

