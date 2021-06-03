PUBLIC	?C_STARTUP        	;向外部申明，ROM运行起始位置
EXTRN  IDATA(process_stack)
EXTRN  CODE(?C_START)
EXTRN  CODE(TaskSwitch)

?C_STARTUP:
ORG     0x0000
	LJMP    InitSP
ORG     0x000B
    LJMP    Timer0Interrupt
ORG     0x00C9
InitSP:
    MOV     SP,#(process_stack)
    JMP     ?C_START
RET

Timer0Interrupt:
    PUSH    ACC
    PUSH    B
    PUSH    PSW
    PUSH    DPH
    PUSH    DPL
    PUSH    0x00
    PUSH    0x01
    PUSH    0x02
    PUSH    0x03
    PUSH    0x04
    PUSH    0x05
    PUSH    0x06
    PUSH    0x07
    LCALL   TaskSwitch
    POP     0x07
    POP     0x06
    POP     0x05
    POP     0x04
    POP     0x03
    POP     0x02
    POP     0x01
    POP     0x00
    POP     DPL
    POP     DPH
    POP     PSW
    POP     B
    POP     ACC
RETI

END

