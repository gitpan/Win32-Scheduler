#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <initguid.h>
#include <ole2.h>
#include <mstask.h>
#include <msterr.h>
#include <wtypes.h>
#include <tchar.h>

#ifdef __BORLANDC__
typedef wchar_t wctype_t; /* in tchar.h, but unavailable unless _UNICODE */
#endif

#include <stdio.h>      //  Gurusamy's right, Borland is brain damaged!
#include <math.h>       //  Gurusamy's right, MS is brain damaged!

#define MYWORD_TEMP WORD

//  If we are building with the core distribution headers we can not define
//  the function names using C++ because of name mangling
#if defined(__cplusplus) && !defined(PERL_OBJECT)
extern "C" {
#endif
    #include "EXTERN.h"
    #include "perl.h"
    #include "XSub.h"

#if defined(__cplusplus) && !defined(PERL_OBJECT)
}
#endif


#ifdef WORD
    #undef WORD
    #define WORD MYWORD_TEMP
#endif // WORD

#include "constant.h"
#include "CUString.hpp"
#include "Scheduler.hpp"

#include "TIE_Scheduler.xpp"
#include "TIE_Task.xpp"

/*----------------------- M I S C   F U N C T I O N S -------------------*/

DWORD FindSubString( LPTSTR pszString, LPTSTR pszSubString )
{
    TCHAR tChar;
    DWORD dwCount = 0;
    DWORD dwSubLength = _tcslen( pszSubString );

    while( '\0' != pszString[0] )
    {
        dwCount++;
        if( _tolower( pszString[0] ) == _tolower( pszSubString[0] ) )
        {

            if( 0 == _tcsnicmp( pszString, pszSubString, dwSubLength ) )
            {
                return( dwCount );
            }
        }
        pszString++;
    }
    return( 0 );
}

/*----------------------- P E R L   F U N C T I O N S -------------------*/
//////////////////////////////////////////////////////////////////
XS( XS_WIN32__Scheduler_Constant )
{
    dXSARGS;
    EXTENSION_VARS;
    char *pszName = NULL;
    LPVOID pBuffer = NULL;
    DWORD dwValue;
    eConstantType eResult;

    if( 2 != items )
    {
        croak( "Usage: " EXTENSION "::Constant( $Name, $Arg )\n" );
    }

    pszName = (char*) SvPV( ST( 0 ), na );

    eResult = Constant( pszName, &pBuffer );
    switch( eResult )
    {
        case String:
            sv_setpv( ST( 1 ), (char*) pBuffer );
            break;

        case Numeric:
            sv_setiv( ST( 1 ), (IV) pBuffer );
            break;
    }

        //  Return the result type.
    PUSH_IV( eResult );


    EXTENSION_RETURN;
}


//////////////////////////////////////////////////////////////////
XS( XS_Win32__Scheduler_QueryInterface )
{
    dXSARGS;
    EXTENSION_VARS;
    DWORD dwResult = 0;
    ITaskScheduler *pITS = NULL;

    if( 1 != items )
    {
        croak( TEXT( "Usage: " EXTENSION "::QueryInterface()\n" ) );
    }

    pITS = (ITaskScheduler *) HASH_GET_IV( EXTRACT_HV( ST( 0 ) ), KEYWORD_SCHEDULER_INTERFACE );
    if( NULL != pITS )
    {
        PUSH_IV( pITS );
    }

    EXTENSION_RETURN;
}

//////////////////////////////////////////////////////////////////
XS( XS_Win32__Scheduler_Task_QueryInterface )
{
    dXSARGS;
    EXTENSION_VARS;
    DWORD dwResult = 0;
    ITask *pTask = NULL;

    if( 1 != items )
    {
        croak( TEXT( "Usage: " EXTENSION "::QueryInterface()\n" ) );
    }

    pTask = (ITask *) HASH_GET_IV( EXTRACT_HV( ST( 0 ) ), KEYWORD_TASK_INTERFACE );
    if( NULL != pTask )
    {
        PUSH_IV( pTask );
    }

    EXTENSION_RETURN;
}

//////////////////////////////////////////////////////////////////
XS( XS_WIN32__Scheduler_Enum )
{
    dXSARGS;
    EXTENSION_VARS;
    DWORD dwTotal = 0;
    HV *pHv = NULL;

    if( 1 != items )
    {
        croak( TEXT( "Usage: " EXTENSION "::Enum( \\%List )\n" ) );
    }

    if( NULL != ( pHv = EXTRACT_HV( ST( 0 ) ) ) )
    {
        IEnumWorkItems *pIEnum;
        HRESULT hr = gpITS->Enum(&pIEnum);
        if( SUCCEEDED( hr ) )
        {
            /////////////////////////////////////////////////////////////////
            // Call IEnumWorkItems::Next to retrieve tasks. Note that 
            // this example tries to retrieve five tasks for each call.
            /////////////////////////////////////////////////////////////////
            LPWSTR *pszwNames;
            DWORD dwTasks = 0;
            DWORD dwTasksToFetch = TOTAL_TASKS_TO_RETRIEVE;
            while( SUCCEEDED( pIEnum->Next( dwTasksToFetch,
                                            &pszwNames,
                                            &dwTasks ) )
                                        && ( 0 != dwTasks ) )
            {
                CUString szuString;

                ///////////////////////////////////////////////////////////////
                // Process each task. Note that this example prints the 
                // name of each task to the screen.
                //////////////////////////////////////////////////////////////
                while( dwTasks )
                {
                    szuString = pszwNames[ --dwTasks ];
                    CoTaskMemFree( pszwNames[ dwTasks ] );

                    dwTotal++;
                    HASH_STORE_PV( pHv, KEYWORD_HASH_NAME, (LPTSTR) szuString );
                }
                CoTaskMemFree( pszwNames );
            }
            pIEnum->Release();
        }
    }

    PUSH_IV( dwTotal );
    EXTENSION_RETURN;
}


//////////////////////////////////////////////////////////////////
XS( boot_Win32__Scheduler )
{
    dXSARGS;
    EXTENSION_VARS;
    LPTSTR file = __FILE__;
    int retcode = 1;

    XS_VERSION_BOOTCHECK ;

    newXS( EXTENSION "::Constant",              XS_WIN32__Scheduler_Constant, file );
    newXS( EXTENSION "::Enum",                  XS_WIN32__Scheduler_Enum, file );

    newXS( EXTENSION  "::TIEHASH",	            XS_Win32__Scheduler_TIE_HASH, file);
	newXS( EXTENSION  "::FETCH",		        XS_Win32__Scheduler_TIE_FETCH, file);
	newXS( EXTENSION  "::STORE",		        XS_Win32__Scheduler_TIE_STORE, file);
	newXS( EXTENSION  "::FIRSTKEY", 	        XS_Win32__Scheduler_TIE_FIRSTKEY, file);
	newXS( EXTENSION  "::NEXTKEY",  	        XS_Win32__Scheduler_TIE_NEXTKEY, file);
	newXS( EXTENSION  "::EXISTS",		        XS_Win32__Scheduler_TIE_EXISTS, file);
	newXS( EXTENSION  "::CLEAR",		        XS_Win32__Scheduler_TIE_CLEAR, file);
	newXS( EXTENSION  "::DELETE",		        XS_Win32__Scheduler_TIE_DELETE, file);
	newXS( EXTENSION  "::DESTROY",	            XS_Win32__Scheduler_TIE_DESTROY, file);
	newXS( EXTENSION  "::QueryInterface",	    XS_Win32__Scheduler_QueryInterface, file);


//    newXS( EXTENSION  "::Task::TIEHASH",	    XS_Win32__Scheduler_Task_TIE_HASH, file);
	newXS( EXTENSION  "::Task::FETCH",		    XS_Win32__Scheduler_Task_TIE_FETCH, file);
	newXS( EXTENSION  "::Task::STORE",		    XS_Win32__Scheduler_Task_TIE_STORE, file);
	newXS( EXTENSION  "::Task::FIRSTKEY", 	    XS_Win32__Scheduler_Task_TIE_FIRSTKEY, file);
	newXS( EXTENSION  "::Task::NEXTKEY",  	    XS_Win32__Scheduler_Task_TIE_NEXTKEY, file);
	newXS( EXTENSION  "::Task::EXISTS",		    XS_Win32__Scheduler_Task_TIE_EXISTS, file);
//  newXS( EXTENSION  "::Task::CLEAR",		    XS_Win32__Scheduler_Task_TIE_CLEAR, file);
    newXS( EXTENSION  "::Task::DELETE",		    XS_Win32__Scheduler_Task_TIE_DELETE, file);
    newXS( EXTENSION  "::Task::DESTROY",	    XS_Win32__Scheduler_Task_TIE_DESTROY, file);
    newXS( EXTENSION  "::Task::QueryInterface",	XS_Win32__Scheduler_Task_QueryInterface, file);
    
    XSRETURN_YES;
}



/* ===============  DLL Specific  Functions  ===================  */

//////////////////////////////////////////////////////////////////
BOOL WINAPI DllMain( HINSTANCE  hinstDLL, DWORD fdwReason, LPVOID  lpvReserved )
{
    BOOL    fResult = TRUE;
    HRESULT hr = ERROR_SUCCESS;

    switch( fdwReason )
    {
        case DLL_PROCESS_ATTACH:

            gdwThread = 1;

            ghDLL = hinstDLL;
            CountConstants();

            hr = CoInitialize( NULL );
            if ( SUCCEEDED( hr ) )
            {
                hr = CoCreateInstance( CLSID_CTaskScheduler,
                                        NULL,
                                        CLSCTX_INPROC_SERVER,
                                        IID_ITaskScheduler,
                                        (void **) &gpITS );
                if( FAILED( hr ) )
                {
                    CoUninitialize();
                    fResult = FALSE;
                }
            }
            break;

        case DLL_THREAD_ATTACH:
            gdwThread++;
            break;

        case DLL_THREAD_DETACH:
            gdwThread--;
            break;

        case DLL_PROCESS_DETACH:
            gpITS->Release();
            CoUninitialize();
            break;

        default:
            break;
    }
    return( fResult );
}

