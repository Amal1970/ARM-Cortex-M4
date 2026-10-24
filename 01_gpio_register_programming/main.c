#include <stdint.h>

#define LED_GREEN		12
#define LED_ORANGE		13
#define LED_RED			14
#define LED_BLUE		15

#define GPIOD_MODER		*((volatile uint32_t *)0x40020C00U)
#define GPIOD_ODR		*((volatile uint32_t *)0x40020C14U)
#define RCC_AHB1ENR     *((volatile uint32_t *)0x40023830U)

void gpiod_clk_enable(void);
void gpiod_init(void);
void led_on(uint8_t led_pin);
void led_off(uint8_t led_pin);
void delay(void);

int main(){

	gpiod_init();

	while(1){

		// turn on green for 500ms
		led_on(LED_GREEN);
		delay();
		led_off(LED_GREEN);

		// turn on orange for 500ms
		led_on(LED_ORANGE);
		delay();
		led_off(LED_ORANGE);

		// turn on red for 500ms
		led_on(LED_RED);
		delay();
		led_off(LED_RED);

		// turn on blue for 500ms
		led_on(LED_BLUE);
		delay();
		led_off(LED_BLUE);
	}
}

// Enable clock for GPIOD (bit 3 in RCC_AHB1ENR)
void gpiod_clk_enable(void){
	RCC_AHB1ENR |=(1U<<3);
}

// Configure pins 12,13,14 and 15 as general purpose Output
void gpiod_init(void){

	// enable clock
	gpiod_clk_enable();

	// set the port type to output
	// all other as default settings

	// clear the values
	GPIOD_MODER &= ~((3U<<24)|(3U<<26)|(3U<<28)|(3U<<30));

	// set to output mode
	GPIOD_MODER |= ((1U<<24)|(1U<<26)|(1U<<28)|(1U<<30));

}

void led_on(uint8_t led_pin){
	GPIOD_ODR |= (1U<<led_pin);
}

void led_off(uint8_t led_pin){
	GPIOD_ODR &= ~(1U<<led_pin);
}

void delay(void){
	for(volatile uint32_t i = 0;i<2000000U;i++);
}
