
#include <stdint.h>

volatile uint32_t initial_control = 0;
volatile uint32_t unpriv_control = 0;
volatile uint32_t exception_status = 0;
volatile uint32_t active_exception = 0;

int main(void)
{
    // Read initial CONTROL register
    __asm volatile(
        "MRS %0, CONTROL"
        : "=r"(initial_control)
    );

    // Switch Thread mode to unprivileged
    __asm volatile(
        "MRS R0, CONTROL   \n\t"
        "ORR R0, R0, #1    \n\t"
        "MSR CONTROL, R0   \n\t"
        "ISB               \n\t"
        ::: "r0", "memory"
    );

    // Verify updated CONTROL register
    __asm volatile(
        "MRS %0, CONTROL"
        : "=r"(unpriv_control)
    );

    // Generate SVC exception
    __asm volatile("SVC #0");

    while (1);
}

void SVC_Handler(void)
{
    // Record the active exception number
    __asm volatile(
        "MRS %0, IPSR"
        : "=r"(active_exception)
    );

    exception_status = 1;
}
