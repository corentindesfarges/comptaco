; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{3C8BC1D6-4A40-460C-9C15-DE3A0C9055FB}
AppName=ComptaCo
AppVersion=2.2
;AppVerName=ComptaCo 2.2
AppPublisher=Corentin Desfarges
AppPublisherURL=http://corentindesfarges.fr
AppSupportURL=http://corentindesfarges.fr
AppUpdatesURL=http://corentindesfarges.fr
DefaultDirName={pf}\ComptaCo
DefaultGroupName=ComptaCo
OutputDir=D:\Qt\Projets
OutputBaseFilename=comptaco_2.2
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "brazilianportuguese"; MessagesFile: "compiler:Languages\BrazilianPortuguese.isl"
Name: "catalan"; MessagesFile: "compiler:Languages\Catalan.isl"
Name: "corsican"; MessagesFile: "compiler:Languages\Corsican.isl"
Name: "czech"; MessagesFile: "compiler:Languages\Czech.isl"
Name: "danish"; MessagesFile: "compiler:Languages\Danish.isl"
Name: "dutch"; MessagesFile: "compiler:Languages\Dutch.isl"
Name: "finnish"; MessagesFile: "compiler:Languages\Finnish.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"
Name: "german"; MessagesFile: "compiler:Languages\German.isl"
Name: "greek"; MessagesFile: "compiler:Languages\Greek.isl"
Name: "hebrew"; MessagesFile: "compiler:Languages\Hebrew.isl"
Name: "hungarian"; MessagesFile: "compiler:Languages\Hungarian.isl"
Name: "italian"; MessagesFile: "compiler:Languages\Italian.isl"
Name: "japanese"; MessagesFile: "compiler:Languages\Japanese.isl"
Name: "norwegian"; MessagesFile: "compiler:Languages\Norwegian.isl"
Name: "polish"; MessagesFile: "compiler:Languages\Polish.isl"
Name: "portuguese"; MessagesFile: "compiler:Languages\Portuguese.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"
Name: "scottishgaelic"; MessagesFile: "compiler:Languages\ScottishGaelic.isl"
Name: "serbiancyrillic"; MessagesFile: "compiler:Languages\SerbianCyrillic.isl"
Name: "serbianlatin"; MessagesFile: "compiler:Languages\SerbianLatin.isl"
Name: "slovenian"; MessagesFile: "compiler:Languages\Slovenian.isl"
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"
Name: "turkish"; MessagesFile: "compiler:Languages\Turkish.isl"
Name: "ukrainian"; MessagesFile: "compiler:Languages\Ukrainian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\ComptaCo.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\categorie.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\ComptaCo.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\dao.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\favori.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\icudt53.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\icuin53.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\icuuc53.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\libgcc_s_dw2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\libwinpthread-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\magasin.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\main.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\moc_view_accueil.cpp"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\moc_view_accueil.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\moc_view_addbox.cpp"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\moc_view_addbox.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\moc_view_categories.cpp"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\moc_view_categories.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\moc_view_comptes.cpp"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\moc_view_comptes.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\moc_view_favoris.cpp"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\moc_view_favoris.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\moc_view_magasins.cpp"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\moc_view_magasins.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\operation.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\qrc_resources.cpp"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\qrc_resources.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\qselect.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\Qt5Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\Qt5Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\Qt5Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\sqlite3.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\typepmt.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\utilities.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\view_accueil.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\view_addbox.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\view_categories.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\view_comptes.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\view_favoris.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\view_magasins.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\platforms\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\Qt\Projets\build-ComptaCo-Desktop_Qt_5_4_1_MinGW_32bit-Release\release\imageformats\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\ComptaCo"; Filename: "{app}\ComptaCo.exe"
Name: "{commondesktop}\ComptaCo"; Filename: "{app}\ComptaCo.exe"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\ComptaCo"; Filename: "{app}\ComptaCo.exe"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\ComptaCo.exe"; Description: "{cm:LaunchProgram,ComptaCo}"; Flags: nowait postinstall skipifsilent
