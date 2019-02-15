#ifndef __BARE_BONES_HISTORY__
#define __BARE_BONES_HISTORY__

#include <stdio.h>

// General
void import_history_from_file(FILE* file);
void export_history_to_file(FILE* file);
void clear(void);
char** get_entire_history(void);

// Entries
char* current_entry(void);
char* get_entry(unsigned int index);
char* latest_entry_with_prefix(char* prefix);
char* latest_entry_containing(char* substring);
unsigned int entries_n(void);

#endif
