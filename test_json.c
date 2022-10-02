#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>
#include <limits.h>
#include "miniunit.h"
#include "clog.h"
#include "json.h"

// parse_int() test declarations.
static int _test_parse_int_valid();
static int _test_parse_char_invalid();
static int _test_parse_int_valid_multidigit();
static int _test_parse_int_valid_negative();
static int _test_parse_int_char_valid();
static int _test_parse_int_char_neg_valid();
static int _test_parse_char_int_invalid();
static int _test_parse_char_neg_invalid();
static int _test_parse_char_multineg_invalid();
static int _test_parse_space_invalid();
static int _test_parse_space_valid();
//-------------------------------------------------
// parse_string() test declarations.
static int _test_parse_string_valid();
static int _test_parse_string_valid_one_char();
static int _test_parse_string_valid_multi_chars();
static int _test_parse_string_invalid();
//-------------------------------------------------
// parse_element() test declarations.
static int _test_parse_element_int();
static int _test_parse_element_whitespace_int();
static int _test_parse_element_whitespace_int_odd();
static int _test_parse_element_invalid_int();
static int _test_parse_element_string();
static int _test_parse_element_invalid_string();
static int _test_parse_element_invalid();
static void _test_print_element();
static int _test_print_element_letter();
//-------------------------------------------------
// parse_list() test declarations.
static int _test_parse_list_empty_valid();
static int _test_parse_list_basic_valid();
static int _test_parse_list_int_valid();
static int _test_parse_list_int_multidigit_valid();
static int _test_parse_list_string_valid();
static int _test_parse_list_two_string_valid();

static int _test_parse_list_matrix_int_valid();
static int _test_parse_list_matrix_multint_valid();
static int _test_parse_list_matrix_string_valid();
static int _test_parse_list_matrix_multistring_valid();
static int _test_parse_list_open_valid();
static int _test_parse_list_not_open_valid();
static int _test_parse_list_open_invalid();
static int _test_parse_list_initial_invalid();
static int _test_parse_list_comma_invalid();
static int _test_parse_list_open_end_invalid(); 
static int _test_parse_list_half_open_invalid();
static int _test_parse_list_brackets_invalid();

int main(int argc, char* argv[]) {

	// pars_int() test calls.
	//--------------------------------------------
	mu_run(_test_parse_int_valid);
	mu_run(_test_parse_char_invalid);

	mu_run(_test_parse_int_valid_multidigit);
	mu_run(_test_parse_int_valid_negative);
	mu_run(_test_parse_int_char_valid);
	mu_run(_test_parse_int_char_neg_valid);

	mu_run(_test_parse_char_int_invalid);
	mu_run(_test_parse_char_neg_invalid);	
	mu_run(_test_parse_char_multineg_invalid);

	mu_run(_test_parse_space_invalid);
	mu_run(_test_parse_space_valid);

	// parse_string() test calls.
	//--------------------------------------------
	mu_run(_test_parse_string_valid);
	mu_run(_test_parse_string_valid_one_char);
	mu_run(_test_parse_string_valid_multi_chars);
	mu_run(_test_parse_string_invalid);

	// parse_element() test calls.
	//--------------------------------------------
	mu_run(_test_parse_element_int);
	mu_run(_test_parse_element_whitespace_int);
	mu_run(_test_parse_element_whitespace_int_odd);
	mu_run(_test_parse_element_invalid_int);
	mu_run(_test_parse_element_string);
	mu_run(_test_parse_element_invalid_string);
	mu_run(_test_parse_element_invalid);
	_test_print_element();
	mu_run(_test_print_element_letter);

	// parse_list() test calls.
	//--------------------------------------------
	mu_run(_test_parse_list_empty_valid);
	mu_run(_test_parse_list_basic_valid);
	mu_run(_test_parse_list_int_valid);
	mu_run(_test_parse_list_int_multidigit_valid);
	mu_run(_test_parse_list_string_valid);
	mu_run(_test_parse_list_two_string_valid);

	mu_run(_test_parse_list_matrix_int_valid);
	mu_run(_test_parse_list_matrix_multint_valid);
	mu_run(_test_parse_list_matrix_string_valid);
	mu_run(_test_parse_list_matrix_multistring_valid);
	mu_run(_test_parse_list_open_valid);
	mu_run(_test_parse_list_not_open_valid);
	mu_run(_test_parse_list_open_invalid);
    mu_run(_test_parse_list_initial_invalid);
	mu_run(_test_parse_list_comma_invalid);
	mu_run(_test_parse_list_open_end_invalid); 
	mu_run(_test_parse_list_half_open_invalid);
	mu_run(_test_parse_list_brackets_invalid);

	return EXIT_SUCCESS;
}
//---------------------------------------------
// parse_int() test cases.
//---------------------------------------------
static int _test_parse_int_valid() {
	mu_start();

	int a_value;
	char* input = "1";
	char const* a_pos = input;
	bool is_success = parse_int(&a_value, &a_pos);
	mu_check(is_success);
	mu_check(a_pos == input + 1);
	mu_check(a_value == 1);

	mu_end();
}

static int _test_parse_char_invalid() {
	mu_start();

	int a_value;
	char* input = "B";
	char const* a_pos = input;
	bool is_success = parse_int(&a_value, &a_pos);
	mu_check(!is_success);
	mu_check(a_pos == input);

	mu_end();
}

static int _test_parse_int_valid_multidigit() {
	mu_start();

	int a_value;
	char* input = "45";
	char const* a_pos = input;
	bool is_success = parse_int(&a_value, &a_pos);
	mu_check(is_success);
	mu_check(a_pos == input + 2);
	mu_check(a_value == 45);

	mu_end();
}

static int _test_parse_int_valid_negative() {
	mu_start();

	int a_value;
	char* input = "-45";
	char const* a_pos = input;
	bool is_success = parse_int(&a_value, &a_pos);
	mu_check(is_success);
	mu_check(a_pos == input + 3);
	mu_check(a_value == -45);

	mu_end();
}

static int _test_parse_int_char_valid() {
	mu_start();

	int a_value;
	char* input = "123AAA";
	char const* a_pos = input;
	bool is_success = parse_int(&a_value, &a_pos);
	mu_check(is_success);
	mu_check(a_pos == input + 3);
	mu_check(a_value == 123);

	mu_end();
}

static int _test_parse_int_char_neg_valid() {
	mu_start();

	int a_value;
	char* input = "-123AAA";
	char const* a_pos = input;
	bool is_success = parse_int(&a_value, &a_pos);
	mu_check(is_success);
	mu_check(a_pos == input + 4);
	mu_check(a_value == -123);

	mu_end();
}

static int _test_parse_char_int_invalid() {
	mu_start();

	int a_value;
	char* input = "AAA454";
	char const* a_pos = input;
	bool is_success = parse_int(&a_value, &a_pos);
	mu_check(!is_success);
	mu_check(a_pos == input);

	mu_end();
}

static int _test_parse_char_neg_invalid() {
	mu_start();

	int a_value;
	char* input = "-AA454";
	char const* a_pos = input;
	bool is_success = parse_int(&a_value, &a_pos);
	mu_check(!is_success);
	mu_check(a_pos == input + 1);

	mu_end();
}

static int _test_parse_char_multineg_invalid() {
	mu_start();

	int a_value;
	char* input = "--45";
	char const* a_pos = input;
	bool is_success = parse_int(&a_value, &a_pos);
	mu_check(!is_success);
	mu_check(a_pos == input + 1);

	mu_end();
}

static int _test_parse_space_invalid() {
	mu_start();

	int a_value;
	char* input = "  KD";
	char const* a_pos = input;
	bool is_success = parse_int(&a_value, &a_pos);
	mu_check(!is_success);
	mu_check(a_pos == input);

	mu_end();
}

static int _test_parse_space_valid() {
	mu_start();

	int a_value;
	char* input = "123   ";
	char const* a_pos = input;
	bool is_success = parse_int(&a_value, &a_pos);
	mu_check(is_success);
	mu_check(a_pos == input + 3);
	mu_check(a_value == 123);

	mu_end();
}
//-----------------------------------------------------
// parse_string() test cases.
//-----------------------------------------------------
static int _test_parse_string_valid() {
	mu_start();

	char* result;
	char const* input = "\"\"";
	char const* pos = input;
	bool is_success = parse_string(&result, &pos);
	mu_check(is_success);
	mu_check_strings_eq("", result);
	mu_check(pos == input + 2);
	mu_check(*pos == '\0');
	free(result);

	mu_end();
}

static int _test_parse_string_valid_one_char() {
	mu_start();

	char* result;
	char const* input = "\"D\"";
	char const* pos = input;
	bool is_success = parse_string(&result, &pos);
	mu_check(is_success);
	mu_check_strings_eq("D", result);
	mu_check(pos == input + 3);
	mu_check(*pos == '\0');
	free(result);

	mu_end();
}

static int _test_parse_string_valid_multi_chars() {
	mu_start();

	char* result;
	char const* input = "\"DKB\"";
	char const* pos = input;
	bool is_success = parse_string(&result, &pos);
	mu_check(is_success);
	mu_check_strings_eq("DKB", result);
	mu_check(pos == input + 5);
	mu_check(*pos == '\0');
	free(result);

	mu_end();
}

static int _test_parse_string_invalid() {
	mu_start();

	char* result;
	char const* input = "\"D";
	char const* pos = input;
	bool is_success = parse_string(&result, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 2);
	mu_check(*pos == '\0');
	//-------------------------
	input = "\"D\nK\"";
	pos = input;
	is_success = parse_string(&result, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 2);
	mu_check(*pos == '\n');
	//-------------------------
	input = "\"DK\0\"";
	pos = input;
	is_success = parse_string(&result, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 3);
	mu_check(*pos == '\0');
	//-------------------------
	input = "\"D\nK\0\"";
	pos = input;
	is_success = parse_string(&result, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 2);
	mu_check(*pos == '\n');

	mu_end();
}
//-----------------------------------------------------
// parse_element() test cases.
//-----------------------------------------------------
static int _test_parse_element_int() {
	mu_start();

	Element element;
	char const* input = "9";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(element.as_int == 9);
	mu_check(element.type == ELEMENT_INT);
	mu_check(pos == input + 1);
	mu_check(*pos == '\0');
	//---------------------------------------------
	input = "-5";
	pos = input;
	is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(element.as_int == -5);
	mu_check(element.type == ELEMENT_INT);
	mu_check(pos == input + 2);
	mu_check(*pos == '\0');

	mu_end();
}

static int _test_parse_element_whitespace_int() {
	mu_start();

	Element element;
	char const* input = "  7";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(element.as_int == 7);
	mu_check(element.type == ELEMENT_INT);
	mu_check(pos == input + 3);
	mu_check(*pos == '\0');

	mu_end();
}

static int _test_parse_element_whitespace_int_odd() {
	mu_start();

	Element element;
	char const* input = " 8 K";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(element.as_int == 8);
	mu_check(element.type == ELEMENT_INT);
	mu_check(pos == input + 2);
	mu_check(*pos == ' ');

	mu_end();
}

static int _test_parse_element_invalid_int() {
	mu_start();

	Element element;
	char const* input = "--3";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 1);
	mu_check(*pos == '-');

	mu_end();
}

static int _test_parse_element_string() {
	mu_start();

	Element element;
	char const* input = "\"KLB\"";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check_strings_eq("KLB", element.as_string);
	mu_check(element.type == ELEMENT_STRING);
	mu_check(pos == input + 5);
	mu_check(*pos == '\0');
	free_element(element);

	mu_end();
}

static int _test_parse_element_invalid_string() {
	mu_start();

	Element element;
	char const* input = "\"KLB";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 4);
	mu_check(*pos == '\0');

	mu_end();
}

static int _test_parse_element_invalid() {
	mu_start();

	Element element;
	char const* input = "KLB";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	mu_check(pos == input);
	mu_check(*pos == 'K');

	mu_end();
}

static void _test_print_element() {
	mu_start();

	Element element;
	char const* value = "423";
	bool is_success = parse_element(&element, &value);
	mu_check(is_success);
	printf("Testing parse_element(&element, \"423\")\n");
	printf(" - Expected: 423\n");
	printf(" - Actual:   ");
	print_element(element);
	fputc('\n', stdout);
	free_element(element);
}

static int _test_print_element_letter() {
	mu_start();

	Element element;
	char const* value = "\"JLC\"";
	bool is_success = parse_element(&element, &value);
	mu_check(is_success);
	printf("Testing parse_element(&element, \"\\\"JLC\\\"\")\n");
	printf(" - Expected: \"JLC\"\n");
	printf(" - Actual:   ");
	print_element(element);
	fputc('\n', stdout);
	free_element(element);

	mu_end();
}
//-----------------------------------------------------
// parse_list() test cases.
//-----------------------------------------------------
static int _test_parse_list_empty_valid() {
	mu_start();

	Node* head = NULL;
	char const* input = "[]";
	char const* pos = input;
	bool is_success = parse_list(&head, &pos);
	mu_check(is_success);
	mu_check(head == NULL);
	mu_check(pos == input + 2);

	mu_end();
}

static int _test_parse_list_basic_valid() {
	mu_start();

	Node* head = NULL;
	char const* input = "[0]";
	char const* pos = input;
	bool is_success = parse_list(&head, &pos);
	mu_check(is_success);	
	mu_check(head->element.type == ELEMENT_INT);
	mu_check(head->element.as_int == 0);
	mu_check(head->next == NULL);
	mu_check(pos == input + 3);
	Element element = (Element) { .as_list = head, .type = ELEMENT_LIST };
	free_element(element);

	mu_end();
}

static int _test_parse_list_int_valid() {
	mu_start();

	Node* head = NULL;
	char const* input = "[1, 2]";
	char const* pos = input;
	bool is_success = parse_list(&head, &pos);
	mu_check(is_success);
	mu_check(head->element.type == ELEMENT_INT);
	mu_check(head->element.as_int == 1);
	mu_check(head->next->element.as_int == 2);
	mu_check((head->next)->next == NULL);
	mu_check(pos == input + 6);
	Element element = (Element) { .as_list = head, .type = ELEMENT_LIST };
	free_element(element);

	mu_end();
}

static int _test_parse_list_int_multidigit_valid() {
	mu_start();

	Node* head = NULL;
	char const* input = "[12, 14]";
	char const* pos = input;
	bool is_success = parse_list(&head, &pos);
	mu_check(is_success);
	mu_check(head->element.type == ELEMENT_INT);
	mu_check(head->element.as_int == 12);
	mu_check(head->next->element.as_int == 14);
	mu_check((head->next)->next == NULL);
	mu_check(pos == input + 8);
	Element element = (Element) { .as_list = head, .type = ELEMENT_LIST};
	free_element(element);

	mu_end();
}

static int _test_parse_list_string_valid() {
	mu_start();

	Node* head = NULL;
	char const* input = "[\"a\"]";
	char const* pos = input;
	bool is_success = parse_list(&head, &pos);
	mu_check(is_success);
	mu_check(head->element.type == ELEMENT_STRING);
	mu_check_strings_eq(head->element.as_string, "a");
	mu_check(head->next == NULL);
	mu_check(pos == input + 5);
	Element element = (Element) { .type = ELEMENT_LIST, .as_list = head};
	free_element(element);

	mu_end();
}

static int _test_parse_list_two_string_valid() {
	mu_start();

	Node* head = NULL;
	char const* input = "[\"a\",\"b\"]";
	char const* pos = input;
	bool is_success = parse_list(&head, &pos);
	mu_check(is_success);
	mu_check(head->element.type == ELEMENT_STRING);
	mu_check_strings_eq(head->element.as_string, "a");
	mu_check_strings_eq(head->next->element.as_string, "b");
	mu_check((head->next)->next == NULL);
	mu_check(pos == input + 9);
	Element element = (Element) { .type = ELEMENT_LIST, .as_list = head};
	free_element(element);

	mu_end();
}

static int _test_parse_list_matrix_int_valid() {
	mu_start();

	Node* head = NULL;
	char const* input = "[[1]]";
	char const* pos = input;
	bool is_success = parse_list(&head, &pos);
	mu_check(is_success);
	mu_check(head->element.type == ELEMENT_LIST);
	mu_check(head->element.as_list->element.as_int == 1);
	mu_check(head->next == NULL);
	mu_check(pos == input + 5);
	Element element = (Element) { .type = ELEMENT_LIST, .as_list = head};
	free_element(element);

	mu_end();
}

static int _test_parse_list_matrix_multint_valid() {
	mu_start();

	Node* head = NULL;
	char const* input = "[[1,2]]";
	char const* pos = input;
	bool is_success = parse_list(&head, &pos);
	mu_check(is_success);
	mu_check(head->element.type == ELEMENT_LIST);
	mu_check(head->element.as_list->element.as_int == 1);
	mu_check(head->element.as_list->next->element.as_int == 2);
	mu_check(head->next == NULL);
	mu_check(pos == input + 7);
	Element element = (Element) { .type = ELEMENT_LIST, .as_list = head};
	free_element(element);

	mu_end();
}

static int _test_parse_list_matrix_string_valid() {
	mu_start();

	Node* head = NULL;
	char const* input = "[[\"a\"]]";
	char const* pos = input;
	bool is_success = parse_list(&head, &pos);
	mu_check(is_success);
	mu_check(head->element.type == ELEMENT_LIST);
	mu_check_strings_eq(head->element.as_list->element.as_string, "a");
	mu_check(head->next == NULL);
	mu_check(pos == input + 7);
	Element element = (Element) { .type = ELEMENT_LIST, .as_list = head};
	free_element(element);

	mu_end();
}

static int _test_parse_list_matrix_multistring_valid() {
	mu_start();

	Node* head = NULL;
	char const* input = "[[\"a\",\"b\"]]";
	char const* pos = input;
	bool is_success = parse_list(&head, &pos);
	mu_check(is_success);
	mu_check(head->element.type == ELEMENT_LIST);
	mu_check_strings_eq(head->element.as_list->element.as_string, "a");
	mu_check_strings_eq(head->element.as_list->next->element.as_string, "b");
	mu_check(head->next == NULL);
	mu_check(pos == input + 11);
    Element element = (Element) { .type = ELEMENT_LIST, .as_list = head};
	free_element(element);

	mu_end();
}

static int _test_parse_list_open_valid() {
	mu_start();

	Node* head = NULL;
	char const* input = "[1]A";
	char const* pos = input;
	bool is_success = parse_list(&head, &pos);
	mu_check(is_success);
	mu_check(head->element.type == ELEMENT_INT);
	mu_check(head->element.as_int == 1);
	mu_check(head->next == NULL);
	mu_check(pos == input + 3);
	Element element = (Element) { .type = ELEMENT_LIST, .as_list = head};
	free_element(element);

	mu_end();
}

static int _test_parse_list_not_open_valid() {
	mu_start();

	Node* head = NULL;
	char const* input = "[1, \"A\"]";
	char const* pos = input;
	bool is_success = parse_list(&head, &pos);
	mu_check(is_success);
	mu_check(head->element.type == ELEMENT_INT);
	mu_check(head->element.as_int == 1);
	mu_check_strings_eq(head->next->element.as_string, "A");
	mu_check((head->next)->next == NULL);
	Element element = (Element) { .type = ELEMENT_LIST, .as_list = head};
	free_element(element);

	mu_end();
}

static int _test_parse_list_open_invalid() {
	mu_start();

	Node* head = NULL;
	char const* input = "1, 2";
	char const* pos = input;
	bool is_success = parse_list(&head, &pos);
	mu_check(!is_success);
	mu_check(head == NULL);
	mu_check(pos == input);

	mu_end();
}

static int _test_parse_list_initial_invalid() {
	mu_start();

	Node* head = NULL;
	char const* input = "A[]";
	char const* pos = input;
	bool is_success = parse_list(&head, &pos);
	mu_check(!is_success);
	mu_check(head == NULL);
	mu_check(pos == input);

	mu_end();
}

static int _test_parse_list_comma_invalid() {
	mu_start();

	Node* head = NULL;
	char const* input = "[1,,2]";
	char const* pos = input;
	bool is_success = parse_list(&head, &pos);
	mu_check(!is_success);
	mu_check(head != NULL);
	mu_check(pos == input + 3);
	Element element = (Element) { .type = ELEMENT_LIST, .as_list = head};
	free_element(element);

	mu_end();
}

static int _test_parse_list_open_end_invalid() {
	mu_start();

	Node* head = NULL;
	char const* input = "[1,";
	char const* pos = input;
	bool is_success = parse_list(&head, &pos);
	mu_check(!is_success);
	mu_check(head != NULL);
	mu_check(pos == input + 2);
	Element element = (Element) { .type = ELEMENT_LIST, .as_list = head};
	free_element(element);

	mu_end();
}

static int _test_parse_list_half_open_invalid() {
	mu_start();

	Node* head = NULL;
	char const* input = ",14]";
	char const* pos = input;
	bool is_success = parse_list(&head, &pos);
	mu_check(!is_success);
	mu_check(head == NULL);
	mu_check(pos == input);

	mu_end();
}
	
static int _test_parse_list_brackets_invalid() {
	mu_start();

	Node* head = NULL;
	char const* input = "[[";
	char const* pos = input;
	bool is_success = parse_list(&head, &pos);
	mu_check(!is_success);
	mu_check(head == NULL);
	mu_check(pos == input + 1);

	mu_end();
}
