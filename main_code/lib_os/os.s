				;khai bao chung
				AREA |.TEXT|,CODE,READONLY,ALIGN=2
				;tap lenh thumb
				THUMB
				;stack kieu 8 byte
				PRESERVE8
				; bien currentPt da duoc khai bao o dau do trong chuong trinh
				EXTERN currentPt
				;xuat ham ra ben ngoai de su dung trong chuong trinh c
				EXPORT osSchedulerLaunch
				EXPORT PendSV_Handler
				;ham nay da duoc khai bao dau do trong chuong trinh
				IMPORT osSchedulerRoundRobin

;chuong trinh con khoi chay task dau tien trong chuong trinh
osSchedulerLaunch
	LDR R0, =currentPt
	LDR R2, [R0]
	
	LDR SP, [R2]
	POP {R4-R11}
	POP {R0-R3}
	POP {R12}
	ADD SP, SP, #4
	POP {LR}
	ADD SP, SP, #4
	
	CPSIE I
	BX LR

;chuong trinh con thuc hien sau luu, khoi phuc va chuyen task
PendSV_Handler
	CPSID I
	PUSH {R4-R11}
	LDR R0, =currentPt
	LDR R1, [R0]
	
	STR SP, [R1]
	
	PUSH {R0, LR}
	BL osSchedulerRoundRobin
	POP {R0, LR}
	LDR R1, [R0]
	
	LDR SP, [R1]
	POP {R4-R11}
	CPSIE I
	BX LR

	END
		