
#include <stdint.h>

uint8_t g_svc_number = 0;

int main(){

	// jump to uPRIV mode
	__asm volatile("MRS R0,CONTROL \n\t"
					"ORR R0,R0,#1  \n\t"
					"MSR CONTROL,R0 \n\t"
					"ISB \n\t"
					:::"r0","memory");

	// generate the SVC exception
	__asm volatile("SVC #3");

	while(1);
}

__attribute__((naked)) void SVC_Handler(void){

	__asm volatile("TST LR,#4 \n"          // test bit 2 of EXC_RETURN to see which stack
					"ITE EQ\n"			   // if 0, we were using MSP
					"MRSEQ R0,MSP\n"	   // move MSP pointer to R0
					"MRSNE R0,PSP\n"	   // if 1, move PSP into R0
					"B SVC_Handler_C\n");  // Branch to our C logic, passing the pointer in R0

}

void SVC_Handler_C(uint32_t *svc_args){
	// index 6 of the hardware saved stack frame holds the program counter (PC)
	// this points to the instruction after the SVC
	uint32_t stacked_pc = svc_args[6];

	// step back 2bytes to find the address of the SVC instruction
	uint16_t *svc_instruction = (uint16_t *)(stacked_pc -2);

	// lower 8 bits of the instruction contain the immediate value(#3)
	volatile uint8_t svc_number  = (uint8_t)(*svc_instruction & 0xFF);

	g_svc_number = svc_number;
}
