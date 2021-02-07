#include "main.h"
#include "stm32f303xe.h"
#include "RCCConfig.h"
#include "Delay.h"

void gpioConfig (void){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	GPIOA->MODER |= (1<<10);

	GPIOA->OTYPER |= 0;
	GPIOA->OSPEEDR |= 0;
}

int main(void){

	sysClockConfig();
	TIM6Config();
	gpioConfig();

	while(1){

		GPIOA->BSRR |= (1<<5);
		Delay_ms (1000);
		GPIOA->BSRR |= (1<<5)<<16;
		Delay_ms (1000);
	}
}
