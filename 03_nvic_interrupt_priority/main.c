
#include <stdint.h>

// LED = PD12
// BUTTON = PA0

#define LED_GREEN 		12
#define EXIT0_IRQ_NO	6

#define RCC_AHB1ENR     	*((volatile uint32_t *)0x40023830U)
#define RCC_APB2ENR     	*((volatile uint32_t *)0x40023844U)

#define GPIOD_MODER			*((volatile uint32_t *)0x40020C00U)
#define GPIOD_ODR			*((volatile uint32_t *)0x40020C14U)

#define GPIOA_MODER			*((volatile uint32_t *)0x40020000U)
#define GPIOA_IDR			*((volatile uint32_t *)0x40020010U)

#define SYSCFG_EXTICR1		*((volatile uint32_t *)0x40013808U)

#define EXTI_IMR			*((volatile uint32_t *)0x40013C00U)
#define EXTI_RTSR			*((volatile uint32_t *)0x40013C08U)
#define EXTI_PR				*((volatile uint32_t *)0x40013C14U)

#define NVIC_ISER0    		*((volatile uint32_t *)0xE000E100U)
#define NVIC_IPR6 			*((volatile uint8_t *)0xE000E406U)

void gpio_init(void);
void exti_init(void);
void nvic_init(void);

void led_off(uint8_t pin);
void led_toggle(uint8_t pin);

int main(){

	gpio_init();

	led_off(LED_GREEN);

	exti_init();

	while(1);
}

void gpio_init(void){
	//enable clock
	RCC_AHB1ENR |= (1<<0);
	RCC_AHB1ENR |= (1<<3);

	// set mode
	GPIOD_MODER &= ~(3<<24);
	GPIOD_MODER	|= (1<<24);
	GPIOA_MODER &= ~(3<<0);

}

void exti_init(void){
	// enable clock for SYSCFG
	RCC_APB2ENR |= (1<<14);

	// configure PA0 to EXTI0
	SYSCFG_EXTICR1 &= ~(0xF << 0);

	// enable EXTI0 interrupt
	EXTI_IMR |= (1<<0);

	// enable trigger rising
	EXTI_RTSR |= (1<<0);

	// enable it in NVIC
	nvic_init();
}

void nvic_init(void){

	// set priority
	NVIC_IPR6 = (2<<4);

	// enable interrupt for EXTI0
	NVIC_ISER0 |= (1<<EXIT0_IRQ_NO);
}

void led_toggle(uint8_t pin){
	GPIOD_ODR ^= (1<<pin);
}

void led_off(uint8_t pin){
	GPIOD_ODR &= ~(1<<pin);
}

void EXTI0_IRQHandler(void){
	// button pressed
	if(EXTI_PR & (1<<0)){
		// clear pending bit
		EXTI_PR = (1<<0);
		// do the toggling
		led_toggle(LED_GREEN);

	}
}
