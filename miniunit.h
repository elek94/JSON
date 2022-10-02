#include "clog.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#define mu_start()   				int __mu_line_number = 0
#define mu_check(condition)			do { 																		\
										if((__mu_line_number == 0) && (!(condition))) { 							\
											__mu_line_number = __LINE__;										\
										}																		\
									}while(false)
#define mu_run(function) 			do {																		\
										if(function()) {														\
											logf_red("Test failed: %s at line %d\n", (#function), function());	\
										}																		\
										else {																	\
											logf_green("Test passed: %s\n", (#function));						\
										}																		\
									}while(false)
#define 							mu_end() return(__mu_line_number)
#define 							mu_check_strings_eq(str1, str2) mu_check(!strcmp((str1), (str2)))

