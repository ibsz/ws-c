/*
 * queue.c
 *
 *  Created on: May 29, 2017
 *      Author: ibsz
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

ELEM *add(HEAD *head, DATA item) {
	if (head == NULL) {
		return NULL;
	}
	ELEM *elem = malloc(sizeof(ELEM));
	if (elem == NULL) {
		return NULL;
	}

	elem->item = item;
	elem->next = NULL;

	if (head->first == NULL) {
		head->first = elem;
		head->last = elem;
		head->len = 1;
	} else {
		elem->next = head->first;
		head->first = elem;
	}
	return elem;
}

ELEM *take(HEAD *head) {
	if (head == NULL || head->first == NULL) {
		return NULL;
	}

	ELEM *current = head->first;
	while (current->next != head->last) {
		current = current->next;
	}
	head->last = current;
	head->len -= 1;
	current = current->next;
	head->last->next = NULL;
	return current;
}

void print_item(DATA data) {
	printf("%d / '%c'; ", data.num, data.sym);
}

void print_queue(HEAD *header) {
	if (header == NULL || header->first == NULL)
		return;
	printf("\nqueue: ");
	ELEM *current = header->first;
	while (current != NULL) {
		print_item(current->item);
		current = current->next;
	}
	printf("\n");
}

ELEM *createElem(DATA data) {
	ELEM *elem = malloc(sizeof(ELEM));
	if (elem == NULL) {
		return NULL;
	}
	elem->item = data;
	elem->next = NULL;
	return elem;
}

ELEM *push(HEAD *head, DATA data) {
	return add(head, data);
}

ELEM *enqueue(HEAD *head, DATA data) {
	return add(head, data);
}

ELEM *dequeue(HEAD *head) {
	return take(head);
}

ELEM *pop(HEAD *head) {
	return take(head);
}

ELEM *front(HEAD *head) {
	if (head == NULL || head->last == NULL) {
		return NULL;
	}
	return head->last;
}

ELEM *top(HEAD *head) {
	if (head == NULL || head->first == NULL) {
		return NULL;
	}
	return head->first;
}

ELEM *back(HEAD *head) {
	return top(head);
}
