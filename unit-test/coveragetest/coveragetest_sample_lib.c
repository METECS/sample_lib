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
** File: coveragetest_sample_lib.c
**
** Purpose:
** Coverage Unit Test cases for the SAMPLE library
**
** Notes:
** This implements various test cases to exercise all code
** paths through all functions defined in the SAMPLE library.
**
** It is primarily focused at providing examples of the various
** stub configurations, hook functions, and wrapper calls that
** are often needed when coercing certain code paths through
** complex functions.
*/

/*
 * Includes
 */

#include "sample_lib_coveragetest_common.h"
#include <ut_sample_lib.h>

/*
 * This code needs to access the "override" stubs for string.h,
 * as well as the normal system string.h.  It is differentiated
 * by explicitly specifying the "overrides/" prefix here.
 */
#include <overrides/string.h>
#include <stdbool.h>
#include <stdarg.h>

char UT_TESTBUFFER[] = "SAMPLELIB_UT";

/*
 * Local test state structure
 */
typedef struct
{
    bool format_string_valid;
    bool printf_content_valid;

} SAMPLE_Function_TestState_t;


/*
 * A local helper (hook) function for the OS_printf stub provided by OSAL.
 * This confirms internal content of the format string and arguments.
 */
static int32 UT_printf_hook(void *UserObj, int32 StubRetcode, uint32 CallCount,
        const UT_StubContext_t *Context, va_list va)
{
    SAMPLE_Function_TestState_t *State = UserObj;

    /*
     * The OS_printf() stub passes format string as the argument
     * This confirms the whole string; normally this level of test
     * detail would not be needed, but this serves as an example
     * of how it can be done.
     */
    if (Context->ArgCount > 0 &&
            strcmp(Context->ArgPtr[0],
                    "SAMPLE_Function called, buffer=\'%s\'\n") == 0)
    {
        State->format_string_valid = true;

        /*
         * The remainder of the OS_printf() arguments are in the va_list
         * The first argument should be a pointer to the internal buffer,
         * which in this case should match the content of UT_TESTBUFFER
         * (because it was overridden as part of the init)
         */
        if (strcmp(va_arg(va, const char *), UT_TESTBUFFER) == 0)
        {
            State->printf_content_valid = true;
        }
    }

    return 0;
}



/*
**********************************************************************************
**          TEST CASE FUNCTIONS
**********************************************************************************
*/

void Test_SAMPLE_LibInit(void)
{
    /*
     * Test Case For:
     * int32 SAMPLE_LibInit( void )
     */

    /* Set a data buffer for strncpy()
     * This overriddes what it would normally do */
    UT_SetDataBuffer(UT_KEY(OCS_strncpy), UT_TESTBUFFER,
            sizeof (UT_TESTBUFFER), false);

    /* nominal case should return SUCCESS */
    UT_TEST_FUNCTION_RC(SAMPLE_LibInit(), CFE_SUCCESS);

    /* A simple confirmation that "OS_printf" was invoked
     * exactly 1 time during the previous function call  */
    UtAssert_True(UT_GetStubCount(UT_KEY(OS_printf)) == 1, "OS_printf called");

    /*
     * Test that the internal buffer contains the right thing
     * In this case, it is the locally-provided (override) content
     *
     * This requires use of the local accessor routine to get to the
     * internal buffer, which is declared "static"
     */
    UtAssert_StrCmp(UT_TESTBUFFER, UT_SampleLib_GetInternalBuffer(),
            "Internal buffer content valid");

    /* Test failure of the underlying library call */
    UT_SetForceFail(UT_KEY(OCS_strncpy), -1);

    /* off-nominal case should return CFE_STATUS_NOT_IMPLEMENTED */
    UT_TEST_FUNCTION_RC(SAMPLE_LibInit(), CFE_STATUS_NOT_IMPLEMENTED);
}

void Test_SAMPLE_Function(void)
{
    /*
     * Test Case For:
     * void SAMPLE_Function( void )
     */
    SAMPLE_Function_TestState_t state;

    /*
     * This function has no conditionals, but it does call
     * OS_printf with a string.  This can be tested in UT.
     */
    memset(&state, 0, sizeof(state));
    UT_SetVaHookFunction(UT_KEY(OS_printf), UT_printf_hook, &state);

    /*
     * Invoke the actual function
     */
    SAMPLE_Function();

    /*
     * Make sure that the extra conditions checked by the
     * hook function were satisfied
     */
    UtAssert_True(state.format_string_valid, "OS_printf format string test");
    UtAssert_True(state.printf_content_valid, "OS_printf content test");
}



/*
 * Setup function prior to every test
 */
void Sample_UT_Setup(void)
{
    UT_ResetState(0);
}

/*
 * Teardown function after every test
 */
void Sample_UT_TearDown(void)
{

}


/*
 * Register the test cases to execute with the unit test tool
 */
void OS_Application_Startup(void)
{
    ADD_TEST(SAMPLE_LibInit);
    ADD_TEST(SAMPLE_Function);
}





