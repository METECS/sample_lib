/*
**  GSC-18128-1, "Core Flight Executive Version 6.6"
**
**  Copyright (c) 2006-2019 United States Government as represented by
**  the Administrator of the National Aeronautics and Space Administration.
**  All Rights Reserved.
**
**  Licensed under the Apache License, Version 2.0 (the "License");
**  you may not use this file except in compliance with the License.
**  You may obtain a copy of the License at
**
**    http://www.apache.org/licenses/LICENSE-2.0
**
**  Unless required by applicable law or agreed to in writing, software
**  distributed under the License is distributed on an "AS IS" BASIS,
**  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**  See the License for the specific language governing permissions and
**  limitations under the License.
*/

/*
** File: sample_lib_ut_replacements.h
**
** Purpose:
** Demonstrates the concept of compile-time replacement
** for C library calls.
**
** Notes:
** For most Unit tests this is _NOT_ necessary.  Whenever
** possible, FSW code should only call CFE/OSAL/PSP code for
** which there are already stubs available and the the
** replacements can be made transparently at link time.
**
** However, in some circumstances, in particular when it
** is a C library function that needs modification, it is
** necessary to divert/replace the call to a stub at
** compile-time rather than at link time.
**
** To handle this situation, this file #define's macros
** to replace these C library calls with alternate versions
** by leveraging the C preprocessor.
*/

#ifndef _SAMPLE_LIB_UT_REPLACEMENTS_H_
#define _SAMPLE_LIB_UT_REPLACEMENTS_H_

/*******************************************************************************
 * OCS FUNCTION MAPPINGS for APIs normally supplied by libc headers
 *******************************************************************************/

/*
 * Override a libc function with a local version.
 * This is mainly to demonstrate the concept.
 *
 * This causes the all subsequent calls to the "strncpy()"
 * function to call "OCS_strncpy()" instead, where OCS_strncpy
 * is a locally-provided stub routine.
 *
 * NOTE: a local stub copy of "string.h" must also be provided, as
 * this will interfere with the definition in the system file.
 */
#define strncpy                   OCS_strncpy

#endif /* _SAMPLE_LIB_UT_REPLACEMENTS_H_ */
