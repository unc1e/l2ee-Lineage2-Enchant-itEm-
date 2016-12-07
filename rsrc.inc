ID_BTN_DATA_START = 101
ID_BTN_DATA_STOP = 102
ID_BTN_WORK_START = 103
ID_BTN_WORK_STOP = 104
ID_BTN_SPEED = 105
ID_BTN_TYPE = 106
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
directory RT_DIALOG, dialogs, RT_VERSION, versions
resource versions, 1, LANG_NEUTRAL, version
versioninfo version, VOS__WINDOWS32, VFT_APP, VFT2_UNKNOWN,LANG_ENGLISH+SUBLANG_DEFAULT, 0,\
	'FileDescription','L2 Enchant itEm (l2ee.dll)',\
	'LegalCopyright','unc1e aka assassins909 aka FastX, 2016',\
	'FileVersion','1.0',\
	'OriginalFilename','l2ee.dll'

resource dialogs, 9999, LANG_ENGLISH+SUBLANG_DEFAULT, main
	dialog main, 'L2 Enchant itEm (l2ee.dll) by unc1e aka assassins909', 100, 100, 180, 150, WS_CAPTION + WS_POPUP + WS_SYSMENU + DS_MODALFRAME
	dialogitem 'BUTTON', 'Start record', ID_BTN_DATA_START, 10, 10, 75, 15, WS_VISIBLE + WS_TABSTOP + BS_DEFPUSHBUTTON
	dialogitem 'BUTTON', 'Stop record', ID_BTN_DATA_STOP, 95, 10, 75, 15, WS_VISIBLE + WS_TABSTOP + BS_DEFPUSHBUTTON
	dialogitem 'BUTTON', 'Start enchant', ID_BTN_WORK_START, 10, 30, 75, 15, WS_VISIBLE + WS_TABSTOP + BS_DEFPUSHBUTTON
	dialogitem 'BUTTON', 'Stop enchant', ID_BTN_WORK_STOP, 95, 30, 75, 15, WS_VISIBLE + WS_TABSTOP + BS_DEFPUSHBUTTON
	dialogitem 'BUTTON', 'Change speed', ID_BTN_SPEED, 10, 50, 160, 15, WS_VISIBLE + WS_TABSTOP + BS_DEFPUSHBUTTON
	dialogitem 'BUTTON', 'Stack/unstack scrolls', ID_BTN_TYPE, 10, 70, 160, 15, WS_VISIBLE + WS_TABSTOP + BS_DEFPUSHBUTTON
	dialogitem 'EDIT', 'http://tophope.ru/', NULL, 10, 90, 160, 15, WS_VISIBLE + WS_BORDER + WS_TABSTOP + ES_AUTOHSCROLL
	dialogitem 'EDIT', 'http://tophope.ru/members/assassins909.42030/', NULL, 10, 110, 160, 15, WS_VISIBLE + WS_BORDER + WS_TABSTOP + ES_AUTOHSCROLL
	dialogitem 'EDIT', 'https://github.com/unc1e', NULL, 10, 130, 160, 15, WS_VISIBLE + WS_BORDER + WS_TABSTOP + ES_AUTOHSCROLL
enddialog