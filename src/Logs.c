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

/// @brief Indicate whether or not log system is initialized.
static int log_initialized = 0;

/// @brief Variable containing the current debug_level.
static unsigned char debug_level;

/// @brief Variable containing the current output filename.
static char* output_filename;

/// @brief Variable containing the current output file descriptor.
static FILE* output_file;

int setupLogs(unsigned char debugLevel , char* const outputFilename ) {
	output_filename	= outputFilename;
	debug_level = debugLevel;

	output_file = fopen(output_filename, "a+");
	if(output_file == NULL) return 1;

	log_initialized = 1;
	return 0;
}

int closeLogs() {
	log_initialized = 0;
	return (fclose(output_file) == EOF) ? 1 : 0;
}

void addEntry(unsigned char level, const char* const message) {
	if(log_initialized) {
		if(level <= debug_level) {
			fprintf(output_file, "[DEBUG] %s\n", message);
		}
	}
}
