///////////////////////////////////////////////////////////////////////
//	
void SaveTask( ITask *pTask )
{
    IPersistFile *pPersistFile;

    if( NULL != pTask )
    {
        HRESULT hr;

        if( SUCCEEDED( pTask->QueryInterface( IID_IPersistFile, (void **) &pPersistFile ) ) )
        {
            hr = pPersistFile->Save( NULL, TRUE );
            // Release the IPersistFile interface.
            pPersistFile->Release();
        }
    }
}

///////////////////////////////////////////////////////////////////////
//	
XS( XS_Win32__Scheduler_TIE_HASH )
{
	dXSARGS;
    EXTENSION_VARS;
	HV	*phvObject = NULL;
	SV	*psvSelf   = NULL;
	SV	*psvResult = NULL;
		

    //  Maybe here we should allow you to connect to a remote machine??
	if( ( 1 > items ) || ( 2 < items  ) )
	{
		croak( "Usage: " EXTENSION  "::TIEHASH( $Self [, $Machine ] )\n" );
    }

	psvSelf = ST( 0 );
	
	phvObject = newHV();
    if( NULL != phvObject )
	{
        ITaskScheduler *pITS = NULL;
        HRESULT hr = CoCreateInstance( CLSID_CTaskScheduler,
                                        NULL,
                                        CLSCTX_INPROC_SERVER,
                                        IID_ITaskScheduler,
                                        (void **) &pITS );
        if( SUCCEEDED( hr ) )
        {
            if( 2 == items )
            {
                LPTSTR pszMachine = SvPV( ST( 1 ), na );
                if( 0 != _tcscmp( pszMachine, TEXT( "" ) ) )
                {
                    CUString szuMachine( pszMachine );
                    hr = pITS->SetTargetComputer( szuMachine );
                }
            }

            if( SUCCEEDED( hr ) )
            {
                HASH_STORE_IV( phvObject, KEYWORD_SCHEDULER_INTERFACE, pITS );
    		    psvResult = sv_bless( sv_2mortal( newRV_noinc( (SV*) phvObject ) ), 
                                      gv_stashpv( EXTENSION , TRUE ) );
            }
        }
	}
		
	if( NULL != psvResult )
	{
        PUSH_NOREF( psvResult );
	}

	EXTENSION_RETURN;
}

///////////////////////////////////////////////////////////////////////
//	
XS(XS_Win32__Scheduler_TIE_FETCH)
{
	dXSARGS;
	EXTENSION_VARS;
    HV		*phvSelf;
    ITaskScheduler *pITS = NULL;
    HRESULT hr = ERROR_SUCCESS;
    DWORD dwTotal = 0;
    BOOL fResult = FALSE;
	LPTSTR pszName = NULL;
    SV *pSvResult = NULL;
		
	if (items != 2)
	{
		croak("Usage: " EXTENSION  "::TIEFETCH( $Self, $Key )\n");
    }
		
    //	FETCH	
	phvSelf = (HV*) SvRV( ST( 0 ) );
    pszName = SvPV( ST( 1 ), na );
	
    pITS = (ITaskScheduler *) HASH_GET_IV( phvSelf, KEYWORD_SCHEDULER_INTERFACE );
    if( NULL != pITS )
    {
        CUString szuBuffer( pszName );
        ITask *pTask = NULL;    

        if( SUCCEEDED( pITS->Activate( szuBuffer, IID_ITask, (IUnknown**) &pTask ) ) )
        {


        //   Here we should create a new object and make it magic...
                pSvResult = TieTask( PERL_OBJECT_ARGS pTask );

	        if( NULL != pSvResult )
	        {
        //		ST(0) = sv_newmortal();
        //		sv_setsv( ST(0), svResult);
                PUSH_NOREF( pSvResult );
	        }
/*            
            HV *pHv = newHV();
            if( NULL != pHv )
            {
                WORD wBuffer;
                WORD wBuffer2;
                DWORD dwBuffer;
                LPWSTR pszBuffer = NULL;

                if( SUCCEEDED( pTask->GetAccountInformation( &pszBuffer ) ) )
                {
                    szuBuffer = pszBuffer;
                    HASH_STORE_PV( pHv, KEYWORD_JOB_ACCOUNT, (LPTSTR) szuBuffer );
                    CoTaskMemFree ( pszBuffer );
                }

                if( SUCCEEDED( pTask->GetApplicationName( &pszBuffer ) ) )
                {
                    szuBuffer = pszBuffer;
                    HASH_STORE_PV( pHv, KEYWORD_JOB_APPLICATION, (LPTSTR) szuBuffer );
                    CoTaskMemFree ( pszBuffer );
                }

                if( SUCCEEDED( pTask->GetComment( &pszBuffer ) ) )
                {
                    szuBuffer = pszBuffer;
                    HASH_STORE_PV( pHv, KEYWORD_JOB_COMMENT, (LPTSTR) szuBuffer );
                    CoTaskMemFree ( pszBuffer );
                }

                if( SUCCEEDED( pTask->GetCreator( &pszBuffer ) ) )
                {
                    szuBuffer = pszBuffer;
                    HASH_STORE_PV( pHv, KEYWORD_JOB_CREATOR, (LPTSTR) szuBuffer );
                    CoTaskMemFree ( pszBuffer );
                }

                if( SUCCEEDED( pTask->GetParameters( &pszBuffer ) ) )
                {
                    szuBuffer = pszBuffer;
                    HASH_STORE_PV( pHv, KEYWORD_JOB_PARAMETERS, (LPTSTR) szuBuffer );
                    CoTaskMemFree ( pszBuffer );
                }

                if( SUCCEEDED( pTask->GetWorkingDirectory( &pszBuffer ) ) )
                {
                    szuBuffer = pszBuffer;
                    HASH_STORE_PV( pHv, KEYWORD_JOB_DIRECTORY, (LPTSTR) szuBuffer );
                    CoTaskMemFree ( pszBuffer );
                }

                if( SUCCEEDED( pTask->GetErrorRetryCount( &wBuffer ) ) )
                {
                    HASH_STORE_IV( pHv, KEYWORD_JOB_RETRY_COUNT, wBuffer );
                }

                if( SUCCEEDED( pTask->GetErrorRetryInterval( &wBuffer ) ) )
                {
                    HASH_STORE_IV( pHv, KEYWORD_JOB_RETRY_INTERVAL, wBuffer );
                }

                if( SUCCEEDED( pTask->GetExitCode( &dwBuffer ) ) )
                {
                    HASH_STORE_IV( pHv, KEYWORD_JOB_EXIT_CODE, dwBuffer );
                }

                if( SUCCEEDED( pTask->GetFlags( &dwBuffer ) ) )
                {
                    HASH_STORE_IV( pHv, KEYWORD_JOB_FLAGS, dwBuffer );
                }

                if( SUCCEEDED( pTask->GetIdleWait( &wBuffer, &wBuffer2  ) ) )
                {
                    HASH_STORE_IV( pHv, KEYWORD_JOB_IDLE_MINUTES, wBuffer );
                    HASH_STORE_IV( pHv, KEYWORD_JOB_DEADLINE_MINUTES, wBuffer2 );
                }

                if( SUCCEEDED( pTask->GetMaxRunTime( &dwBuffer ) ) )
                {
                    HASH_STORE_IV( pHv, KEYWORD_JOB_MAX_RUN_TIME, dwBuffer );
                }

                if( SUCCEEDED( pTask->GetPriority( &dwBuffer ) ) )
                {
                    HASH_STORE_IV( pHv, KEYWORD_JOB_PRIORITY, dwBuffer );
                }


                PUSH_HV( pHv );
            }
            pTask->Release();
*/
        }
    }

    EXTENSION_RETURN;
}

///////////////////////////////////////////////////////////////////////
//	
XS( XS_Win32__Scheduler_TIE_STORE )
{
	dXSARGS;
	EXTENSION_VARS;
    HV		*phvSelf;
    HV      *pHvJob;
    ITaskScheduler *pITS = NULL;
    HRESULT hr = ERROR_SUCCESS;
    DWORD dwTotal = 0;
    BOOL fResult = FALSE;
	LPTSTR pszName = NULL;
	
	if( 3 != items )
	{
		croak( "Usage: " EXTENSION  "::TIESTORE( $Self, $Key, \\%Job )\n" );
    }

	phvSelf = (HV*) SvRV( ST( 0 ) );
    pszName = SvPV( ST( 1 ), na );
	pHvJob  = EXTRACT_HV( ST( 2 ) );

    pITS = (ITaskScheduler *) HASH_GET_IV( phvSelf, KEYWORD_SCHEDULER_INTERFACE );
    if( ( NULL != pITS ) && ( NULL != pHvJob ) )
    {
        CUString szuBuffer( pszName );
        //  IScheduledWorkItem *pWorkItem = NULL;
        ITask *pTask = NULL;
        BOOL fNewTask = FALSE;

        //  First check if the element already exists. If so then modify it
        //  otherwise create a new task

        hr = pITS->Activate( szuBuffer, IID_ITask, (IUnknown**) &pTask );
        if( FAILED( hr ) )
        {
            hr = pITS->NewWorkItem( szuBuffer, CLSID_CTask, IID_ITask, (IUnknown**) &pTask );
            fNewTask = TRUE;
        }

        if( SUCCEEDED( hr ) )
        {
            CUString szuBuffer2;

            if( SUCCEEDED( hr ) && ( HASH_KEY_EXISTS( pHvJob, KEYWORD_JOB_ACCOUNT ) ) )
            {
                szuBuffer = HASH_GET_PV( pHvJob, KEYWORD_JOB_ACCOUNT );
                szuBuffer2 = HASH_GET_PV( pHvJob, KEYWORD_JOB_PASSWORD );
                hr = pTask->SetAccountInformation( szuBuffer, szuBuffer2 );
            }
            
            if( SUCCEEDED( hr ) && ( HASH_KEY_EXISTS( pHvJob, KEYWORD_JOB_COMMENT ) ) )
            {
                szuBuffer = HASH_GET_PV( pHvJob, KEYWORD_JOB_COMMENT );
                hr = pTask->SetComment( szuBuffer );
            }

            if( SUCCEEDED( hr ) && ( HASH_KEY_EXISTS( pHvJob, KEYWORD_JOB_CREATOR ) ) )
            {
                szuBuffer = HASH_GET_PV( pHvJob, KEYWORD_JOB_CREATOR );
                hr = pTask->SetCreator( szuBuffer );
            }

            if( SUCCEEDED( hr ) && ( HASH_KEY_EXISTS( pHvJob, KEYWORD_JOB_RETRY_COUNT ) ) )
            {
                WORD wRetryCount = (WORD) HASH_GET_IV( pHvJob, KEYWORD_JOB_RETRY_COUNT );
                hr = pTask->SetErrorRetryCount( wRetryCount );
            }

            if( SUCCEEDED( hr ) && ( HASH_KEY_EXISTS( pHvJob, KEYWORD_JOB_RETRY_INTERVAL ) ) )
            {
                WORD wRetryInterval = (WORD) HASH_GET_IV( pHvJob, KEYWORD_JOB_RETRY_INTERVAL );
                hr = pTask->SetErrorRetryInterval( wRetryInterval );
            }

            if( SUCCEEDED( hr ) && ( HASH_KEY_EXISTS( pHvJob, KEYWORD_JOB_FLAGS ) ) )
            {
                DWORD dwFlags = HASH_GET_IV( pHvJob, KEYWORD_JOB_FLAGS );
                hr = pTask->SetFlags( dwFlags );
            }

            if( SUCCEEDED( hr ) && ( HASH_KEY_EXISTS( pHvJob, KEYWORD_JOB_CREATOR ) ) )
            {
                WORD wIdleMinutes = HASH_GET_IV( pHvJob, KEYWORD_JOB_IDLE_MINUTES );
                WORD wDeadlineMinutes = HASH_GET_IV( pHvJob, KEYWORD_JOB_DEADLINE_MINUTES );
                hr = pTask->SetIdleWait( wIdleMinutes, wDeadlineMinutes );
            }

            if( SUCCEEDED( hr ) && ( HASH_KEY_EXISTS( pHvJob, KEYWORD_JOB_DATA ) ) )
            {
                SV* pSv = HASH_GET_SV( pHvJob, KEYWORD_JOB_DATA );
                PBYTE pData = (PBYTE) SvPV( pSv, na );
                DWORD dwDataLength = SvLEN( pSv );
                hr = pTask->SetWorkItemData( dwDataLength, (BYTE*) pData );
            }

            if( SUCCEEDED( hr ) && ( HASH_KEY_EXISTS( pHvJob, KEYWORD_JOB_APPLICATION ) ) )
            {
                szuBuffer = HASH_GET_PV( pHvJob, KEYWORD_JOB_APPLICATION );
                hr = pTask->SetApplicationName( szuBuffer );
            }

            if( SUCCEEDED( hr ) && ( HASH_KEY_EXISTS( pHvJob, KEYWORD_JOB_DIRECTORY ) ) )
            {
                szuBuffer = HASH_GET_PV( pHvJob, KEYWORD_JOB_DIRECTORY );
                hr = pTask->SetWorkingDirectory( szuBuffer );
            }

            if( SUCCEEDED( hr ) && ( HASH_KEY_EXISTS( pHvJob, KEYWORD_JOB_PRIORITY ) ) )
            {
                DWORD dwPriority = HASH_GET_IV( pHvJob, KEYWORD_JOB_PRIORITY );
                hr = pTask->SetPriority( dwPriority );
            }

            if( SUCCEEDED( hr ) && ( HASH_KEY_EXISTS( pHvJob, KEYWORD_JOB_MAX_RUN_TIME ) ) )
            {
                DWORD dwMaxRunTime = HASH_GET_IV( pHvJob, KEYWORD_JOB_MAX_RUN_TIME );
                hr = pTask->SetMaxRunTime( dwMaxRunTime );
            }

            if( SUCCEEDED( hr ) && ( HASH_KEY_EXISTS( pHvJob, KEYWORD_JOB_PARAMETERS ) ) )
            {
                szuBuffer = HASH_GET_PV( pHvJob, KEYWORD_JOB_PARAMETERS );
                hr = pTask->SetParameters( szuBuffer );
            }

            if( SUCCEEDED( hr ) )
            {
                if( TRUE == fNewTask )
                {
                    szuBuffer = pszName;
                    if( SUCCEEDED( pITS->AddWorkItem( szuBuffer, pTask ) ) )
                    {
                        fResult = TRUE;
                    }
                }
                else
                {
                    fResult = TRUE;
                }
            }
            
            SaveTask( pTask );
            
            if( TRUE == fResult )
            {
                PUSH_IV( 1 );
            }

            pTask->Release();
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
    HV		*phvSelf;
    ITaskScheduler *pITS = NULL;
    HRESULT hr = ERROR_SUCCESS;
    DWORD dwTotal = 0;
    BOOL fResult = FALSE;
	LPTSTR pszPreviousKey = NULL;
	
	if( 1 != items )
	{
		croak( "Usage: " EXTENSION  "::FIRSTKEY( $Self )\n" );
    }

    phvSelf = (HV*) SvRV( ST( 0 ) );
    pITS = (ITaskScheduler *) HASH_GET_IV( phvSelf, KEYWORD_SCHEDULER_INTERFACE );
    if( NULL != pITS )
    {
        IEnumWorkItems *pEnum = NULL;
        if( SUCCEEDED( pITS->Enum( &pEnum ) ) )
        {
            
            LPWSTR *pszwNames;
            DWORD dwTasks = 0;
            DWORD dwTasksToFetch = 1;
            CUString szuName;
            BOOL fFound = FALSE;

            if( SUCCEEDED( pEnum->Next( dwTasksToFetch,
                                            &pszwNames,
                                            &dwTasks ) )
                                        && ( 0 != dwTasks ) )
            {
                DWORD dwCount;

                szuName = pszwNames[ 0 ];
                CoTaskMemFree( pszwNames[ 0 ] );

//                if( 0 == ( dwCount = FindSubString( szuName, TEXT( ".job" ) ) ) )
                {
                    dwCount = _tcslen( (LPTSTR) szuName );
                }
                PUSH_PNV( (LPTSTR) szuName, dwCount );
            }
            CoTaskMemFree( pszwNames );
            pEnum->Release();
        }    
    }

    EXTENSION_RETURN;
}

///////////////////////////////////////////////////////////////////////
//	
XS(XS_Win32__Scheduler_TIE_NEXTKEY)
{
	dXSARGS;
    EXTENSION_VARS;
    HV		*phvSelf;
    ITaskScheduler *pITS = NULL;
    HRESULT hr = ERROR_SUCCESS;
    DWORD dwTotal = 0;
    BOOL fResult = FALSE;
	LPTSTR pszPreviousKey = NULL;
	
	if( 2 != items )
	{
		croak( "Usage: " EXTENSION  "::NEXTKEY( $Self, $PreviousKey )\n" );
    }

	pszPreviousKey = SvPV( ST( 1 ), na );
    phvSelf = (HV*) SvRV( ST( 0 ) );
    pITS = (ITaskScheduler *) HASH_GET_IV( phvSelf, KEYWORD_SCHEDULER_INTERFACE );
    if( NULL != pITS )
    {
        IEnumWorkItems *pEnum = NULL;
        if( SUCCEEDED( pITS->Enum( &pEnum ) ) )
        {
            
            LPWSTR *pszwNames;
            DWORD dwTasks = 0;
            DWORD dwTasksToFetch = TOTAL_TASKS_TO_RETRIEVE;
            CUString szuName;
            BOOL fFound = FALSE;

            while( SUCCEEDED( pEnum->Next( dwTasksToFetch,
                                            &pszwNames,
                                            &dwTasks ) )
                                        && ( 0 != dwTasks )
                                        && ( FALSE == fResult ) )
            {
                DWORD dwIndex = 0;
                while( dwIndex < dwTasks )
                {
                    szuName = pszwNames[ dwIndex ];
                    CoTaskMemFree( pszwNames[ dwIndex++ ] );

                    if( TRUE == fFound )
                    {
                        DWORD dwCount;
                        fResult = TRUE; 
//                        if( 0 == ( dwCount = FindSubString( szuName, TEXT( ".job" ) ) ) )
                        {
                            dwCount = _tcslen( (LPTSTR) szuName );
                        }
                        PUSH_PNV( (LPTSTR) szuName, dwCount );

                        while( dwIndex < dwTasks )
                        {
                            CoTaskMemFree( pszwNames[ dwIndex++ ] );
                        }
                        break;
                    }
                    else if( 0 == _tcsicmp( szuName, pszPreviousKey ) )
                    {
                        fFound = TRUE;
                    }
                }
                CoTaskMemFree( pszwNames );
            }
            pEnum->Release();
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
    HV		*phvSelf;
    ITaskScheduler *pITS = NULL;
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
    pITS = (ITaskScheduler *) HASH_GET_IV( phvSelf, KEYWORD_SCHEDULER_INTERFACE );
    if( NULL != pITS )
    {
        CUString szuBuffer( pszKey );
        ITask *pTask = NULL;
        BOOL fNewTask = FALSE;

        //  First check if the element already exists. If so then modify it
        //  otherwise create a new task

        if( SUCCEEDED( pITS->Activate( szuBuffer, IID_ITask, (IUnknown**) &pTask ) ) )
        {
            fResult = TRUE;
            pTask->Release();
        }
    }
        
/*        
        
        
        
        IEnumWorkItems *pEnum = NULL;
        if( SUCCEEDED( pITS->Enum( &pEnum ) ) )
        {
            
            LPWSTR *pszwNames;
            DWORD dwTasks = 0;
            DWORD dwTasksToFetch = TOTAL_TASKS_TO_RETRIEVE;
            CUString szuName;

            while( SUCCEEDED( pEnum->Next( dwTasksToFetch,
                                            &pszwNames,
                                            &dwTasks ) )
                                        && ( 0 != dwTasks )
                                        && ( FALSE == fResult ) )
            {
                DWORD dwIndex = 0;
                while( dwIndex < dwTasks )
                {
                    szuName = pszwNames[ dwIndex ];
                    CoTaskMemFree( pszwNames[ dwIndex++ ] );

                    if( ( FALSE == fResult ) && ( 0 == _tcsicmp( szuName, pszKey ) ) )
                    {
                        fResult = TRUE; 
                    }
                }
                CoTaskMemFree( pszwNames );
            }
            pEnum->Release();
        }    
    }
*/

    EXTENSION_RETURN_BOOL( fResult );
}

///////////////////////////////////////////////////////////////////////
//	
XS(XS_Win32__Scheduler_TIE_CLEAR)
{
	dXSARGS;
    EXTENSION_VARS;
    HV		*phvSelf;
    ITaskScheduler *pITS = NULL;
    HRESULT hr = ERROR_SUCCESS;
    DWORD dwTotal = 0;
	
	if( 1 != items )
	{
		croak( "Usage: " EXTENSION  "::CLEAR( $Self )\n" );
    }

#ifdef CLEAR_WORK_ITEMS
    //  This is VERY dangerous as it will clear out all of the
    //  registered work items.  BE CAREFULL IF YOU USE THIS!!!
    phvSelf = (HV*) SvRV( ST( 0 ) );
    pITS = (ITaskScheduler *) HASH_GET_IV( hvSelf, KEYWORD_SCHEDULER_INTERFACE );
    if( NULL != pITS )
    {
        IEnumWorkItems *pEnum = NULL;
        if( SUCCEEDED( pITS->Enum( &pEnum ) )
        {
            LPWSTR *pszwNames;
            DWORD dwTasks = 0;
            DWORD dwTasksToFetch = TOTAL_TASKS_TO_RETRIEVE;
            CUString szuName;
     
            while( SUCCEEDED( pIEnum->Next( dwTasksToFetch,
                                            &pszwNames,
                                            &dwTasks ) )
                                        && ( 0 != dwTasks ) )
            {
                while( dwTasks )
                {
                    szuName = pszwNames[ --dwTasks ];
                    CoTaskMemFree( pszwNames[ dwTasks ] );

                    dwTotal++;
                    hr = pITS->Delete( pszuName );
                }
                CoTaskMemFree( pszwNames );
            }
            pIEnum->Release();
        }    
    }
#endif  //  CLEAR_WORK_ITEMS

    EXTENSION_RETURN_BOOL( SUCCEEDED( hr ) );
}

///////////////////////////////////////////////////////////////////////
//	
XS(XS_Win32__Scheduler_TIE_DELETE)
{
	dXSARGS;
    EXTENSION_VARS;
    HV		*phvSelf;
    ITaskScheduler *pITS = NULL;
    HRESULT hr;
    CUString szuName;
	
	if( 2 != items )
	{
		croak( "Usage: " EXTENSION  "::DELETE( $Self, $Key )\n" );
    }

	//	DELETE	
	phvSelf = (HV*) SvRV( ST( 0 ) );
	szuName = SvPV( ST( 1 ), na);

    pITS = (ITaskScheduler *) HASH_GET_IV( phvSelf, KEYWORD_SCHEDULER_INTERFACE );
    if( NULL != pITS )
    {
        hr = pITS->Delete( szuName );
    }

    EXTENSION_RETURN_BOOL( SUCCEEDED( hr ) );
}

///////////////////////////////////////////////////////////////////////
//	
XS(XS_Win32__Scheduler_TIE_DESTROY)
{
	dXSARGS;
    EXTENSION_VARS;
    HV		*phvSelf;
    SV      *pSvSelf = NULL;
    ITaskScheduler *pITS = NULL;
	
	if( 1 != items )
	{
		croak( "Usage: " EXTENSION  "::DESTROY( $Self )\n" );
    }
    
	//	DESTROY
    phvSelf = (HV*) SvRV( ST( 0 ) );
    pITS = (ITaskScheduler *) HASH_GET_IV( phvSelf, KEYWORD_SCHEDULER_INTERFACE );
    if( NULL != pITS )
    {
        pITS->Release();
    }

    XSRETURN_EMPTY;
}
