// 开始任务函数。
.global own_start_tsk
own_start_tsk:
	ldr r4, =pcur_TCB
    ldr r5, =ptsk_rdy_head
    ldr r5, [r5]
    str r5, [r4] 

    ldr r4, =pcur_TCB                   
    ldr r4, [r4]               
    ldr sp, [r4]               

    ldmfd sp!, {r4}            
    msr spsr, r4
    ldmfd sp!, {r4}            
    msr cpsr, r4
    ldmfd sp!, {r0-r12, lr, pc} 

// 中断处理函数。
.global own_irq_handle
own_irq_handle:
	stmfd sp!, {r0-r3, r12, lr}  

    bl do_irq	
	
	ldmfd sp!, {r0-r3, r12, lr}
	
    stmfd sp!, {r0-r3}
    mov r1, sp
    sub r2, lr, #4
	add sp, sp, #16

    mrs r3, spsr
    orr r0, r3, #0xc0
    msr spsr_c, r0

    msr cpsr_c, #0x13

    stmfd sp!, {r2}             
    stmfd sp!, {r4-r12, lr}     
    mov r4, r1                 
    mov r5, r3
    ldmfd r4!, {r0-r3}
    stmfd sp!, {r0-r3}          
    stmfd sp!, {r5}            
    mrs r4, spsr
    stmfd sp!, {r4}

	ldr r4, =pcur_TCB                  
    ldr r4, [r4]               
    str sp, [r4]               

	b own_start_tsk 

// 进入临界区函数。
.global own_enter_critical
own_enter_critical:
    mrs r0, cpsr
    orr r0, r0, #0xc0
    msr cpsr_c, r0
    mov pc, lr

// 退出临界区函数。
.global own_exit_critical
own_exit_critical:
    mrs r0, cpsr
    bic r0, r0, #0xc0
    msr cpsr_c, r0
    mov pc, lr
