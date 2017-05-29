/*
 * queue
 *
 *  Created on: May 29, 2017
 *      Author: ibsz
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef union char_or_int
{
	int num;
	char sym;
} DATA;

typedef struct elem
{
	struct elem *next;
	DATA item;
} ELEM;

typedef struct head
{
	ELEM *first;
	ELEM *last;
	int len;
} HEAD;

/**
 * Add an element to top of the queue
 */
ELEM *push(HEAD *head, DATA data);

/**
 * Add an element to top of the queue
 */
ELEM *enqueue(HEAD *head, DATA data);

/**
 * Removes and give back the last element of the queue
 */
ELEM *dequeue(HEAD *head);

/**
 * Removes and give back the first element of the queue
 */
ELEM *pop(HEAD *head);

/**
 * Give back the last element of the queue w/o changing the queue
 */
ELEM *front(HEAD *head);

/**
 * Give back the first element of the queue w/o changing the queue
 */
ELEM *top(HEAD *head);

/**
 * Give back the first element of the queue w/o changing the queue
 */
ELEM *back(HEAD *head);

#endif /* QUEUE_H_ */
