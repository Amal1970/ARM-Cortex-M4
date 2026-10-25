
#include <stdint.h>

#define SYSCLK				16000000U
#define TICK_HZ				1000U
#define SYSTICK_RELOAD		((SYSCLK/TICK_HZ)-1U)

#define SYST_CSR  			*((volatile uint32_t *)0xE000E010U)
#define SYST_RVR  			*((volatile uint32_t *)0xE000E014U)
#define SYST_CVR  			*((volatile uint32_t *)0xE000E018U)


#define LED_GREEN	 		12

#define GPIOD_MODER			*((volatile uint32_t *)0x40020C00U)
#define GPIOD_ODR			*((volatile uint32_t *)0x40020C14U)
#define RCC_AHB1ENR     	*((volatile uint32_t *)0x40023830U)

#define DELAY_500		500U

volatile uint32_t g_tick_count = 0;

void led_gpio_init(void);
void systick_init(uint32_t count);
void led_toggle(uint8_t pin);
void systick_delay_ms(uint32_t delay_ms);

int main(){

	// initialize LED
	led_gpio_init();

	// initialize SysTick
	systick_init(SYSTICK_RELOAD);

	while(1){
		led_toggle(LED_GREEN);
		systick_delay_ms(DELAY_500);
		led_toggle(LED_GREEN);
		systick_delay_ms(DELAY_500);
	}
}

void led_gpio_init(void){
	// enable the clock
	RCC_AHB1ENR |=(1U<<3); // GPIO D

	// set the port type to output
	// all other as default settings

	// clear the values
	GPIOD_MODER &= ~(3U<<24);

	// set to output mode
	GPIOD_MODER |= (1U<<24);
}

void systick_init(uint32_t count_value){

	// 1. program the reload value
	SYST_RVR = (count_value)&0x00FFFFFF;

	// 2. clear current value
	SYST_CVR = 0;

	// program control and status register
	// 1. enable exception
	SYST_CSR |=(1<<1);
	// 2. indicate the clock source
	SYST_CSR |=(1<<2);
	// 3. enable the counter
	SYST_CSR |=(1<<0);
}

void led_toggle(uint8_t pin){
	GPIOD_ODR ^= (1<<pin);
}


void systick_delay_ms(uint32_t delay_ms){

	uint32_t start_tick = g_tick_count;

	while((g_tick_count - start_tick)<delay_ms);
}

void SysTick_Handler(void){
	g_tick_count++;
}
