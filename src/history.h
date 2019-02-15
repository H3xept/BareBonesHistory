#ifndef __BARE_BONES_HISTORY__
#define __BARE_BONES_HISTORY__

#include <stdio.h>

// General
void init_history();
void import_history_from_file(char* filename);
void export_history_to_file(char* filename);
void clear_history(void);
char** get_entire_history(void);

// Entries
void add_history_entry(char* line);
char* current_history_entry(void);
char* get_history_entry(unsigned int index);
char* latest_history_entry_with_prefix(char* prefix);
char* latest_history_entry_containing(char* substring);
unsigned int entries_n(void);

#endif
