# Microsoft Developer Studio Project File - Name="FB" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=FB - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FB.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FB.mak" CFG="FB - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FB - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /X /I "C:\PROGRA~1\PAXPAY~1\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 POSLIB.lib POSLIB.res POSApp.lib nafxcwd.lib /nologo /subsystem:windows /debug /machine:I386 /out:"FB.exe" /pdbtype:sept /libpath:"C:\PROGRA~1\PAXPAY~1\LIB"
# Begin Target

# Name "FB - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\PasswordCheck.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AppInfo.h
# End Source File
# Begin Source File

SOURCE=.\globaldef.h
# End Source File
# Begin Source File

SOURCE=.\UI\PasswordCheck.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Engine"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Engine\AdviceEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\Engine\AdviceEngine.h
# End Source File
# Begin Source File

SOURCE=.\Engine\CardReader.cpp
# End Source File
# Begin Source File

SOURCE=.\Engine\CardReader.h
# End Source File
# Begin Source File

SOURCE=.\Engine\CommEngine2.cpp
# End Source File
# Begin Source File

SOURCE=.\Engine\CommEngine2.h
# End Source File
# Begin Source File

SOURCE=.\Engine\Engine.cpp
# End Source File
# Begin Source File

SOURCE=.\Engine\Engine.h
# End Source File
# Begin Source File

SOURCE=.\Engine\FileSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\Engine\FileSystem.h
# End Source File
# Begin Source File

SOURCE=.\Engine\OnlineEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\Engine\OnlineEngine.h
# End Source File
# Begin Source File

SOURCE=.\Engine\PrinterEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\Engine\PrinterEngine.h
# End Source File
# Begin Source File

SOURCE=.\Engine\RefundEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\Engine\RefundEngine.h
# End Source File
# Begin Source File

SOURCE=.\Engine\SettleEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\Engine\SettleEngine.h
# End Source File
# Begin Source File

SOURCE=.\Engine\TMSEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\Engine\TMSEngine.h
# End Source File
# Begin Source File

SOURCE=.\Engine\UIEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\Engine\UIEngine.h
# End Source File
# Begin Source File

SOURCE=.\Engine\VoidEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\Engine\VoidEngine.h
# End Source File
# End Group
# Begin Group "UI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UI\DelayedMessageBox.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\DelayedMessageBox.h
# End Source File
# Begin Source File

SOURCE=.\UI\IdleDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\IdleDlg.h
# End Source File
# Begin Source File

SOURCE=.\UI\IMenu.h
# End Source File
# Begin Source File

SOURCE=.\UI\InputBox.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\InputBox.h
# End Source File
# Begin Source File

SOURCE=.\UI\LoginDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\LoginDlg.h
# End Source File
# Begin Source File

SOURCE=.\UI\Menu.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\Menu.h
# End Source File
# Begin Source File

SOURCE=.\UI\MenuItem.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\MenuItem.h
# End Source File
# Begin Source File

SOURCE=.\UI\MessageBox.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\MessageBox.h
# End Source File
# Begin Source File

SOURCE=.\UI\Screen.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\Screen.h
# End Source File
# Begin Source File

SOURCE=.\UI\ScreenBatchSum.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\ScreenBatchSum.h
# End Source File
# Begin Source File

SOURCE=.\UI\ScreenDefParams.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\ScreenDefParams.h
# End Source File
# Begin Source File

SOURCE=.\UI\ScreenParams.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\ScreenParams.h
# End Source File
# Begin Source File

SOURCE=.\Util\ScreenParams.h
# End Source File
# Begin Source File

SOURCE=.\UI\ScreenTrnxLog.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\ScreenTrnxLog.h
# End Source File
# Begin Source File

SOURCE=.\UI\SSMenu2.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\SSMenu2.h
# End Source File
# Begin Source File

SOURCE=.\UI\UIUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\UIUtils.h
# End Source File
# End Group
# Begin Group "Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Files\Acquier.cpp
# End Source File
# Begin Source File

SOURCE=.\Files\Acquier.h
# End Source File
# Begin Source File

SOURCE=.\Files\Batch.cpp
# End Source File
# Begin Source File

SOURCE=.\Files\Batch.h
# End Source File
# Begin Source File

SOURCE=.\Files\Issuer.cpp
# End Source File
# Begin Source File

SOURCE=.\Files\Issuer.h
# End Source File
# Begin Source File

SOURCE=.\Files\Paramters.cpp
# End Source File
# Begin Source File

SOURCE=.\Files\Paramters.h
# End Source File
# Begin Source File

SOURCE=.\Files\SettleReport.cpp
# End Source File
# Begin Source File

SOURCE=.\Files\SettleReport.h
# End Source File
# Begin Source File

SOURCE=.\Files\Table.cpp
# End Source File
# Begin Source File

SOURCE=.\Files\Table.h
# End Source File
# Begin Source File

SOURCE=.\Files\Terminal.cpp
# End Source File
# Begin Source File

SOURCE=.\Files\Terminal.h
# End Source File
# End Group
# Begin Group "8583"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\8583\8583.cpp
# End Source File
# Begin Source File

SOURCE=.\8583\8583.h
# End Source File
# End Group
# Begin Group "Trnx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Trnx\ITrnxBase.h
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxBakiyeSorgu.cpp
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxBakiyeSorgu.h
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxBase.cpp
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxBase.h
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxDebitYukleme.cpp
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxDebitYukleme.h
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxFactory.h
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxHarcama.cpp
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxHarcama.h
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxKartGuncelle.cpp
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxKartGuncelle.h
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxKrediKartYukleme.cpp
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxKrediKartYukleme.h
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxNakitYukleme.cpp
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxNakitYukleme.h
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxOnline.cpp
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxOnline.h
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxPuanKullanma.cpp
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxPuanKullanma.h
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxPuanSorgu.cpp
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxPuanSorgu.h
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxPuanSorguOnline.cpp
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxPuanSorguOnline.h
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxRefund.cpp
# End Source File
# Begin Source File

SOURCE=.\Trnx\TrnxRefund.h
# End Source File
# End Group
# Begin Group "Utils"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Util\NumFuncs.cpp
# End Source File
# Begin Source File

SOURCE=.\Util\NumFuncs.h
# End Source File
# Begin Source File

SOURCE=.\Util\Tlv.cpp
# End Source File
# End Group
# Begin Group "Crypt"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Crypt\crypt.cpp
# End Source File
# Begin Source File

SOURCE=.\Crypt\crypt.h
# End Source File
# Begin Source File

SOURCE=.\Crypt\des.cpp
# End Source File
# Begin Source File

SOURCE=.\Crypt\des.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
