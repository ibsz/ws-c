/*
 ============================================================================
 Name        : iniparser.c
 Author      : ibsz
 Version     :
 Copyright   : Your copyright notice
 Description : ini file parser in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

typedef struct ini_tuple {
	char *key;				// key
	char *value;			// value
} INI_TUPLE;

typedef struct ini_section {
	char *section;			// section name
	void (*action)(void);	// action for interface call
	int interval; 			// action interval
	SLIST_HEADER *ptuple;	// list of key value pairs;
} INI_SECTION;

void ini_section_formater(INI_SECTION *sec);
