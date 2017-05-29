/*
 ============================================================================
 Name        : DoubleEndedQueue.c
 Author      : ibsz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void log(ELEM *elem){
	if(elem != NULL){
		print_item(elem->item);
	}
}

int main(void) {

	HEAD *head = malloc(sizeof(HEAD));
	if (head != NULL) {
		printf("\npush: ");
		log(push(head, (DATA ) { .num = 50 }));
		print_queue(head);
		printf("\npush: ");
		log(push(head, (DATA ) { .sym = 'F' }));
		print_queue(head);
		printf("\npush: ");
		log(push(head, (DATA ) { .num = 42 }));
		print_queue(head);
		printf("\npush: ");
		log(push(head, (DATA ) { .num = 48 }));
		print_queue(head);
		printf("\nenqueue: ");
		log(enqueue(head, (DATA ) { .sym = 'A' }));
		print_queue(head);
		printf("\ndequeue: ");
		log(dequeue(head));
		print_queue(head);
		printf("\npop: ");
		log(pop(head));
		print_queue(head);
		printf("\nfront: ");
		log(front(head));
		print_queue(head);
		printf("\ntop: ");
		log(top(head));
		print_queue(head);
		printf("\nback: ");
		log(back(head));
		print_queue(head);
	}

	puts("press any key..."); /* prints press any key... */
	return EXIT_SUCCESS;
}
