//  Constant.cpp
//  Constant support for Win32 Perl extensions
//  (c) Dave Roth
//  Courtesy of Roth Consulting
//  http://www.roth.net/
//
//  Available under the GNU license.
//  2000.03.19

#define WIN32_LEAN_AND_MEAN

#ifdef __BORLANDC__
typedef wchar_t wctype_t; /* in tchar.h, but unavailable unless _UNICODE */
#endif
 
#include <windows.h>
#include <tchar.h>
#include <wtypes.h>
#include <stdio.h>      //  Gurusamy's right, Borland is brain damaged!
#include <math.h>       //  Gurusamy's right, MS is brain damaged!
#include <mstask.h>
#include <msterr.h>

#include "constant.h" 

static DWORD gdwConstTotal = 0;
static ConstantStruct gsConst[] =
{
    //  Scheduled Work Item flags from the IScheduledWorkItem interface
    { TEXT( "TASK_FLAG_INTERACTIVE" ),                          (LPVOID) (TASK_FLAG_INTERACTIVE),                   Numeric },
    { TEXT( "TASK_FLAG_DELETE_WHEN_DONE" ),                     (LPVOID) (TASK_FLAG_DELETE_WHEN_DONE),              Numeric },
    { TEXT( "TASK_FLAG_DISABLED" ),                             (LPVOID) (TASK_FLAG_DISABLED),                      Numeric },
    { TEXT( "TASK_FLAG_HIDDEN" ),                               (LPVOID) (TASK_FLAG_HIDDEN),                        Numeric },
    { TEXT( "TASK_FLAG_RUN_ONLY_IF_LOGGED_ON" ),                (LPVOID) (TASK_FLAG_RUN_ONLY_IF_LOGGED_ON),         Numeric },
    { TEXT( "TASK_FLAG_START_ONLY_IF_IDLE" ),                   (LPVOID) (TASK_FLAG_START_ONLY_IF_IDLE),            Numeric },
    { TEXT( "TASK_FLAG_KILL_ON_IDLE_END" ),                     (LPVOID) (TASK_FLAG_KILL_ON_IDLE_END),              Numeric },
    { TEXT( "TASK_FLAG_RESTART_ON_IDLE_RESUME" ),               (LPVOID) (TASK_FLAG_RESTART_ON_IDLE_RESUME),        Numeric },
    { TEXT( "TASK_FLAG_DONT_START_IF_ON_BATTERIES" ),           (LPVOID) (TASK_FLAG_DONT_START_IF_ON_BATTERIES),    Numeric },
    { TEXT( "TASK_FLAG_KILL_IF_GOING_ON_BATTERIES" ),           (LPVOID) (TASK_FLAG_KILL_IF_GOING_ON_BATTERIES),    Numeric },
    { TEXT( "TASK_FLAG_RUN_IF_CONNECTED_TO_INTERNET" ),         (LPVOID) (TASK_FLAG_RUN_IF_CONNECTED_TO_INTERNET),  Numeric },
    
TASK_SUNDAY
TASK_MONDAY
TASK_TUESDAY
TASK_WEDNESDAY
TASK_THURSDAY
TASK_FRIDAY
TASK_SATURDAY
TASK_FIRST_WEEK
TASK_SECOND_WEEK
TASK_THIRD_WEEK
TASK_FOURTH_WEEK
TASK_LAST_WEEK
TASK_JANUARY
TASK_FEBRUARY
TASK_MARCH
TASK_APRIL
TASK_MAY
TASK_JUNE
TASK_JULY
TASK_AUGUST
TASK_SEPTEMBER
TASK_OCTOBER
TASK_NOVEMBER
TASK_DECEMBER
TASK_FLAG_INTERACTIVE
TASK_FLAG_DELETE_WHEN_DONE
TASK_FLAG_DISABLED
TASK_FLAG_START_ONLY_IF_IDLE
TASK_FLAG_KILL_ON_IDLE_END
TASK_FLAG_DONT_START_IF_ON_BATTERIES
TASK_FLAG_KILL_IF_GOING_ON_BATTERIES
TASK_FLAG_RUN_ONLY_IF_DOCKED
TASK_FLAG_HIDDEN
TASK_FLAG_RUN_IF_CONNECTED_TO_INTERNET
TASK_FLAG_RESTART_ON_IDLE_RESUME
TASK_FLAG_SYSTEM_REQUIRED
TASK_TRIGGER_FLAG_HAS_END_DATE
TASK_TRIGGER_FLAG_KILL_AT_DURATION_END
TASK_TRIGGER_FLAG_DISABLED
TASK_MAX_RUN_TIMES


    //  Process priorities
    { TEXT( "REALTIME_PRIORITY_CLASS" ),                        (LPVOID) (REALTIME_PRIORITY_CLASS),                 Numeric },
    { TEXT( "HIGH_PRIORITY_CLASS" ),                            (LPVOID) (HIGH_PRIORITY_CLASS),                     Numeric },
    { TEXT( "NORMAL_PRIORITY_CLASS" ),                          (LPVOID) (NORMAL_PRIORITY_CLASS),                   Numeric },
    { TEXT( "IDLE_PRIORITY_CLASS" ),                            (LPVOID) (IDLE_PRIORITY_CLASS),                     Numeric },
    
    //  MaxRunTime 
    { TEXT( "INFINITE" ),                                       (LPVOID) (INFINITE),                                Numeric },    

//    { TEXT( "" ),           (LPVOID) (),    Numeric },

        // Terminating structure. Leave this here!
    { NULL,                                     (LPVOID) NULL,                              Numeric }
};

eConstantType Constant( LPTSTR pszConstant, LPVOID *ppBuffer )
{
    eConstantType eResult = NotDefined;
    DWORD dwIndex = 0;

    while( NULL != gsConst[ dwIndex ].m_Name )
    {
        if( NULL == gsConst[ dwIndex ].m_Name )
        {
            break;
        }

        if( *pszConstant == *gsConst[ dwIndex ].m_Name )
        {
            int iResult = _tcsicmp( gsConst[ dwIndex ].m_Name, pszConstant );
            if( 0 == iResult )
            {
                *ppBuffer = gsConst[ dwIndex ].m_pBuffer;
                eResult = gsConst[ dwIndex ].m_eType;
                break;
            }
            /*
                //  This code segment is commented out so that we don't run into 
                //  the problem of a constant being out of alpha order hence not
                //  resolving.
            else if( 0 < iResult )
            {
                    //  We have passed the spot where this constant
                    //  *should* have been if it were in alpha order
                break;
            }
            */
        }
        dwIndex++;
    }
    return( eResult );
}

LPTSTR GetConstantName( DWORD dwIndex )
{
    LPTSTR pszBuffer = NULL;
    if( gdwConstTotal > dwIndex )
    {
        pszBuffer = gsConst[ dwIndex ].m_Name;
    }
    return( pszBuffer );
}

DWORD GetTotalConstants()
{
    return( gdwConstTotal );
}

void CountConstants()
{
   gdwConstTotal = 0;
   while( NULL != gsConst[ gdwConstTotal++ ].m_Name ){};  
}

/*
void LogToFile( LPTSTR pszMessage )
{
    if( ghLogFile )
    {
        DWORD dwWritten = 0;
        DWORD dwBufferSize = 0;
        TCHAR szBuffer[ 256 ];
        SYSTEMTIME Time;
        GetLocalTime( &Time );
        wsprintf( szBuffer, TEXT( "[%04d.%02d.%02d %d:%02d:%02d] %s\n" ), 
                Time.wYear,
                Time.wMonth,
                Time.wDay,
                Time.wHour,
                Time.wMinute,
                Time.wSecond,
                (LPTSTR) pszMessage ); 

        dwBufferSize = lstrlen( szBuffer );
        WriteFile( ghLogFile, 
                    (LPCVOID) (szBuffer),
                    dwBufferSize, 
                    &dwWritten, 
                    NULL );
    }
}
*/
