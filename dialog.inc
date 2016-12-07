proc dialogThread, hInstance
	@@:
	invoke dialogboxparam, [hInstance], 9999, NULL, pDialog, NULL
	jmp @b
endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

proc pDialog, hInstance, uMsg, wParam, lParam
	mov eax, [uMsg]

	cmp eax, WM_COMMAND
	je .wmcommand

	cmp eax, WM_CLOSE
	je .wmclose
	xor eax,eax
	ret

	.wmcommand:
	cmp DWORD[wParam], BN_CLICKED shl 16 + ID_BTN_DATA_START
	je .data_clicked_start

	cmp DWORD[wParam], BN_CLICKED shl 16 + ID_BTN_DATA_STOP
	je .data_clicked_stop

	cmp DWORD[wParam], BN_CLICKED shl 16 + ID_BTN_WORK_START
	je .work_clicked_start

	cmp DWORD[wParam], BN_CLICKED shl 16 + ID_BTN_WORK_STOP
	je .work_clicked_stop

	cmp DWORD[wParam], BN_CLICKED shl 16 + ID_BTN_SPEED
	je .speed_clicked

	cmp DWORD[wParam], BN_CLICKED shl 16 + ID_BTN_TYPE
	je .type_clicked

	jmp .exit
	
	.data_clicked_start:
	mov ebx, [pAddr_unh_requseitem]
	mov eax, ebx
	add eax, [eax+1]
	add eax, 5
	mov [requseitem_retAddr], eax

	invoke virtualprotect, ebx, 5, PAGE_EXECUTE_READWRITE, oldProtect

	mov eax, handler_requseitem
	sub eax, ebx
	sub eax, 5

	mov BYTE[ebx], 0xe9
	push eax
	mov eax, DWORD[ebx+1]
	mov [requseitem_origBytes], eax
	pop eax
	mov DWORD[ebx+1], eax
	jmp .exit

	.data_clicked_stop:
	cmp [requseitem_origBytes], NULL
	je .exit
	mov eax, [requseitem_origBytes]
	mov ebx, [pAddr_unh_requseitem]
	mov [ebx+1], eax
	jmp .exit

	.work_clicked_start:
	mov [work], 1
	jmp .exit

	.work_clicked_stop:
	mov [work], 0
	jmp .exit

	.speed_clicked:
	cmp [timeout], 5100
	je @f
	add [timeout], 500
	jmp .exit
	@@:
	mov [timeout], 100
	jmp .exit

	.type_clicked:
	not [p_stack]
	jmp .exit

	.wmclose:
	invoke endDialog, [hInstance], 1
	.exit:
	mov eax,1
	ret
endp