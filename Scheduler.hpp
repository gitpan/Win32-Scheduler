//  Scheduler.cpp
//  Header for the Win32::Scheduler Perl extension.
//  (c) Dave Roth
//  Courtesy of Roth Consulting
//  http://www.roth.net/
//
//  2000.07.01

#include "Win32Perl.h"

#ifndef _SCHEDULER_H_
#   define _SCHEDULER_H_
#   ifndef WIN32
#       ifdef _WIN32
#           define WIN32   
#       endif // _WIN32  
#   endif // WIN32  
  
///////////////////////////////////////////////////////////////////////////////////////////
//  Begin resource compiler macro block

    //  Include the version information...
    #include "version.h"

    #define EXTENSION_NAME          "Scheduler"

    #define EXTENSION_PARENT_NAMESPACE      "Win32"
    #define EXTENSION               EXTENSION_PARENT_NAMESPACE "::" EXTENSION_NAME
    
    #define EXTENSION_FILE_NAME     EXTENSION_NAME

    #define EXTENSION_VERSION       VERSION
    #define EXTENSION_AUTHOR        "Dave Roth <rothd@roth.net>"

    #define COPYRIGHT_YEAR          "2000"
    #define COPYRIGHT_NOTICE        "Copyright (c) " COPYRIGHT_YEAR

    #define COMPANY_NAME            "Roth Consulting\r\nhttp://www.roth.net/consult"

    #define VERSION_TYPE            "Beta"
//  End resource compiler macro block
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//  These are members that will be defined in the blessed Perl Object.
//  These are only intended to be used by this extension (and maybe it's
//  brethern). I would not suggest other applications rely on this since it
//  may change.

#define KEYWORD_SCHEDULER_INTERFACE TEXT( "scheduler_interface" )
#define KEYWORD_TASK_INTERFACE      TEXT( "task_interface" )
#define KEYWORD_HASH_NAME           TEXT( "name" )

#define KEYWORD_JOB_ACCOUNT         TEXT( "account" )
#define KEYWORD_JOB_PASSWORD        TEXT( "password" )
#define KEYWORD_JOB_COMMENT         TEXT( "comment" )
#define KEYWORD_JOB_CREATOR         TEXT( "creator" )
#define KEYWORD_JOB_RETRY_COUNT     TEXT( "retry_count" )
#define KEYWORD_JOB_RETRY_INTERVAL  TEXT( "retry_interval" )
#define KEYWORD_JOB_IDLE_MINUTES    TEXT( "idle_minutes" )
#define KEYWORD_JOB_DEADLINE_MINUTES TEXT( "deadline_minutes" )
#define KEYWORD_JOB_DATA            TEXT( "data" )
#define KEYWORD_JOB_APPLICATION     TEXT( "application" )
#define KEYWORD_JOB_EXIT_CODE       TEXT( "exit_code" )
#define KEYWORD_JOB_MAX_RUN_TIME    TEXT( "max_run_time" )
#define KEYWORD_JOB_FLAGS           TEXT( "flags" )
#define KEYWORD_JOB_DIRECTORY       TEXT( "directory" )
#define KEYWORD_JOB_PRIORITY        TEXT( "priority" )
#define KEYWORD_JOB_PARAMETERS      TEXT( "parameters" )
#define KEYWORD_JOB_LAST_RUN_TIME   TEXT( "last_run_time" )
#define KEYWORD_JOB_NEXT_RUN_TIME   TEXT( "next_run_time" )
#define KEYWORD_JOB_RUN_TIMES       TEXT( "run_times" )

#define INDEX_JOB_ACCOUNT           0x00
#define INDEX_JOB_PASSWORD          0x01
#define INDEX_JOB_COMMENT           0x02
#define INDEX_JOB_CREATOR           0x03
#define INDEX_JOB_RETRY_COUNT       0x04
#define INDEX_JOB_RETRY_INTERVAL    0x05
#define INDEX_JOB_IDLE_MINUTES      0x06
#define INDEX_JOB_DEADLINE_MINUTES  0x07
#define INDEX_JOB_DATA              0x08
#define INDEX_JOB_APPLICATION       0x09
#define INDEX_JOB_EXIT_CODE         0x0A
#define INDEX_JOB_MAX_RUN_TIME      0x0B
#define INDEX_JOB_FLAGS             0x0C
#define INDEX_JOB_DIRECTORY         0x0D
#define INDEX_JOB_PRIORITY          0x0E
#define INDEX_JOB_PARAMETERS        0x0F
#define INDEX_JOB_LAST_RUN_TIME     0x10
#define INDEX_JOB_NEXT_RUN_TIME     0x11
#define INDEX_JOB_RUN_TIMES         0x12

#define INDEX_JOB_BAD_ATTRIBUTE     0xFF

#define TOTAL_TASKS_TO_RETRIEVE     5
#define TOTAL_RUN_TIME_TO_FETCH     10

    ITaskScheduler *gpITS = NULL;
    HINSTANCE ghDLL = NULL;
    DWORD gdwThread = 0;

    SV *TieTask( PERL_OBJECT_PROTO ITask *pTask );
    SV *MakeMagicHash( PERL_OBJECT_PROTO SV* pSvBasedOn, LPTSTR pszNameSpace );
    HRESULT SaveTask( ITask *pTask );
    DWORD FindSubString( LPTSTR pszString, LPTSTR pszSubString );
    HRESULT ModifyTask( PERL_OBJECT_PROTO ITask *pTask, HV *pHv );
    DWORD SystemTimeToCTime( SYSTEMTIME *psTime );
#endif // _SCHEDULER_H_