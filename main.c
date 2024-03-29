#include <stdlib.h>
#include <time.h>

#include "stm32l476xx.h"
#include "LED.h"
#include "Button.h"
#include "game.h"

int main(void) {
	RCC->CR |= RCC_CR_MSIRGSEL;
	RCC->CR = (RCC->CR & ~RCC_CR_MSIRANGE) | RCC_CR_MSIRANGE_10;
	while (!(RCC->CR & RCC_CR_MSIRDY));
	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	GPIOB->MODER = (GPIOB->MODER & 0xFFFFC000u) | 0x00000001u;
	GPIOB->PUPDR = (GPIOB->PUPDR & 0xFFFFC000u) | 0x00001554u;
	
	RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;
	RNG->CR |= RNG_CR_RNGEN;
	
	RCC->CCIPR |= RCC_CCIPR_CLK48SEL;
	
	while (!(RNG->SR & RNG_SR_DRDY));
	
	srand(RNG->DR);

	mastermind();
}
