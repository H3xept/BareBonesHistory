#include "macros.h"
#include "Test.h"
#include "../src/history.h"

void setup(){
	init_history();
	fclose(fopen("historyTestFile", "w"));
	return;
}

void test_add_entry(){
	add_history_entry("test");
	clear_history();
}

void test_add_and_read_entry(){
	add_history_entry("test");
	assert_eq_str(current_history_entry(), "test");
	clear_history();
}

void test_add_and_read_multiple_entries(){
	add_history_entry("test");
	assert_eq_str(current_history_entry(), "test");
	add_history_entry("hello");
	assert_eq_str(current_history_entry(), "hello");
	add_history_entry(":)");
	assert_eq_str(current_history_entry(), ":)");
	clear_history();
}

void test_add_and_read_specific_entry(){
	add_history_entry("test");
	add_history_entry("hello");
	add_history_entry(":)");
	assert_eq_str(get_history_entry(2), "hello");
	clear_history();
}

void test_read_specific_entry_edge_cases(){
	assert_true(get_history_entry(1) == NULL);
	add_history_entry("test");
	add_history_entry("hello");
	add_history_entry(":)");
	assert_eq_str(get_history_entry(1), "test");
	assert_eq_str(get_history_entry(3), ":)");
	assert_true(get_history_entry(4) == NULL);
	assert_true(get_history_entry(11) == NULL);
	clear_history();
}

void test_entry_with_prefix(){
	assert_true(latest_history_entry_with_prefix("x") == NULL);
	add_history_entry("test");
	add_history_entry("hello");
	add_history_entry("rest");
	add_history_entry("hello there");
	add_history_entry(":)");
	assert_eq_str(latest_history_entry_with_prefix("hel"), "hello there");
	assert_eq_str(latest_history_entry_with_prefix(":"), ":)");
	assert_eq_str(latest_history_entry_with_prefix("te"), "test");
	assert_true(latest_history_entry_with_prefix("x") == NULL);
	assert_true(latest_history_entry_with_prefix("est") == NULL);
	clear_history();
}

void test_entry_with_substring(){
	assert_true(latest_history_entry_containing("x") == NULL);
	add_history_entry("test");
	add_history_entry("hello");
	add_history_entry("rest");
	add_history_entry("hello there");
	add_history_entry(":)");
	assert_eq_str(latest_history_entry_containing("hel"), "hello there");
	assert_eq_str(latest_history_entry_containing(":"), ":)");
	assert_eq_str(latest_history_entry_containing("es"), "rest");
	assert_eq_str(latest_history_entry_containing(")"), ":)");
	assert_true(latest_history_entry_containing("x") == NULL);
	assert_eq_str(latest_history_entry_containing(""), ":)");
	clear_history();
}

void test_history_IO(){
	add_history_entry("test");
	add_history_entry("hello");
	add_history_entry("rest");
	add_history_entry("hello there");
	add_history_entry(":)");
	export_history_to_file("historyTestFile");
	import_history_from_file("historyTestFile");
	assert_eq_str(get_history_entry(1), "test");
	assert_eq_str(get_history_entry(2), "hello");
	assert_eq_str(get_history_entry(3), "rest");
	assert_eq_str(get_history_entry(4), "hello there");
	assert_eq_str(get_history_entry(5), ":)");
	assert_true(get_history_entry(6) == NULL);
	clear_history();
}

void test_get_entire_history(){
	add_history_entry("test");
	add_history_entry("hello");
	add_history_entry("rest");
	add_history_entry("hello there");
	add_history_entry(":)");
	char** history_ptr = get_entire_history();
	assert_eq_str(*history_ptr, "test");
	assert_eq_str(*(history_ptr + 1), "hello");
	assert_eq_str(*(history_ptr + 2), "rest");
	assert_eq_str(*(history_ptr + 3), "hello there");
	assert_eq_str(*(history_ptr + 4), ":)");
	assert_true(*(history_ptr + 5) == NULL);
}

void teardown(){
	remove("historyTestFile");
	return;
}