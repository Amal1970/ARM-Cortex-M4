#include <stdint.h>

volatile uint32_t fault_triggered = 0;
volatile uint32_t fault_completed = 0;
volatile uint32_t fault_value = 0;

int main(){
    fault_triggered = 1;

    // deliberately access an invalid memory address
    volatile uint32_t *fault_address = (volatile uint32_t *)0xFFFFFFFU;

    // this memory access should trigger a fault
    fault_value = *fault_address;

    // this statement should never execute
    fault_completed = 1;

    while(1);
}

void HardFault_Handler(void){
    while(1){
        
    }
}