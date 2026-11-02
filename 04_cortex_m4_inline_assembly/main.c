#include <stdint.h>

#define LED_GREEN		12 // BIT 0
#define LED_ORANGE		13 // BIT 1
#define LED_RED			14 // BIT 2
#define LED_BLUE		15 // BIT 3

#define GPIOD_MODER		*((volatile uint32_t *)0x40020C00U)
#define GPIOD_ODR		*((volatile uint32_t *)0x40020C14U)
#define RCC_AHB1ENR     *((volatile uint32_t *)0x40023830U)

void delay(void){
	for(int i= 0;i<200000;i++);
}

void led_gpio_init(void);
void led_display(uint32_t value);
void led_on(uint8_t led_pin);
void led_off(uint8_t led_pin);

uint32_t asm_add(uint32_t a, uint32_t b);
uint32_t asm_sub(uint32_t a, uint32_t b);
uint32_t asm_and(uint32_t a, uint32_t b);
uint32_t asm_orr(uint32_t a, uint32_t b);
uint32_t asm_eor(uint32_t a, uint32_t b);

int main(){

	led_gpio_init();

	uint32_t a = 6;
	uint32_t b = 4;


	// addition
	led_display(asm_add(a,b));
	delay();
	
	// subtraction
	led_display(asm_sub(a,b));
	delay();
	
	// and operation
	led_display(asm_and(a,b));
	delay();
	
	// or operation
	led_display(asm_orr(a,b));
	delay();
	
	// xor operation
	led_display(asm_eor(a,b));
	delay();
	
	led_off(LED_GREEN);
	led_off(LED_ORANGE);
	led_off(LED_RED);
	led_off(LED_BLUE);

	while(1);

}

void led_on(uint8_t led_pin){
	GPIOD_ODR |= (1<<led_pin);
}

void led_off(uint8_t led_pin){
	GPIOD_ODR &= ~(1<<led_pin);
}

void led_gpio_init(void){
	// enable peripheral clock
	RCC_AHB1ENR |= (1<<3);

	// enable output mode
	// clear the values
	GPIOD_MODER &= ~((3U<<24)|(3U<<26)|(3U<<28)|(3U<<30));

	// set to output mode
	GPIOD_MODER |= ((1U<<24)|(1U<<26)|(1U<<28)|(1U<<30));

	// led off all
	GPIOD_ODR &= ~((1U << 12)|(1U << 13)|(1U << 14)|(1U << 15));

}

void led_display(uint32_t value){
	for(uint32_t i = 0;i<4;i++){
		// bit 0 to 3
		if((value>>i)&1){
			led_on((LED_GREEN+i));
		}
		else{
			led_off((LED_GREEN+i));
		}
	}
}

uint32_t asm_add(uint32_t a, uint32_t b){
	uint32_t sum;
	// the values are now in the c variables
	__asm volatile("ADD %0,%1,%2":"=r"(sum):"r"(a),"r"(b));
	return sum;
}

uint32_t asm_sub(uint32_t a,uint32_t b){
	uint32_t sub;

	__asm volatile("SUB %0,%1,%2":"=r"(sub):"r"(a),"r"(b));

	return sub;
}

uint32_t asm_and(uint32_t a, uint32_t b){
	uint32_t and;

	__asm volatile("AND %0,%1,%2":"=r"(and):"r"(a),"r"(b));

	return and;
}

uint32_t asm_orr(uint32_t a, uint32_t b){
	uint32_t orr;

	__asm volatile("ORR %0,%1,%2":"=r"(orr):"r"(a),"r"(b));

	return orr;
}

uint32_t asm_eor(uint32_t a, uint32_t b){
	uint32_t eor;

	__asm volatile("EOR %0,%1,%2":"=r"(eor):"r"(a),"r"(b));

	return eor;
}

