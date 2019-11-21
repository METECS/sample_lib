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
** File: ut_sample_lib.h
**
** Purpose:
** Extra scaffolding functions for the sample_lib unit test
**
** Notes:
** This is simply defining an extra UT-specific accessor function
** to obtain a pointer to a private internal (static) data structure
**
** UT often needs to modify internal data structures in ways that
** actual applications never would (bypassing the normal API) in
** order to exercise or set up for off-nominal cases.
*/

#ifndef _UT_SAMPLE_LIB_H_
#define _UT_SAMPLE_LIB_H_


/*
 * UT-specific function to access the internal (static) data buffer.
 * Demonstrates how UT can access symbols that are not externally visible.
 */
char* UT_SampleLib_GetInternalBuffer(void);



#endif /* _UT_SAMPLE_LIB_H_ */

