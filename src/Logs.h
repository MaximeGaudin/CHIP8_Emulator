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

enum DEBUG_LEVELS { ERROR = 0, WARNING = 1, DRAWING = 2, DISASSEMBLING = 3 };

static int log_initialized = 0;

#define DEFAULT_DEBUG_LEVEL 1
static unsigned char debug_level;

#define DEFAULT_OUTPUT_FILE "DEBUG_LOGS"
static char* output_file;

void setupLogs();
void setupLogs(unsigned char debugLevel);
void setupLogs(unsigned char debugLevel, char* outputFile);

void closeLogs();

void addEntry(DEBUG_LEVELS level, const char* const message);
