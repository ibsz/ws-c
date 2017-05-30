/*
 ============================================================================
 Name        : stringutils.h
 Author      : ibsz
 Version     : v 1.0
 Copyright   : LGPL
 Description : string utils in C, Ansi-style
 ============================================================================
 */

#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

/**
 * trim white space
 */
char *trimwhitespace(char *str);

/**
 * count number of separator in str
 */
size_t countCharInStr(char* str, char separator);

char **strSplit(char* a_str, const char a_delim);

int indexOfStr(char** strArray, int length, char* matcher);

#endif /* STRINGUTILS_H_ */

