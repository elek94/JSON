#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "miniunit.h"
#include "clog.h"
#include "json.h"

static void __list_append(Node** a_head, Node** a_tail, Element element); // helper

bool parse_int(int* a_value, char const** a_pos) {

	int digit_multiplier = 1; 							// declarations and initializations of variables.
	int each_digit = 0; 
	int total = 0;

	int len = 0;
	int length = strlen(*a_pos);

	if(*(*a_pos) != '-') {
		if(!isdigit(*(*a_pos))) {						// if no negative sign and no digit after, return false
			return false;
		}
		*a_value = 1;									// if digit, initialize positive 1.
	}
	else {
		if(!isdigit(*(*a_pos + 1))) {					// if negative sign and no digit after, return false.
			*a_pos += 1;
			return false;
		}
		*a_value = -1;									// if digit, initialize -1.
	}
	
	for(int i = 0; i <= length - 1; i += 1) {
		if(isdigit(*(*a_pos + i)) || (*(*a_pos) == '-' && isdigit(*(*a_pos + 1)) && i == 0)) {  // if digit or negative digit increase
			len += 1;																			// len by 1 for only count valid chars.
		}
	}

	for(int i = 0; i <= len; i++) {							// using ASCII, found the decimal equivalent for character
		if(isdigit(*(*a_pos + (len - 1) - i))) {			// as index increases, multiply the step and found the total with addition.
			each_digit = *(*a_pos + (len - 1) - i);
			each_digit -= '0';
			total += (each_digit * digit_multiplier);
			digit_multiplier *= 10;
		}
	}

	*a_pos += len;											// skip the pos for all valid characters that was counted.

	*a_value *= total;										// assign total calculated integer of previous string in the input.

	return true;
}

bool parse_string(char** a_s, char const** a_pos) {

	int length = strlen(*a_pos);
	int count_backslash = 0;
	int count_newline = 0;
	int count_null = 0;
	int position = 0;
	//---------------------------------------return FALSE part----------------------------------------------------------------------
	for(int i = 0; i <= length - 1; i += 1) {
		if(*(*a_pos + i) == '"' && (i == 0 || i > 0)) { 				// check if surrounded by "".
			count_backslash += 1;										// otherwise.
			if(count_backslash < 2) {
				position += 1;												// increase position only if double quotes detected.
			}
		}
		else if(*(*a_pos + i) == '\n' && i != length - 1) {				// check if there is newline in the middle of the string,
			count_newline += 1;											// if so, determine invalid.
			position -= 1;												// decrease position as invalid condition detected.
		}
		else {															//incremenet position as no invalid condition detected.
			position += 1;												// (we skip position as we detect what we want for validity
		}																// and decrease the position as we see unwanted invalid things.)
	}
	if(count_backslash % 2 != 0 || (count_newline >= 1 || count_null >= 1)) {
		*a_pos += position;												// as newline detected, skip position by position - 1
		return false;													// and return false.
	}
	//------------------------------------------ return TRUE part---------------------------------------------------------------
	*a_s = malloc((length + 1) * sizeof(*a_s));						// malloc called.

	position = 1;
	while(*(*a_pos + position) != '"') {							// don't parse escape code and assign **a_pos values to **a_s values.
		*(*a_s + (position - 1)) = *(*a_pos + position);
		position += 1;
	}
	*a_pos += (position + 1);										// increment by final position calculated in loop

	return true;
}

// PARSE_ELEMENT
//---------------------------------------------------------------------------------
bool parse_element(Element* a_element, char const** a_pos) {

	while(isspace(*(*a_pos))) {									// skip whitespaces.
		*a_pos += 1;
	}

	if(isdigit(*(*a_pos)) || *(*a_pos) == '-') {				// if input string literal digit(negative or positive), call parse_int.
		*a_element = (Element){ .type = ELEMENT_INT };
		return parse_int(&(a_element -> as_int), a_pos);
	}
	else if(*(*a_pos) == '"') {
		*a_element = (Element){ .type = ELEMENT_STRING };		// check if it is string otherwise, if so, call the element with
		return parse_string(&(a_element -> as_string), a_pos);	//  parse string.
	}
	else if(*(*a_pos) == '[') {
		*a_element = (Element){ .type = ELEMENT_LIST };         // check if it is list otherwise, if so, call parse_list().
		return parse_list(&(a_element -> as_list), a_pos);
	}
	else {									
		return false;											// and return false.
	}
}

// helper called for parse_list()
static void __list_append(Node** a_head, Node** a_tail, Element element) {

	Node* new_tail = malloc(sizeof(*new_tail));
	*new_tail = (Node) { .element = element, .next = NULL };

	if(*a_head == NULL) {
		*a_head = new_tail;
	}
	else {
		(*a_tail) -> next = new_tail;
	}
	*a_tail = new_tail;
}

// parse_list() definition and body flows throughout __list_append() helper.
bool parse_list(Node** a_head, char const** a_pos) {

	if((*(*a_pos) != '[')) {	// if opening brackets not in the beginning, it will return false.
		return false;
	}
	Node* a_tail = NULL;
	*a_pos += 1;
	int count_node = 0;
	Element element;

	while((*(*a_pos) != ']' && *(*a_pos + 1) != '\0')) {
		
		if(*(*a_pos) == ',' && *(*a_pos - 1) != ',') {
			*a_pos += 1;
		}

		bool is_parse = parse_element(&element, a_pos);

		if(is_parse) {
			__list_append(a_head, &a_tail, element); // helper called.
			count_node += 1;
		}
		else {
			if(count_node > 0) {
				for(int i = 0; i < count_node; i += 1) {
					free_element(element);
				}
			}
			return false;
		}
	}
	if(*(*a_pos) == ']') {
		*a_pos += 1;
		return true;
	}
	else {
		if(count_node > 0) {
			for(int i = 0; i < count_node; i += 1) {
				free_element(element);
			}
		}
		return false;
	}
}

void free_element(Element element) {				// free the Element's string when the parse_string function what we called in test 
	if(element.type == ELEMENT_STRING) {			// the test case.
		free((element.as_string));
	}
	if(element.type == ELEMENT_LIST) {
		while(element.as_list != NULL) {
			Node* new_head = element.as_list -> next;
			free_element(element.as_list -> element);
			free(element.as_list);
			element.as_list = new_head;
		}
	}
}

void print_element(Element element) {				// print the element if integer.
	if(element.type == ELEMENT_INT) {
		printf("%d", element.as_int);
	}
	else if(element.type == ELEMENT_STRING){		// print the element if string.
		printf("\"%s\"", element.as_string);
	}
}
