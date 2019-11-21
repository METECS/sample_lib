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
** File: ut_sample_lib.c
**
** Purpose:
** Code Unit from SAMPLE library tuned for unit testing
**
** Notes:
** This duplicates a source code unit from the main FSW,
** but adds additional "scaffolding" around the FSW so it can be
** tested.  This includes:
**  - A "replacements" file that can define macros that redirect
**    system calls to other versions.
**  - Implementation of any "accessor" methods that allow the
**    UT test cases to access private data structures within
**    the code unit.
** Also, unlike the FSW code,  this module should be compiled with
** coverage instrumentation flags if the toolchain supports it
** (i.e. -pg --coverage on gcc).  It is also compiled with an
** alternate include path, such that locally-provided "overrides"
** of header files will take precedence over include files of the
** same name.
**
** The "replacements" allows for alternate versions of functions
** to be selected at _compile-time_ rather than at _link-time_ as
** is normally done with stub libraries.
**
** Note that link-time replacement is preferable for many reasons,
** it is simpler and more robust, as it keeps the stubs with the
** library that supplies the main code.  However, it may not always
** be possible, particularly when it is a C library call that needs
** to be stubbed out.
**
** Rather than relying on a platform specific solution (LD_PRELOAD, etc)
** to trigger an alternate version of the library call, this simply
** uses #define's to re-map that function name to a different name, for
** which a matching stub is provided locally.
*/

#include "sample_lib_ut_replacements.h"
#include "ut_sample_lib.h"

/*
 * After the UT scaffolding, include the FSW source file directly
 */
#include "sample_lib.c"


/*
 * A UT-specific "accessor" that can access local static structures
 *
 * This provides a means for UT to test data structures without making
 * them externally visible.
 */
char* UT_SampleLib_GetInternalBuffer(void)
{
    return SAMPLE_Buffer;
}
