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
	assert_eq_str(current_history_entry(), "test\n");
	clear_history();
}

void test_add_and_read_multiple_entries(){
	add_history_entry("test");
	assert_eq_str(current_history_entry(), "test\n");
	add_history_entry("hello");
	assert_eq_str(current_history_entry(), "hello\n");
	add_history_entry(":)");
	assert_eq_str(current_history_entry(), ":)\n");
	clear_history();
}

void test_add_and_read_specific_entry(){
	add_history_entry("test");
	add_history_entry("hello");
	add_history_entry(":)");
	assert_eq_str(get_history_entry(1), "hello\n");
	clear_history();
}

void test_read_specific_entry_edge_cases(){
	assert_true(get_history_entry(0) == NULL);
	add_history_entry("test");
	add_history_entry("hello");
	add_history_entry(":)");
	assert_eq_str(get_history_entry(0), "test\n");
	assert_eq_str(get_history_entry(2), ":)\n");
	assert_true(get_history_entry(3) == NULL);
	assert_true(get_history_entry(10) == NULL);
	clear_history();
}

void test_entry_with_prefix(){
	assert_true(latest_history_entry_with_prefix("x") == NULL);
	add_history_entry("test");
	add_history_entry("hello");
	add_history_entry("rest");
	add_history_entry("hello there");
	add_history_entry(":)");
	assert_eq_str(latest_history_entry_with_prefix("hel"), "hello there\n");
	assert_eq_str(latest_history_entry_with_prefix(":"), ":)\n");
	assert_eq_str(latest_history_entry_with_prefix("te"), "test\n");
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
	assert_eq_str(latest_history_entry_containing("hel"), "hello there\n");
	assert_eq_str(latest_history_entry_containing(":"), ":)\n");
	assert_eq_str(latest_history_entry_containing("es"), "rest\n");
	assert_eq_str(latest_history_entry_containing("\n"), ":)\n");
	assert_true(latest_history_entry_containing("x") == NULL);
	assert_eq_str(latest_history_entry_containing(""), ":)\n");
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
	assert_eq_str(get_history_entry(0), "test\n");
	assert_eq_str(get_history_entry(1), "hello\n");
	assert_eq_str(get_history_entry(2), "rest\n");
	assert_eq_str(get_history_entry(3), "hello there\n");
	assert_eq_str(get_history_entry(4), ":)\n");
	assert_true(get_history_entry(5) == NULL);
}

void teardown(){
	remove("historyTestFile");
	return;
}