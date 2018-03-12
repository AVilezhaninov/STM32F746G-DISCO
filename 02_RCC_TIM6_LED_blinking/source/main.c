#include "stm32f7xx.h"
#include "rcc.h"


/******************************************************************************/
/* Define *********************************************************************/
/******************************************************************************/
/* TIM6 prescaler and auto reload values for 0.5 sec interrupt interval */
#define TIM6_PSC    4319u
#define TIM6_ARR    12499u;


/******************************************************************************/
/* Interrupts *****************************************************************/
/******************************************************************************/
/**
 * TIM6 interrupt handler
 */
void TIM6_DAC_IRQHandler(void) {
    /* Clear TIM6 update interrupt flag */
    TIM6->SR &= ~TIM_SR_UIF;
    /* Toggle LED */
    GPIOI->ODR ^= GPIO_ODR_ODR_1;
}




/******************************************************************************/
/* Main ***********************************************************************/
/******************************************************************************/
int main(void) {
    /* Init system clock */
    SystemClock_Init();

    /* Enable GPIOI clock */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;
    /* GPIOI pin 1 in push-pull mode */
    GPIOI->MODER |= GPIO_MODER_MODER1_0;

    /* Enable TIM6 clock */
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
    /* Set TIM6 prescaler */
    TIM6->PSC = TIM6_PSC;
    /* Set TIM6 auto reload value */
    TIM6->ARR = TIM6_ARR;
    /* Enable TIM6 update interrupt */
    TIM6->DIER |= TIM_DIER_UIE;
    /* Set TIM6 interrupt priority */
    NVIC_SetPriority(TIM6_DAC_IRQn, 1u);
    /* Enable TIM6 interrupt */
    NVIC_EnableIRQ(TIM6_DAC_IRQn);
    /* Enable TIM6 timer */
    TIM6->CR1 |= TIM_CR1_CEN;

    while (1u) {

    }
}
