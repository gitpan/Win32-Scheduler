
typedef struct _TASK_ATTRIBUTE
{
    LPTSTR m_pszAttribute;
    int    m_iIndex;
} TASK_ATTRIBUTE;

static TASK_ATTRIBUTE *spTaskAttributes[] =
{
    {   KEYWORD_JOB_ACCOUNT,            INDEX_JOB_ACCOUNT             },
    {   KEYWORD_JOB_PASSWORD,           INDEX_JOB_PASSWORD            },
    {   KEYWORD_JOB_COMMENT,            INDEX_JOB_COMMENT             },
    {   KEYWORD_JOB_CREATOR,            INDEX_JOB_CREATOR             },
    {   KEYWORD_JOB_RETRY_COUNT,        INDEX_JOB_RETRY_COUNT         },
    {   KEYWORD_JOB_RETRY_INTERVAL,     INDEX_JOB_RETRY_INTERVAL      },
    {   KEYWORD_JOB_IDLE_MINUTES,       INDEX_JOB_IDLE_MINUTES        },
    {   KEYWORD_JOB_DEADLINE_MINUTES,   INDEX_JOB_DEADLINE_MINUTES    },
    {   KEYWORD_JOB_DATA,               INDEX_JOB_DATA                },
    {   KEYWORD_JOB_APPLICATION,        INDEX_JOB_APPLICATION         },
    {   KEYWORD_JOB_EXIT_CODE,          INDEX_JOB_EXIT_CODE           },
    {   KEYWORD_JOB_MAX_RUN_TIME,       INDEX_JOB_MAX_RUN_TIME        },
    {   KEYWORD_JOB_FLAGS,              INDEX_JOB_FLAGS               },
    {   KEYWORD_JOB_DIRECTORY,          INDEX_JOB_DIRECTORY           },
    {   KEYWORD_JOB_PRIORITY,           INDEX_JOB_PRIORITY            },
    {   KEYWORD_JOB_PARAMETERS,         INDEX_JOB_PARAMETERS          },

    {   NULL,                           INDEX_JOB_BAD_ATTRIBUTE       }
};

///////////////////////////////////////////////////////////////////////
//	
DWORD GetAttributeIndex( LPCTSTR pszAttribute )
{
    DWORD dwIndex = 0;
    TASK_ATTRIBUTE pTaskAttribute = szTaskAttributes[ dwIndex ];

    while( NULL != pTaskAttribute.m_pszAttribute )
    {
        if( 0 == _tcsicmp( pTaskAttribute.m_pszAttribute, pszAttribute ) )
        {
            return( dwIndex );
        }
        pTaskAttribute = spTaskAttributes[ ++dwIndex ];
    }
    return( INDEX_JOB_BAD_ATTRIBUTE );
}


///////////////////////////////////////////////////////////////////////
//	
XS(XS_Win32__Scheduler_Task_TIE_FETCH)
{
	dXSARGS;
	EXTENSION_VARS;
    HV		*pHvSelf;
    ITask   *pTask = NULL;
    HRESULT hr = ERROR_SUCCESS;
    DWORD dwTotal = 0;
    BOOL fResult = FALSE;
	LPTSTR pszName = NULL;
    SV *pSvResult = NULL;
		
	if (items != 2)
	{
		croak("Usage: " EXTENSION  "::Task::TIEFETCH( $Self, $Key )\n");
    }
		
    //	FETCH	
	pHvSelf = (HV*) SvRV( ST( 0 ) );
    pszName = SvPV( ST( 1 ), na );
	
    pTask = (ITask *) HASH_GET_IV( pHvSelf, INDEX_TASK_INTERFACE );
    if( NULL != pTask )
    {
        CUString szuBuffer( pszName );
        LPTSTR pszAttributeKeyName = NULL;
        LPTSTR pszBuffer = NULL;
        DWORD dwBuffer = 0;
        WORD  wBuffer = 0;
        enum { Unknown, String, Dword } eValueType Unknown;

        switch( GetAttributeIndex( pszName ) )
        {
        
            case INDEX_JOB_ACCOUNT:
                if( SUCCEEDED( pTask->GetAccountInformation( &pszBuffer ) ) )
                {
                    szuBuffer = pszBuffer;
                    pszAttributeKeyName = KEYWORD_JOB_ACCOUNT;
                    CoTaskMemFree ( pszBuffer );
                    eValueType = String;
                }
                break;

            case INDEX_JOB_PASSWORD:
                break;

            case INDEX_JOB_COMMENT:
                if( SUCCEEDED( pTask->GetComment( &pszBuffer ) ) )
                {
                    szuBuffer = pszBuffer;
                    pszAttributeKeyName = KEYWORD_JOB_COMMENT;
                    CoTaskMemFree ( pszBuffer );
                    eValueType = String;
                }
                break;

            case INDEX_JOB_CREATOR:
                if( SUCCEEDED( pTask->GetCreator( &pszBuffer ) ) )
                {
                    szuBuffer = pszBuffer;
                    pszAttributeKeyName = KEYWORD_JOB_CREATOR;
                    CoTaskMemFree ( pszBuffer );
                    eValueType = String;
                }
                break;

            case INDEX_JOB_RETRY_COUNT:
                if( SUCCEEDED( pTask->GetErrorRetryCount( &wBuffer ) ) )
                {
                    pszAttributeKeyName = KEYWORD_JOB_RETRY_COUNT;
                    dwBuffer = wBuffer;
                    eValueType = Dword;
                }
                break;

            case INDEX_JOB_RETRY_INTERVAL:
                if( SUCCEEDED( pTask->GetErrorRetryInterval( &wBuffer ) ) )
                {
                    pszAttributeKeyName = KEYWORD_JOB_RETRY_INTERVAL;
                    dwBuffer = wBuffer;
                    eValueType = Dword;
                }
                break;

            case INDEX_JOB_IDLE_MINUTES:
                {
                    WORD wBuffer2;
                    if( SUCCEEDED( pTask->GetIdleWait( &wBuffer, &wBuffer2  ) ) )
                    {
                        pszAttributeKeyName = KEYWORD_JOB_IDLE_MINUTES;
                        dwBuffer = wBuffer;
                        eValueType = DoubleWord;
                    }
                }
                break;

            case INDEX_JOB_DEADLINE_MINUTES:
                {
                    WORD wBuffer2;
                    if( SUCCEEDED( pTask->GetIdleWait( &wBuffer, &wBuffer2  ) ) )
                    {
                        pszAttributeKeyName = KEYWORD_JOB_DEADLINE_MINUTES;
                        dwBuffer = wBuffer2;
                        eValueType = Dword;
                    }
                }
                break;

            case INDEX_JOB_DATA:
                break;

            case INDEX_JOB_APPLICATION:
                if( SUCCEEDED( pTask->GetApplicationName( &pszBuffer ) ) )
                {
                    szuBuffer = pszBuffer;
                    pszAttributeKeyName = KEYWORD_JOB_APPLICATION;
                    CoTaskMemFree ( pszBuffer );
                    eValueType = String;
                }
                break;

            case INDEX_JOB_EXIT_CODE:
                if( SUCCEEDED( pTask->GetExitCode( &dwBuffer ) ) )
                {
                    pszAttributeKeyName = KEYWORD_JOB_EXIT_CODE;
                    eValueType = Dword;
                }
                break;

            case INDEX_JOB_MAX_RUN_TIME:
                if( SUCCEEDED( pTask->GetMaxRunTime( &dwBuffer ) ) )
                {
                    pszAttributeKeyName = KEYWORD_JOB_MAX_RUN_TIME;
                    eValueType = Dword;
                }
                break;

            case INDEX_JOB_FLAGS:
                if( SUCCEEDED( pTask->GetFlags( &dwBuffer ) ) )
                {
                    pszAttributeKeyName = KEYWORD_JOB_FLAGS;
                    eValueType = Dword;
                }
                break;

            case INDEX_JOB_DIRECTORY:
                if( SUCCEEDED( pTask->GetWorkingDirectory( &pszBuffer ) ) )
                {
                    szuBuffer = pszBuffer;
                    pszAttributeKeyName = KEYWORD_JOB_DIRECTORY;
                    CoTaskMemFree ( pszBuffer );
                    eValueType = String;
                }
                break;

            case INDEX_JOB_PRIORITY:
                if( SUCCEEDED( pTask->GetPriority( &dwBuffer ) ) )
                {
                    pszAttributeKeyName = KEYWORD_JOB_PRIORITY;
                    eValueType = Dword;
                }
                break;

            case INDEX_JOB_PARAMETERS:
                if( SUCCEEDED( pTask->GetParameters( &pszBuffer ) ) )
                {
                    szuBuffer = pszBuffer;
                    pszAttributeKeyName = KEYWORD_JOB_PARAMETERS;
                    CoTaskMemFree ( pszBuffer );
                    eValueType = String;
                }
                break;

            case INDEX_JOB_BAD_ATTRIBUTE:
            default:
                //  OOohh bad!
                
                break;
        }

        if( NULL != pHv )
        {
            switch( eValueType )
            {
            case String:
                HASH_STORE_PV( pHv, pszAttributeKeyName, (LPTSTR) pszuBuffer );
                break;

            case Dword:
                HASH_STORE_IV( pHv, pszAttributeKeyName, (DWORD) dwBuffer );
                break;

            }

        }
        else
        {
            switch( eValueType )
            {
            case String:
                STORE_PV( pSv, pszAttributeKeyName, (LPTSTR) pszuBuffer );
                break;

            case Dword:
                HASH_STORE_IV( pSv, pszAttributeKeyName, (DWORD) dwBuffer );
                break;

            }
        }
    }
    EXTENSION_RETURN;
}

///////////////////////////////////////////////////////////////////////
//	
XS( XS_Win32__Scheduler_Task_TIE_STORE )
{
	dXSARGS;
	EXTENSION_VARS;
    HV      *pHv = NULL;
    HV		*pHvSelf;
    ITask   *pTask = NULL;
    HRESULT hr = ERROR_SUCCESS;
    DWORD dwTotal = 0;
    BOOL fResult = FALSE;
	LPTSTR pszName = NULL;
    SV *pSvResult = NULL;
		
	if (items != 2)
	{
		croak("Usage: " EXTENSION  "::Task::TIESTORE( $Self, $Key )\n");
    }
		
    //	FETCH	
	pHvSelf = (HV*) SvRV( ST( 0 ) );
    if( NULL == ( pHv = EXTRACT_HV( ST( 1 ) ) ) )
    {
        pszName = SvPV( ST( 1 ), na );
    }
	
    pTask = (ITask *) HASH_GET_IV( pHvSelf, INDEX_TASK_INTERFACE );
    if( NULL != pTask )
    {
        CUString szuBuffer( pszName );
        LPTSTR pszAttributeKeyName = NULL;
        LPTSTR pszBuffer = NULL;
        DWORD dwBuffer = 0;
        WORD  wBuffer = 0;
        HRESULT hr = ERROR_SUCCESS;
        enum { Unknown, String, Dword } eValueType Unknown;

        switch( GetAttributeIndex( pszName ) )
        {
        
            case INDEX_JOB_ACCOUNT:
                if( SUCCEEDED( hr ) )
                {
                    CUString szuBuffer2;

                    szuBuffer = HASH_GET_PV( pHvJob, KEYWORD_JOB_ACCOUNT );
                    szuBuffer2 = HASH_GET_PV( pHvJob, KEYWORD_JOB_PASSWORD );
                    hr = pTask->SetAccountInformation( szuBuffer, szuBuffer2 );
                }
                break;

            case INDEX_JOB_PASSWORD:
                if( ! HASH_KEY_EXISTS( pHvJob, KEYWORD_JOB_ACCOUNT ) )
                {
                    LPWSTR pszwAccount;

                    hr = pTask->GetAccountInformation( &pszwAccount );
                    if( SUCCEEDED( hr ) )
                    {
                        szuBuffer = HASH_GET_PV( pHvJob, KEYWORD_JOB_PASSWORD );
                        hr = pTask->SetAccountInformation( pszwAccount, szuBuffer );
                    }
                }
                break;

            case INDEX_JOB_COMMENT:
                if( SUCCEEDED( hr ) )
                {
                    szuBuffer = HASH_GET_PV( pHvJob, KEYWORD_JOB_COMMENT );
                    hr = pTask->SetComment( szuBuffer );
                }
                break;

            case INDEX_JOB_CREATOR:
                if( SUCCEEDED( hr ) )
                {
                    szuBuffer = HASH_GET_PV( pHvJob, KEYWORD_JOB_CREATOR );
                    hr = pTask->SetCreator( szuBuffer );
                }
                break;

            case INDEX_JOB_RETRY_COUNT:
                if( SUCCEEDED( hr ) )
                {
                    dwBuffer = HASH_GET_IV( pHvJob, KEYWORD_JOB_RETRY_COUNT );
                    hr = pTask->SetErrorRetryCount( dwBuffer );
                }
                break;

            case INDEX_JOB_RETRY_INTERVAL:
                if( SUCCEEDED( hr ) )
                {
                    dwBuffer = HASH_GET_IV( pHvJob, KEYWORD_JOB_RETRY_INTERVAL );
                    pTask->SetErrorRetryInterval( dwBuffer );
                }
                break;

            case INDEX_JOB_IDLE_MINUTES:
                if( SUCCEEDED( hr ) )
                {
                    DWORD dwBuffer2;

                    dwBuffer = HASH_GET_IV( pHvJob, KEYWORD_JOB_RETRY_MINUTES );
                    dwBuffer2 = HASH_GET_IV( pHvJob, KEYWORD_JOB_DEADLINE_MINUTES );
                    hr = pTask->SetIdleWait( dwBuffer, dwBuffer2 );
                }
                break;

            case INDEX_JOB_DEADLINE_MINUTES:
                if( SUCCEEDED( hr ) )
                {
                    DWORD dwBuffer2;

                    dwBuffer = HASH_GET_IV( pHvJob, KEYWORD_JOB_RETRY_MINUTES );
                    dwBuffer2 = HASH_GET_IV( pHvJob, KEYWORD_JOB_DEADLINE_MINUTES );
                    hr = pTask->SetIdleWait( dwBuffer, dwBuffer2 );
                }
                break;

            case INDEX_JOB_DATA:
                break;

            case INDEX_JOB_APPLICATION:
                if( SUCCEEDED( hr ) )
                {
                    szuBuffer = HASH_GET_PV( pHvJob, KEYWORD_JOB_APPLICATION );
                    hr = pTask->SetApplicationName( szuBuffer );
                }
                break;

            case INDEX_JOB_EXIT_CODE:
                break;

            case INDEX_JOB_MAX_RUN_TIME:
                if( SUCCEEDED( hr ) )
                {
                    dwBuffer = HASH_GET_IV( pHvJob, KEYWORD_JOB_RETRY_MAX_RUN_TIME );
                    pTask->SetMaxRunTime( dwBuffer );
                }
                break;

            case INDEX_JOB_FLAGS:
                if( SUCCEEDED( hr ) )
                {
                    dwBuffer = HASH_GET_IV( pHvJob, KEYWORD_JOB_RETRY_FLAGS );
                    pTask->SetFlags( dwBuffer );
                }
                break;

            case INDEX_JOB_DIRECTORY:
                if( SUCCEEDED( hr ) )
                {
                    szuBuffer = HASH_GET_PV( pHvJob, KEYWORD_JOB_DIRECTORY );
                    hr = pTask->SetWorkingDirectory( szuBuffer );
                }
                break;

            case INDEX_JOB_PRIORITY:
                if( SUCCEEDED( hr ) )
                {
                    dwBuffer = HASH_GET_IV( pHvJob, KEYWORD_JOB_PRIORITY );
                    pTask->SetPriority( dwBuffer );
                }
                break;

            case INDEX_JOB_PARAMETERS:
                if( SUCCEEDED( hr ) )
                {
                    szuBuffer = HASH_GET_PV( pHvJob, KEYWORD_JOB_PARAMTERS );
                    hr = pTask->SetParameters( szuBuffer );
                }
                break;

            case INDEX_JOB_BAD_ATTRIBUTE:
            default:
                //  OOohh bad!
                
                break;
        }

        if( SUCCEEDED( hr ) )
        {
            SaveTask( pTask );
        }

    }
    EXTENSION_RETURN;
}

///////////////////////////////////////////////////////////////////////
//	
XS(XS_Win32__Scheduler_TIE_FIRSTKEY)
{
	dXSARGS;
    EXTENSION_VARS;
    HV		*pHvSelf;
    ITask   *pTask = NULL;
	
	if( 1 != items )
	{
		croak( "Usage: " EXTENSION  "::Task::FIRSTKEY( $Self )\n" );
    }

	pszPreviousKey = SvPV( ST( 1 ), na );
    pHvSelf = (HV*) SvRV( ST( 0 ) );
    pTask = (ITask *) HASH_GET_IV( pHvSelf, KEYWORD_TASK_INTERFACE );
    if( NULL != pTask )
    { 
        PUSH_PV( spTaskAttributes[ 0 ].m_pszAttribute );
    }
    EXTENSION_RETURN;
}

///////////////////////////////////////////////////////////////////////
//	
XS(XS_Win32__Scheduler_TIE_NEXTKEY)
{
	dXSARGS;
    EXTENSION_VARS;
    HV		*pHvSelf;
    ITask   *pTask = NULL;
	LPTSTR pszPreviousKey = NULL;
	
	if( 2 != items )
	{
		croak( "Usage: " EXTENSION  "::NEXTKEY( $Self, $PreviousKey )\n" );
    }

	pszPreviousKey = SvPV( ST( 1 ), na );
    pHvSelf = (HV*) SvRV( ST( 0 ) );
    pTask = (ITask *) HASH_GET_IV( phvSelf, KEYWORD_TASK_INTERFACE );
    if( NULL != pTask )
    { 
        DWORD dwIndex = GetAttributeIndex( pszPreviousKey );
        if( ( INDEX_JOB_BAD_ATTRIBUTE != pszPreviousKey )
            && ( NULL != pszTaskAttributes[ dwIndex ].m_pszAttribute ) )
        {
            PUSH_PV( spTaskAttributes[ dwIndex ].m_pszAttribute );
        }
    }
    EXTENSION_RETURN;
}

///////////////////////////////////////////////////////////////////////
//	
XS(XS_Win32__Scheduler_TIE_EXISTS)
{
	dXSARGS;
    EXTENSION_VARS;
    HV		*pHvSelf;
    ITask   *pTask = NULL;
    HRESULT hr = ERROR_SUCCESS;
    LPTSTR pszKey = NULL;
    DWORD dwTotal = 0;
    BOOL fResult = FALSE;
	
	if( 2 != items )
	{
		croak( "Usage: " EXTENSION  "::EXISTS( $Self, $Key )\n" );
    }

	pszKey  = SvPV( ST( 1 ), na);

    phvSelf = (HV*) SvRV( ST( 0 ) );
    pTask = (ITask *) HASH_GET_IV( phvSelf, KEYWORD_TASK_INTERFACE );
    if( NULL != pTask )
    {
        if( INDEX_JOB_BAD_ATTRIBUTE != GetAttributeIndex( pszKey ) )
        {
            fResult = TRUE;
        }
    }
        
    EXTENSION_RETURN_BOOL( fResult );
}

///////////////////////////////////////////////////////////////////////
//	
XS(XS_Win32__Scheduler_Task_TIE_DELETE)
{
	dXSARGS;
    EXTENSION_VARS;
    HV		*pHvSelf;
    ITask   *pTask = NULL;
    HRESULT hr = ERROR_FAIL;
    CUString szuName;
	
	if( 2 != items )
	{
		croak( "Usage: " EXTENSION  "::Task::DELETE( $Self, $Key )\n" );
    }

	//	DELETE	
	pHvSelf = (HV*) SvRV( ST( 0 ) );
	szuName = SvPV( ST( 1 ), na);

    pTask = (ITask *) HASH_GET_IV( pHvSelf, INDEX_TASK_INTERFACE );
    if( NULL != pTask )
    {
        //hr = pTask->Delete( szuName );

        // Here we must set the szuName attribute to 0 or ""
    }

    EXTENSION_RETURN_BOOL( SUCCEEDED( hr ) );
}

///////////////////////////////////////////////////////////////////////
//	
XS(XS_Win32__Scheduler_Task_TIE_DESTROY)
{
	dXSARGS;
    EXTENSION_VARS;
    HV		*pHvSelf;
    ITask   *pTask = NULL;
	
	if( 1 != items )
	{
		croak( "Usage: " EXTENSION  "::Task::DESTROY( $Self )\n" );
    }
    
	//	DESTROY
    pHvSelf = (HV*) SvRV( ST( 0 ) );
    pTask = (ITask *) HASH_GET_IV( pHvSelf, KEYWORD_TASK_INTERFACE );
    if( NULL != pTask )
    {
        pTask->Release();
        HASH_STORE_IV( pHvSelf, KEYWORD_TASK_INTERFACE, 0 );
    }

    XSRETURN_EMPTY;
}
