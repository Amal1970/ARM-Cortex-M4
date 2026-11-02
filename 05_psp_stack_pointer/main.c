#include <stdint.h>

#define SRAM_START  		0x20000000U
#define SRAM_SIZE   		(128U * 1024U)
#define STACK_END 			((SRAM_START) + (SRAM_SIZE))

#define MSP_STACK_START		STACK_END
#define PSP_STACK_START		((MSP_STACK_START) - (1024U))

int main(){

	// read initial MSP and PSP values
	uint32_t msp_value;
	uint32_t psp_value;

	__asm volatile("MRS %0,MSP":"=r"(msp_value));
	__asm volatile("MRS %0,PSP":"=r"(psp_value));

	// load PSP with new value
	__asm volatile("MSR PSP,%0"::"r"(PSP_STACK_START));
	__asm volatile("MRS %0,PSP":"=r"(psp_value));

	// switch from thread mode MSP to PSP
	__asm volatile(
		"MRS R0,CONTROL \n\t"
		"ORR R0,R0,#2 \n\t"
		"MSR CONTROL,R0 \n\t"
		"ISB  \n\t"
		: 				// no output operands
		:				// no input operands
		: "r0","memory" // clobber list
	);

	while(1);

	return 0;
}
