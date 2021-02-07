/*
 * RCCConfig.h
 *
 *  Created on: Jan 29, 2021
 *      Author: kdaniele
 */

#ifndef SRC_RCCCONFIG_H_
#define SRC_RCCCONFIG_H_

// f=48MHz

void sysClockConfig (void)
{
	/* ***************** STEPS FOLLOWED ******************

	1. Enable HSE and wait for the HSE to become Ready
	2. Set the POWER ENABLE CLOCK  and VOLTAGE REGULATOR
	3. Configure the FLASH PREFETCH and the LATENCY Related Settings
	4. Configure the PRESCALERS HCLK, PCLK1, PCLK2
	5. Configure the MAIN PLL
	6. Enable the PLL and wait for it to become ready
	7. Select the Clock Source and wait for it to be set

	*************************************************** */

	//1. Enable HSI and wait for the HSI to become Ready

	RCC->CR |= RCC_CR_HSION;
	while(!(RCC->CR & RCC_CR_HSIRDY));

	//2. Set the POWER ENABLE CLOCK

	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

	//3. Configure the FLASH PREFETCH and the LATENCY Related Settings

	FLASH->ACR |= FLASH_ACR_PRFTBE;
	FLASH->ACR |= FLASH_ACR_LATENCY_1;  //if 24 MHz < HCLK ≤ 48 MHz

	//4. Configure the PRESCALERS HCLK, PCLK1, PCLK2

	//ahb pr
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	//apb2 pr
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
	//apb1 pr
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

	//5. Configure the MAIN PLL

	//PLLMUL 6
	RCC->CFGR |= RCC_CFGR_PLLMUL6;

	//Source of PLL

	RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_PREDIV;

	//6. Enable the PLL and wait for it to become ready

	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));

	//7. Select the Clock Source and wait for it to be set

	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}



#endif /* SRC_RCCCONFIG_H_ */
