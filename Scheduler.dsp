# Microsoft Developer Studio Project File - Name="Scheduler" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Scheduler - Win32 Debug 5005 AS
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Scheduler.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Scheduler.mak" CFG="Scheduler - Win32 Debug 5005 AS"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Scheduler - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Scheduler - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Scheduler - Win32 Debug 5005 AS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Scheduler - Win32 Release 5005 AS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Scheduler - Win32 Release 5005" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Scheduler - Win32 Release 5006" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Perl/Win32/Scheduler", GCDAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Scheduler - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SCHEDULER_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SCHEDULER_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "Scheduler - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SCHEDULER_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SCHEDULER_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Scheduler - Win32 Debug 5005 AS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Scheduler___Win32_Debug_5005_AS"
# PROP BASE Intermediate_Dir "Scheduler___Win32_Debug_5005_AS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\temp\out"
# PROP Intermediate_Dir "\temp\out"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SCHEDULER_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "\include" /I "\include\perl\5005" /I "\include\perl\5005\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SCHEDULER_EXPORTS" /D "MSWIN32" /D "PERL_OBJECT" /D "EMBED" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /fo"Scheduler.res" /i "\include" /i "\include\perl\5005" /d "_DEBUG" /d "MSWIN32" /d "PERL_OBJECT" /d "EMBED"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"c:\perl\site\lib\auto\win32\Scheduler\Scheduler.dll" /pdbtype:sept /libpath:"\lib"

!ELSEIF  "$(CFG)" == "Scheduler - Win32 Release 5005 AS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Scheduler___Win32_Release_5005_AS"
# PROP BASE Intermediate_Dir "Scheduler___Win32_Release_5005_AS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\temp\out"
# PROP Intermediate_Dir "\temp\out"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SCHEDULER_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "\include" /I "\include\perl\5005" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SCHEDULER_EXPORTS" /D "MSWIN32" /D "PERL_OBJECT" /D "EMBED" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /fo"Scheduler.res" /i "\include" /i "\include\perl\5005" /d "NDEBUG" /d "MSWIN32" /d "PERL_OBJECT" /d "EMBED"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"bin\Scheduler_5005_AS.dll"

!ELSEIF  "$(CFG)" == "Scheduler - Win32 Release 5005"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Scheduler___Win32_Release_5005"
# PROP BASE Intermediate_Dir "Scheduler___Win32_Release_5005"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\temp\out"
# PROP Intermediate_Dir "\temp\out"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "\include" /I "\include\perl\5005" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SCHEDULER_EXPORTS" /D "MSWIN32" /D "PERL_OBJECT" /D "EMBED" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "\include" /I "\include\perl\5005" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SCHEDULER_EXPORTS" /D "MSWIN32" /D "EMBED" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /fo"Scheduler.res" /i "\include" /i "\include\perl\5005" /d "NDEBUG" /d "MSWIN32" /d "PERL_OBJECT" /d "EMBED"
# ADD RSC /l 0x409 /fo"Scheduler.res" /i "\include" /i "\include\perl\5005" /d "NDEBUG" /d "MSWIN32" /d "EMBED"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"bin\Scheduler_5005_AS.dll"
# ADD LINK32 perl.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"bin\Scheduler_5005.dll" /libpath:"\lib\perl"

!ELSEIF  "$(CFG)" == "Scheduler - Win32 Release 5006"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Scheduler___Win32_Release_5006"
# PROP BASE Intermediate_Dir "Scheduler___Win32_Release_5006"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\temp\out"
# PROP Intermediate_Dir "\temp\out"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "\include" /I "\include\perl\5005" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SCHEDULER_EXPORTS" /D "MSWIN32" /D "PERL_OBJECT" /D "EMBED" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "\include" /I "\include\perl\5.6" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "EMBED" /D "MSWIN32" /D "HAVE_DES_FCRYPT" /D "MULTIPLICITY" /D "PERL_IMPLICIT_CONTEXT" /D "PERL_IMPLICIT_SYS" /D "PERL_MSVCRT_READFIX" /D "PERL_NO_GET_CONTEXT" /D "PERL_POLLUTE" /D "USE_ITHREADS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /fo"Scheduler.res" /i "\include" /i "\include\perl\5005" /d "NDEBUG" /d "MSWIN32" /d "PERL_OBJECT" /d "EMBED"
# ADD RSC /l 0x409 /fo"Scheduler.res" /i "\include" /i "\include\perl\5.6" /d "WIN32" /d "_DEBUG" /d "_WINDOWS" /d "EMBED" /d "MSWIN32" /d "HAVE_DES_FCRYPT" /d "MULTIPLICITY" /d "PERL_IMPLICIT_CONTEXT" /d "PERL_IMPLICIT_SYS" /d "PERL_MSVCRT_READFIX" /d "PERL_NO_GET_CONTEXT" /d "PERL_POLLUTE" /d "USE_ITHREADS"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"bin\Scheduler_5005_AS.dll"
# ADD LINK32 perl56.lib perlEZ.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"bin\Scheduler_5006.dll" /libpath:"\lib\perl\5.6"

!ENDIF 

# Begin Target

# Name "Scheduler - Win32 Release"
# Name "Scheduler - Win32 Debug"
# Name "Scheduler - Win32 Debug 5005 AS"
# Name "Scheduler - Win32 Release 5005 AS"
# Name "Scheduler - Win32 Release 5005"
# Name "Scheduler - Win32 Release 5006"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CONSTANT.CPP
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Libraries\String\CUString.cpp
# End Source File
# Begin Source File

SOURCE=.\Scheduler.cpp
# End Source File
# Begin Source File

SOURCE=.\Scheduler.def
# End Source File
# Begin Source File

SOURCE=.\TIE_Scheduler.xpp
# End Source File
# Begin Source File

SOURCE=.\TIE_Task.xpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Scheduler.hpp
# End Source File
# Begin Source File

SOURCE=.\SchedulerBuild.h
# End Source File
# Begin Source File

SOURCE=.\VERSION.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Misc"

# PROP Default_Filter ""
# Begin Group "Test"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Test\TEST.PL
# End Source File
# End Group
# Begin Source File

SOURCE=.\bin\CONFIG.INI
# End Source File
# Begin Source File

SOURCE=.\Scheduler.pm
# End Source File
# Begin Source File

SOURCE=".\Win32-Scheduler.ppd"
# End Source File
# End Group
# Begin Source File

SOURCE=.\Test\CopyJobs.pl
# End Source File
# End Target
# End Project
