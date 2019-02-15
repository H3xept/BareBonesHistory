CC = gcc
CFLAGS = -Wall --pedantic --std=c99
SOURCE_FOLDER = src
OUT_FOLDER = bin
SOURCE_FILES = $(SOURCE_FOLDER)/*.c
LIB_NAME = libhistory.a
DEPENDENCIES_FOLDER = dependencies

BARE_BONES_HISTORY = BareBonesHistory
BARE_BONES_HISTORY_LOCATION = ../$(BARE_BONES_HISTORY)
BARE_BONES_HISTORY_LOCATION_GIT = "https://github.com/H3xept/BareBonesHistory"

all: taget_dir prepare_dependencies compile_dylib copy_headers
	
prepare_dependencies: 
	@ echo "Preparing dependencies";
	@ if [ -d $(BARE_BONES_HISTORY_LOCATION) ]; then\
		echo "Folder found locally, running make..."; \
		echo "Making $$BARE_BONES_HISTORY"; \
		make -C $(BARE_BONES_HISTORY_LOCATION); \
		cp $(BARE_BONES_HISTORY_LOCATION)/bin/headers/*.h $(DEPENDENCIES_FOLDER)/$(BARE_BONES_HISTORY)/ ; \
		cp $(BARE_BONES_HISTORY_LOCATION)/bin/libs/*.* $(DEPENDENCIES_FOLDER)/libs ; \
	else \
		echo "Fonder not found, cloning ..."; \
		git clone $(BARE_BONES_HISTORY_LOCATION_GIT) $(BARE_BONES_HISTORY); \
		echo "Making $$BARE_BONES_HISTORY ..." ; \
		make -C $(BARE_BONES_HISTORY); \
		cp $(BARE_BONES_HISTORY)/bin/headers/*.h $(DEPENDENCIES_FOLDER)/$(BARE_BONES_HISTORY)/ ; \
		cp $(BARE_BONES_HISTORY)/bin/libs/*.a $(DEPENDENCIES_FOLDER)/libs ; \
		rm -rf $(BARE_BONES_HISTORY); \
	fi;

compile_dylib: taget_dir 
	@ echo "Compiling lib..."
	@ $(CC) -I$(DEPENDENCIES_FOLDER) $(CFLAGS) $(SOURCE_FILES) -c $(DEPENDENCIES_FOLDER)/libs/*.a
	@ ar rs $(LIB_NAME) *.o
	@ cp $(LIB_NAME) bin/libs
	@ rm *.o $(LIB_NAME)

copy_headers: taget_dir
	@ echo "Copying headers..."
	@ cp $(SOURCE_FOLDER)/*.h $(OUT_FOLDER)/headers/

taget_dir:
	@ echo "Creating folder structure..."
	@ mkdir -p bin/headers
	@ mkdir -p bin/libs
	@ mkdir -p $(DEPENDENCIES_FOLDER)
	@ mkdir -p $(DEPENDENCIES_FOLDER)/$(BARE_BONES_HISTORY)
	@ mkdir -p $(DEPENDENCIES_FOLDER)/libs

clean:
	@ echo "Cleaning..."
	@ rm -rf bin/
	@ rm -rf dependencies/

