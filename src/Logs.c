/*	This file is part of C8E.
 *       
 *       C8E is free software: you can redistribute it and/or modify
 *       it under the terms of the GNU General Public License as published by
 *       the Free Software Foundation, either version 3 of the License, or
 *       (at your option) any later version.
 *       
 *       C8E is distributed in the hope that it will be useful,
 *              but WITHOUT ANY WARRANTY; without even the implied warranty of
 *              MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *              GNU General Public License for more details.
 *       
 *              You should have received a copy of the GNU General Public License
 *              along with C8E.  If not, see <http://www.gnu.org/licenses/>. 
 *
 *		Author : Maxime Gaudin
 */

#include "Logs.h"

#include <stdio.h>

int setupLogs() {
	output_filename	= DEFAULT_OUTPUT_FILENAME;
	debug_level = DEFAULT_DEBUG_LEVEL;

	output_file = fopen(output_filename, "a+");
	if(output_file == NULL) return 1;

	log_initialized = 1;
	return 0;
}

int setupLogs(unsigned char debugLevel) {
	output_filename	= DEFAULT_OUTPUT_FILENAME;
	debug_level = debugLevel;

	output_file = fopen(output_filename, "a+");
	if(output_file == NULL) return 1;

	log_initialized = 1;
	return 0;
}

int setupLogs(unsigned char debugLevel, char* outputFilename) {
	output_filename	= outputFilename;
	debug_level = debugLevel;

	output_file = fopen(output_filename, "a+");
	if(output_file == NULL) return 1;

	log_initialized = 1;
	return 0;
}

int closeLogs() {
	return (fclose(output_file) == EOF) ? 1 : 0;
}

void addEntry(DEBUG_LEVELS level, const char* const message) {
	if(level <= debug_level) {
		fprintf(output_file, "[DEBUG] %s\n", message);
	}
}
