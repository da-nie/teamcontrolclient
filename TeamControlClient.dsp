# Microsoft Developer Studio Project File - Name="TeamControlClient" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=TeamControlClient - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TeamControlClient.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TeamControlClient.mak" CFG="TeamControlClient - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TeamControlClient - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TeamControlClient - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TeamControlClient - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ws2_32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "TeamControlClient - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "TeamControlClient - Win32 Release"
# Name "TeamControlClient - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\cbitmapcell.cpp
# End Source File
# Begin Source File

SOURCE=.\cdate.cpp
# End Source File
# Begin Source File

SOURCE=.\cdialog_about.cpp
# End Source File
# Begin Source File

SOURCE=.\cdialog_clientsettings.cpp
# End Source File
# Begin Source File

SOURCE=.\cdialog_deletefinishedtask.cpp
# End Source File
# Begin Source File

SOURCE=.\cdialog_projectsettings.cpp
# End Source File
# Begin Source File

SOURCE=.\cdialog_tasksetstate.cpp
# End Source File
# Begin Source File

SOURCE=.\cdialog_tasksettings.cpp
# End Source File
# Begin Source File

SOURCE=.\cdialog_usersettings.cpp
# End Source File
# Begin Source File

SOURCE=.\cdocument_main.cpp
# End Source File
# Begin Source File

SOURCE=.\cfillcell.cpp
# End Source File
# Begin Source File

SOURCE=.\cframecell.cpp
# End Source File
# Begin Source File

SOURCE=.\cframewnd_main.cpp
# End Source File
# Begin Source File

SOURCE=.\cicell.cpp
# End Source File
# Begin Source File

SOURCE=.\clinetextcell.cpp
# End Source File
# Begin Source File

SOURCE=.\cproject.cpp
# End Source File
# Begin Source File

SOURCE=.\csafestring.cpp
# End Source File
# Begin Source File

SOURCE=.\ctask.cpp
# End Source File
# Begin Source File

SOURCE=.\ctextcell.cpp
# End Source File
# Begin Source File

SOURCE=.\cthreadclient.cpp
# End Source File
# Begin Source File

SOURCE=.\ctransceiver.cpp
# End Source File
# Begin Source File

SOURCE=.\ctransceiver_autorization.cpp
# End Source File
# Begin Source File

SOURCE=.\ctransceiver_file.cpp
# End Source File
# Begin Source File

SOURCE=.\ctransceiver_ping.cpp
# End Source File
# Begin Source File

SOURCE=.\ctransceiver_project.cpp
# End Source File
# Begin Source File

SOURCE=.\ctransceiver_task.cpp
# End Source File
# Begin Source File

SOURCE=.\ctransceiver_user.cpp
# End Source File
# Begin Source File

SOURCE=.\ctreeview_kit.cpp
# End Source File
# Begin Source File

SOURCE=.\cuser.cpp
# End Source File
# Begin Source File

SOURCE=.\cvector_project.cpp
# End Source File
# Begin Source File

SOURCE=.\cvector_task.cpp
# End Source File
# Begin Source File

SOURCE=.\cvector_user.cpp
# End Source File
# Begin Source File

SOURCE=.\cview_base.cpp
# End Source File
# Begin Source File

SOURCE=.\cview_mytasks.cpp
# End Source File
# Begin Source File

SOURCE=.\cview_outtasks.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\Resource.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\cbitmapcell.h
# End Source File
# Begin Source File

SOURCE=.\cdate.h
# End Source File
# Begin Source File

SOURCE=.\cdialog_about.h
# End Source File
# Begin Source File

SOURCE=.\cdialog_clientsettings.h
# End Source File
# Begin Source File

SOURCE=.\cdialog_deletefinishedtask.h
# End Source File
# Begin Source File

SOURCE=.\cdialog_projectsettings.h
# End Source File
# Begin Source File

SOURCE=.\cdialog_tasksetstate.h
# End Source File
# Begin Source File

SOURCE=.\cdialog_tasksettings.h
# End Source File
# Begin Source File

SOURCE=.\cdialog_usersettings.h
# End Source File
# Begin Source File

SOURCE=.\cdocument_main.h
# End Source File
# Begin Source File

SOURCE=.\cfillcell.h
# End Source File
# Begin Source File

SOURCE=.\cframecell.h
# End Source File
# Begin Source File

SOURCE=.\cframewnd_main.h
# End Source File
# Begin Source File

SOURCE=.\cicell.h
# End Source File
# Begin Source File

SOURCE=.\clinetextcell.h
# End Source File
# Begin Source File

SOURCE=.\cproject.h
# End Source File
# Begin Source File

SOURCE=.\craiiccriticalsection.h
# End Source File
# Begin Source File

SOURCE=.\csafestring.h
# End Source File
# Begin Source File

SOURCE=.\ctask.h
# End Source File
# Begin Source File

SOURCE=.\ctextcell.h
# End Source File
# Begin Source File

SOURCE=.\cthreadclient.h
# End Source File
# Begin Source File

SOURCE=.\ctransceiver.h
# End Source File
# Begin Source File

SOURCE=.\ctransceiver_autorization.h
# End Source File
# Begin Source File

SOURCE=.\ctransceiver_file.h
# End Source File
# Begin Source File

SOURCE=.\ctransceiver_ping.h
# End Source File
# Begin Source File

SOURCE=.\ctransceiver_project.h
# End Source File
# Begin Source File

SOURCE=.\ctransceiver_task.h
# End Source File
# Begin Source File

SOURCE=.\ctransceiver_user.h
# End Source File
# Begin Source File

SOURCE=.\ctreeview_kit.h
# End Source File
# Begin Source File

SOURCE=.\cuser.h
# End Source File
# Begin Source File

SOURCE=.\cvector_project.h
# End Source File
# Begin Source File

SOURCE=.\cvector_task.h
# End Source File
# Begin Source File

SOURCE=.\cvector_user.h
# End Source File
# Begin Source File

SOURCE=.\cview_base.h
# End Source File
# Begin Source File

SOURCE=.\cview_mytasks.h
# End Source File
# Begin Source File

SOURCE=.\cview_outtasks.h
# End Source File
# Begin Source File

SOURCE=.\protocol.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Bitmap\about.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\Bitmap\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\Bitmap\menu_add_task.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\menu_task_is_running.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\mymenulist_taskdone.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\mymenulist_taskfinish.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\mymenulist_taskread.bmp
# End Source File
# Begin Source File

SOURCE=.\outmenulist_deleteask.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\outmenulist_edittask.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\outview_task_cancel.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\outview_task_done.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\outview_task_executed.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\outview_task_finished.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\outview_task_not_read.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\outview_task_read.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\systray_icon.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\systray_icon.ico
# End Source File
# Begin Source File

SOURCE=.\Bitmap\systray_icon_not_read.ico
# End Source File
# Begin Source File

SOURCE=.\Bitmap\systray_icon_not_read_inverse.ico
# End Source File
# Begin Source File

SOURCE=.\Bitmap\task_canceled_frame_two.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\task_done_frame_two.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\task_finished_big.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\task_is_running_frame_two.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\task_not_read_frame_two.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\task_readed.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\task_readed_frame_two.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\threemenulist_userinfo.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\toolbar_main.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\toolbar_my_task.bmp
# End Source File
# Begin Source File

SOURCE=.\treemenulist_addtask.bmp
# End Source File
# Begin Source File

SOURCE=.\treeview.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap\user.BMP
# End Source File
# End Group
# End Target
# End Project
