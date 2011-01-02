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

/**
 * @file CPU.h
 * @brief
 * @version 0.1
 * @date December 12, 2010
 * @author Maxime Gaudin
 */

#ifndef CPU_HEADER
#define CPU_HEADER

/** @brief Define the maximum stack size, i.e. the maximum amount of subroutine calls. **/
#define MAX_STACK_SIZE 0xF

int setupCPU();

void cleanupCPU();

#endif /* CPU_HEADER */
