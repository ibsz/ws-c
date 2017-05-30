/*
 ============================================================================
 Name        : stringutils.c
 Author      : ibsz
 Version     : v 1.0
 Copyright   : LGPL
 Description : string utils in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stringutils.h"

char *trimwhitespace(char *str) {
	char *end;

	// Trim leading space
	while (isspace((unsigned char) *str))
		str++;

	if (*str == 0)  // All spaces?
		return str;

	// Trim trailing space
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char) *end))
		end--;

	// Write new null terminator
	*(end + 1) = 0;

	return str;
}

size_t countCharInStr(char* str, char separator) {
	size_t i = 0;
	char *pch = strchr(str, separator);
	while (pch != NULL) {
		i++;
		pch = strchr(pch + 1, separator);
	}
	return i;
}

char** strSplit(char* a_str, const char a_delim) {
	char** result = 0;
	size_t count = 0;
	char* last_comma = 0;
	char delim[2];
	delim[0] = a_delim;
	delim[1] = 0;

	/* Count how many elements will be extracted. */
	char *pch = strchr(a_str, a_delim);
	while (pch != NULL) {
		count++;
		pch = strchr(pch + count, a_delim);
		last_comma = pch;
	}

	/* Add space for trailing token. */
	count += last_comma < (a_str + strlen(a_str) - 1);

	/* Add space for terminating null string so caller
	 knows where the list of returned strings ends. */
	count++;

	result = malloc(sizeof(char*) * count);

	if (result) {
		size_t idx = 0;
		char* token = strtok(a_str, delim);

		while (token) {
			*(result + idx++) = strdup(token);
			token = strtok(0, delim);
		}
		*(result + idx) = 0;
	}

	return result;
}

int indexOfStr(char** strArray, int length, char* matcher){
	int i;
	for(i=0; i<length; i++){
		char * str = strArray[i];
		if(strcmp(str, matcher) == 0){
			return i;
		}
	}
	return -1;

}
