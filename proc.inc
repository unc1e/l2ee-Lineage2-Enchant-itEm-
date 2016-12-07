proc workThread
	mov ebx, [pAddr_unh_reqenterworld]
	mov eax, ebx
	add eax, [eax+1]
	add eax, 5
	mov [reqenterworld_retAddr], eax

	invoke virtualprotect, ebx, 5, PAGE_EXECUTE_READWRITE, oldProtect

	mov eax, handler_reqenterworld
	sub eax, ebx
	sub eax, 5
	
	mov BYTE[ebx], 0xe9
	mov DWORD[ebx+1], eax
	
	
	local l2Stack[16]:BYTE
	lea esi, [l2Stack]
	push 10
	mov ecx, esi
	call [pAddr_l2ps_create]

	@@:
	cmp [work], 0
	je @b

	mov ecx, esi
	call [pAddr_l2ps_clear]

	push [requseitem_s_oid]
	cmp [p_stack], 0
	jne .workThread_isStack
	dec [requseitem_s_oid]
	.workThread_isStack:
	mov ecx, esi
	call [pAddr_l2ps_pushback]
	push [requseitem_s_ctrl]
	mov ecx, esi
	call [pAddr_l2ps_pushback]

	push esi
	mov ecx, [unh]
	call [pAddr_unh_requseitem]

	push [requseitem_w_oid]
	mov ecx, [unh]
	call [pAddr_unh_reqenchitem]

	invoke sleep, [timeout]
	jmp @b
endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

proc handler_reqenterworld
;;;;;;;;;;;;;;change a data
	mov [unh], ecx
;;;;;;;;;;;;;;return to the original function
	jmp [reqenterworld_retAddr]
endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

proc handler_requseitem
;;;;;;;;;;;;;;change a data
	push esi
	push eax
	push ecx

	mov esi, [esp+16]
	mov ecx, esi
	call [pAddr_l2ps_top]
	cmp [stage], 0
	jne @f
	mov [requseitem_w_oid], eax
	jmp .requseitem_step2
	@@:
	mov [requseitem_s_oid], eax

	.requseitem_step2:
	mov ecx, esi
	call [pAddr_l2ps_top]
	cmp [stage], 0
	jne @f
	mov [requseitem_w_ctrl], eax
	jmp .requseitem_step3
	@@:
	mov [requseitem_s_ctrl], eax

	.requseitem_step3:
	cmp [stage], 0
	jne @f
	push [requseitem_w_oid]
	jmp .requseitem_step4
	@@:
	push [requseitem_s_oid]
	.requseitem_step4:
	mov ecx, esi
	call [pAddr_l2ps_pushback]

	cmp [stage], 0
	jne @f
	push [requseitem_w_ctrl]
	jmp .requseitem_step5
	@@:
	push [requseitem_s_ctrl]
	.requseitem_step5:
	mov ecx, esi
	call [pAddr_l2ps_pushback]

	pop ecx
	pop eax
	pop esi
	not [stage]
;;;;;;;;;;;;;;return to the original function
	jmp [requseitem_retAddr]
endp