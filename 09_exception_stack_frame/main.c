
#include <stdint.h>

volatile uint32_t stacked_r0;
volatile uint32_t stacked_r1;
volatile uint32_t stacked_r2;
volatile uint32_t stacked_r3;
volatile uint32_t stacked_pc;

void trigger_exception(void);

int main(){

	trigger_exception();

	while(1);
}

void SVC_Handler(void){

	uint32_t *stack_frame;

	// Identify which was used before the exception
	__asm volatile(
			"TST LR,#4 \n"
			"ITE EQ \n"
			"MRSEQ %0,MSP \n"
			"MRSNE %0,PSP \n"
			: "=&r"(stack_frame)
            :
            :"cc");

	// Read automatically stacked register values
	stacked_r0 = stack_frame[0];
	stacked_r1 = stack_frame[1];
	stacked_r2 = stack_frame[2];
	stacked_r3 = stack_frame[3];

	stacked_pc = stack_frame[6];
}


void trigger_exception(void){

	__asm volatile(
			"MOV R0,#10\n"
			"MOV R1,#20\n"
			"MOV R2,#30\n"
			"MOV R3,#40\n"
			"SVC #0 \n"
			:
			:
			:"r0","r1","r2","r3","memory");
}

