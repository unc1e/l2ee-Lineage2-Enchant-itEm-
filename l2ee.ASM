format PE DLL
include 'win32a.inc'
entry DllMain

;//////////////////////////////////////////////////////////
;//////////////////////////////////////////////////////////

section '.data' data readable writeable
	cMsg db 'By unc1e aka assassins909 for http://tophope.ru', 0

	reqenterworld_retAddr dd ?
	unh dd ?

	oldProtect dd ?

	requseitem_origBytes dd ?
	requseitem_retAddr dd ?
	requseitem_w_oid dd ?
	requseitem_w_ctrl dd ?
	requseitem_s_oid dd ?
	requseitem_s_ctrl dd ?
	stage dd 0

	work dd 0
	p_stack dd 0
	timeout dd 100
	record dd 0
	
;//////////////////////////////////////////////////////////
;//////////////////////////////////////////////////////////

section '.code' code executable
proc DllMain, hInstance, fdwReason, lpvReserved
	cmp [fdwReason], DLL_PROCESS_ATTACH
	je @f
	ret

	@@:
	invoke disablethreadlibrarycalls, [hInstance]
	invoke outputdebugstring, cMsg
	invoke createthread, NULL, NULL, workThread, NULL, NULL, NULL
	invoke createthread, NULL, NULL, dialogThread, [hInstance], NULL, NULL
	mov eax, TRUE
	ret
endp

include 'proc.inc'
include 'dialog.inc'

;//////////////////////////////////////////////////////////
;//////////////////////////////////////////////////////////

section '.idata' import data readable
library kernel32, 'kernel32.dll',\ ;dll from Windows
	user32, 'user32.dll',\	   ;dll from Windows
	core, 'Core.dll',\	   ;dll from Lineage2
	engine, 'engine.dll'	   ;dll from Lineage2

import kernel32,\
	createthread, 'CreateThread',\
	disablethreadlibrarycalls, 'DisableThreadLibraryCalls',\
	virtualprotect, 'VirtualProtect',\
	outputdebugstring, 'OutputDebugStringA',\
	sleep, 'Sleep'

import core,\
	pAddr_l2ps_create, '??0L2ParamStack@@QAE@H@Z',\
	pAddr_l2ps_clear, '?Clear@L2ParamStack@@QAEXXZ',\
	pAddr_l2ps_pushback, '?PushBack@L2ParamStack@@QAEHPAX@Z',\
	pAddr_l2ps_top, '?Top@L2ParamStack@@QAEPAXXZ',\
	pAddr_l2ps_free, '??1L2ParamStack@@QAE@XZ'

import engine,\
	pAddr_unh_reqenterworld, '?RequestEnterWorldPacket@UNetworkHandler@@UAEHHPAHKKKK@Z',\ ;for get unh
	pAddr_unh_requseitem, '?RequestUseItem@UNetworkHandler@@UAEHAAVL2ParamStack@@@Z',\
	pAddr_unh_reqenchitem, '?RequestEnchantItem@UNetworkHandler@@UAEHH@Z'

import user32,\
	dialogboxparam, 'DialogBoxParamA',\
	endDialog, 'EndDialog'

;//////////////////////////////////////////////////////////
;//////////////////////////////////////////////////////////

section '.rsrc' resource readable
include 'rsrc.inc'

;//////////////////////////////////////////////////////////
;//////////////////////////////////////////////////////////

section '.reloc' fixups data readable discardable