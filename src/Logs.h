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
#include <stdio.h>

enum DEBUG_LEVELS { ERROR = 0, WARNING = 1, DRAWING = 2, DISASSEMBLING = 3 };

/// @brief Indicate whether or not log system is initialized.
static int log_initialized = 0;

/// @brief Specifies teh default debug level : Warning
#define DEFAULT_DEBUG_LEVEL 1

/// @brief Variable containing the current debug_level.
static unsigned char debug_level;

/// @brief Specifies the default output filename, i.e. the file where log will be written.
#define DEFAULT_OUTPUT_FILENAME "DEBUG_LOGS"

/// @brief Variable containing the current output filename.
static char* output_filename;

/// @brief Variable containing the current output file descriptor.
static FILE* output_file;

/**
  * @brief Setup output log file and debug level to values passed in paramaters. Moreover, a file descriptor is created and initialized.
  * @return 0 if success, 0 otherwise.
  */
int setupLogs(unsigned char debugLevel, char* const outputFilename);

/**
  * @brief Close output log file descriptor and flush file buffer.
  * @return 0 if success, 0 otherwise.
  */
int closeLogs();

/**
  * @brief Add new entry in output log file if [level] is below or equal to debug level.
  */
void addEntry(unsigned char level, const char* const message);
