/*
 ============================================================================
 Name        : slist.h
 Author      : ibsz
 Version     :
 Copyright   : Your copyright notice
 Description : slist header in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct slist_item {
	void *data;
	void *next;
	void *prev;

} SLIST_ITEM;

typedef struct slist_header {
	SLIST_ITEM *first;
	SLIST_ITEM *last;
	int count;
} SLIST_HEADER;

