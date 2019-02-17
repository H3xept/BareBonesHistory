#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "history.h"

struct hist_entry{
	struct hist_entry* next;
	struct hist_entry* previous;
	char* line;
};

static unsigned int length;
static struct hist_entry* start;
static struct hist_entry* end;

void _dealloc_entry(struct hist_entry* entry);
int _ends_in_newline(char* string);

// Public functions

void init_history(){
	start = NULL;
	end = NULL;
	length = 0;
}

void import_history_from_file(char* filename){
	if(end){
		clear_history();
	}
	FILE* history_file = fopen(filename, "r");
	char line[MAX_LINE_LEN];
	while(fgets(line, MAX_LINE_LEN, history_file) != NULL){
		add_history_entry(line);
	}
	fclose(history_file);
}

void export_history_to_file(char* filename){
	FILE* history_file = fopen(filename, "w");
	char* lines = calloc(length * MAX_LINE_LEN, sizeof(char));
	struct hist_entry* current_entry = start;
	while(current_entry){
		strcat(lines, current_entry->line);
		current_entry = current_entry->next;
	}
	fprintf(history_file, "%s", lines);
	fclose(history_file);
	free(lines);
}

void clear_history(){
	if(end){
		struct hist_entry* entry = start;
		while(entry->next){
			entry = entry->next;
			_dealloc_entry(entry->previous);
		}
		_dealloc_entry(entry);
	}
	init_history();
}

char** get_entire_history(){
	if(!length){
		return NULL;
	}
	char** history_array = calloc(length + 1, sizeof(char*));
	struct hist_entry* entry = start;
	for(int i = 0; i < length; i++){
		*(history_array + i) = entry->line;
		entry = entry->next;
	}
	*(history_array + length) = NULL;
	return history_array;
}

void add_history_entry(char* line){
	char* nl_terminated = calloc(strlen(line)+1, sizeof(char));
	if (!_ends_in_newline(line)) {
		nl_terminated = realloc(nl_terminated, strlen(line)+2);
		strncpy(nl_terminated, line, strlen(line));
		*(nl_terminated+strlen(nl_terminated)) = '\n';
	} else {
		strncpy(nl_terminated, line, strlen(line));
	}
	struct hist_entry* entry = calloc(1,sizeof(struct hist_entry));
	entry->line = nl_terminated;
	if(end){
		end->next = entry;
		entry->previous = end;
	}
	else{
		start = entry;
	}
	end = entry;
	length++;
}

char* current_history_entry(){
	if(!length){
		return NULL;
	}
	return end->line;
}

char* get_history_entry(unsigned int index){
	if(index >= length){
		return NULL;
	}
	struct hist_entry* entry = start;
	for(int i = 0; i < index; i++){
		entry = entry->next;
	}
	return entry->line;
}

char* latest_history_entry_with_prefix(char* prefix){
	if(!end){
		return NULL;
	}
	struct hist_entry* entry = end;
	do{
		if(strstr(entry->line, prefix) == entry->line){
			return entry->line;
		}
		entry = entry->previous;
	}while(entry);
	return NULL;
}

char* latest_history_entry_containing(char* substring){
	if(!end){
		return NULL;
	}
	struct hist_entry* entry = end;
	do{
		if(strstr(entry->line, substring)){
			return entry->line;
		}
		entry = entry->previous;
	}while(entry);
	return NULL;
}

unsigned int entries_n(){
	return length;
}

// Private functions

void _dealloc_entry(struct hist_entry* entry){
	free(entry->line);
	free(entry);
}

int _ends_in_newline(char* string){
	return *(string + strlen(string) - 1) == '\n';
}