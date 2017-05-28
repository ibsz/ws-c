/*
 ============================================================================
 Name        : IniFile2.c
 Author      : ibsz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "iniparser.h"

int main(void) {
	SLIST_HEADER* ini_list = ini_parse_file("datenlogger.ini");
	print_list(ini_list, ini_section_formater);
	printf("get key from [pi3] url: %s\n",get_key(ini_list, "pi3", "url"));
	puts("Press any key...");
	return EXIT_SUCCESS;
}
