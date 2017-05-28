/*
 ============================================================================
 Name        : slist.c
 Author      : ibsz
 Version     :
 Copyright   : Your copyright notice
 Description : slist header in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

SLIST_ITEM *add(SLIST_HEADER *header, void *data) {
	if (header == NULL || data == NULL) {
		return NULL;
	}
	SLIST_ITEM *item = malloc(sizeof(SLIST_ITEM));
	if (item == NULL) {
		return NULL;
	}

	item->data = data;
	item->next = NULL;
	item->prev = NULL;

	if (header->first == NULL) {
		header->first = item;
		header->last = item;
		header->count = 1;
	} else {
		header->last->next = item;
		item->prev = header->last;
		header->last = item;
		header->count += 1;
	}
	return item;
}

void *take(SLIST_HEADER *header) {
	if (header == NULL || header->first == NULL) {
		return NULL;
	}
	SLIST_ITEM *item = header->first;
	header->first = item->next;
	header->count -= 1;
	if (header->first != NULL) {
		header->first->prev = NULL;
	}
	item->next = NULL;
	return item->data;
}

void defaulr_print_item(void* data) {
	if (data == NULL)
		return;
	printf("%s ", (char*) data);
}

void print_list(SLIST_HEADER *header, void print_item(void*)) {
	if (header == NULL || header->first == NULL)
		return;
	SLIST_ITEM *current = header->first;
	while (current != NULL) {
		print_item(current->data);
		current = current->next;
	}
}

void print_list_default(SLIST_HEADER *header) {
	print_list(header, defaulr_print_item);
}

