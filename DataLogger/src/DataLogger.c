/*
 ============================================================================
 Name        : DataLogger.c
 Author      : ibsz
 Version     : v 1.0
 Copyright   : LGPL
 Description : Data Logger in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "iniparser.h"

int main(void) {
	// read ini file
	SLIST_HEADER* ini_list = ini_parse_file("dataLogger.ini");
	//print_list(ini_list, ini_section_formater);

	char sysCallString[256];
	char* url = get_key(ini_list, "dataSource", "url");
	char* filename = get_key(ini_list, "dataSource", "filename");

	// setup and call wget
	sprintf(sysCallString, "wget %s -O %s", url, filename);
	system(sysCallString);

	// open file
	FILE* file = fopen(filename, "r");
	if (file != NULL) {
		char buff[256];
		char **header = NULL;

		// get data from ini for parsing the records
		char* city = get_key(ini_list, "content", "city");
		char* cityColumnName = get_key(ini_list, "content", "cityColumnName");
		char* dateColumnName = get_key(ini_list, "content", "dateColumnName");
		char* timeColumnName = get_key(ini_list, "content", "timeColumnName");
		char* maxTemperatureColumnName = get_key(ini_list, "content",
				"maxTemperatureColumnName");
		char* minTemperatureColumnName = get_key(ini_list, "content",
				"minTemperatureColumnName");

		int cityColumn = -1;
		int dateColumn = -1;
		int timeColumn = -1;
		int maxTemperatureColumn = -1;
		int minTemperatureColumn = -1;

		while (fgets(buff, sizeof(buff), file)) {
			//printf("line: %s", buff);
			int length = countCharInStr(buff, ';');
			char** split = strSplit(buff, ';');
			if (header == NULL) {
				// parse header for columns
				header = split;
				cityColumn = indexOfStr(header, length, cityColumnName);
				dateColumn = indexOfStr(header, length, dateColumnName);
				timeColumn = indexOfStr(header, length, timeColumnName);
				maxTemperatureColumn = indexOfStr(header, length,
						maxTemperatureColumnName);
				minTemperatureColumn = indexOfStr(header, length,
						minTemperatureColumnName);
				continue;
			}
			// search record for city
			if(strcmp(split[cityColumn], city) == 0){
				// print parsed data from matching record
				printf("\tcity: %s\n\tdate: %s\n\ttime: %s\n\tmin: %s\n\tmax: %s\n",
					split[cityColumn], split[dateColumn], split[timeColumn],
					split[minTemperatureColumn], split[maxTemperatureColumn]);
				// TODO do something with the found data
			}

		}
		// close file
		fclose(file);
	}

	puts("press any key..."); /* prints press any key... */
	return EXIT_SUCCESS;
}
