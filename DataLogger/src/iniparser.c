/*
 ============================================================================
 Name        : iniparser.c
 Author      : ibsz
 Version     : v 1.1
 Copyright   : LGPL
 Description : ini file parser in C, Ansi-style
 Release Note: trimwhitespace() moved to stringutils.h
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iniparser.h"
#include "stringutils.h"

int verbose = 0;

void log(char* info, char* msg){
	if(verbose == 1) printf(">>pars ini<<\t%s\t%s\n", info, msg);
}

void ini_tuple_formater(INI_TUPLE *data) {
	if (data != NULL) {
		printf("\tkey: %s\tvalue: %s\n", data->key, data->value);
	}
}

void ini_section_formater(INI_SECTION *sec) {
	if (sec != NULL) {
		printf("Section: %s\n", sec->section);
		print_list(sec->ptuple, ini_tuple_formater);
	}
}



char* substring(char* str, int start, int end) {
	int length = end - start;
	char* subbuff = malloc(sizeof(char) * length + 1);
	memcpy(subbuff, &str[start], length);
	subbuff[length] = '\0';
	return subbuff;
}

char* parseSection(char *line){
	int start = strcspn(line, "[");
	int end = strcspn( line, "]");
	if(start >= 0 && end > 0 && start < end){
		return substring(line, start+1, end);
	}
	return NULL;
}

INI_TUPLE* parseTuple(char *line){
	int separator = strcspn(line, "=");
	if(separator > 0){
		INI_TUPLE *tuple = malloc(sizeof(INI_TUPLE));
		if(tuple == 0) return NULL;
		tuple->key = substring(line, 0, separator);
		tuple->value = substring(line, separator+1, strlen(line));
		log("createKey", tuple->key);
		log("\tvalue", tuple->value);
		return tuple;
	}
	return NULL;
}

INI_SECTION* createSection(SLIST_HEADER* section_list, char *secName){
	if(section_list == NULL || secName == NULL) return NULL;
	log("createSection", secName);
	INI_SECTION *sec = malloc(sizeof(INI_SECTION));
	SLIST_HEADER *list = malloc(sizeof(SLIST_HEADER));

	if(sec == NULL || list == NULL) return NULL;
	sec->section = secName;
	sec->interval = 0;
	sec->action = NULL;
	sec->ptuple = list;
	list->count = 0;
	list->first = NULL;
	list->last = NULL;
	return sec;
}

SLIST_HEADER* ini_parse_file(char *filename) {
	FILE *file;
	log("parse file", filename);
	file = fopen(filename, "r");
	if (file) {
		// create List to store data
		SLIST_HEADER* section_list = malloc(sizeof(SLIST_HEADER));
		if (section_list != NULL) {
			section_list->count = 0;
			section_list->first = NULL;
			section_list->last = NULL;

			INI_SECTION *current = NULL;

			// read from file to list
			char buff[256];
			while (fgets(buff, sizeof(buff), file)) {
				char *line = trimwhitespace(buff);

				if(strlen(line) == 0){
					log("skip empty line", line);
					continue;
				}
				// if line is section -> create section
				char *secName = parseSection(line);
				if(secName != NULL){
					current = createSection(section_list, secName);
					add(section_list, current);
					continue;
				}
				// if line is key/value pair -> create tuple
				INI_TUPLE *tuple =parseTuple(line);
				if(tuple != NULL){
					add(current->ptuple, tuple);
					continue;
				}
				log("could not parse line: %s", line);
			}
		}
		fclose(file);
		return section_list;
	}else{
		log("file not found", filename);
	}
	return NULL;
}

INI_SECTION* find_section(SLIST_HEADER* root, char *section) {
	if (root == NULL || section == NULL || root->first == NULL)
		return NULL;
	SLIST_ITEM *current = root->first;
	int i = 0;
	for (; i < root->count; i++) {
		INI_SECTION *data = current->data;
		if (strcmp(data->section, section) == 0) {
			return data;
		}
		current = current->next;
	}
	return NULL;
}

INI_TUPLE* find_key(INI_SECTION *section, char *key) {
	if (section == NULL || key == NULL)
		return NULL;
	SLIST_HEADER *list = section->ptuple;
	SLIST_ITEM *current = list->first;
	int i = 0;
	for (; i < list->count; i++) {
		INI_TUPLE *data = current->data;
		if (strcmp(data->key, key) == 0) {
			return data;
		}
		current = current->next;
	}
	return NULL;
}

char* get_key(SLIST_HEADER* root, char *section, char *key) {
	if (root == NULL || section == NULL || key == NULL || root->first == NULL)
		return NULL;
	INI_SECTION *sec = find_section(root, section);
	if (sec == NULL)
		return NULL;
	INI_TUPLE *tuple = find_key(sec, key);
	if (tuple != NULL) {
		return tuple->value;
	}
	return NULL;
}
