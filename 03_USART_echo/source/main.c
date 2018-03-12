#include "stm32f7xx.h"
#include "rcc.h"


/******************************************************************************/
/* Private variables **********************************************************/
/******************************************************************************/
/* USART BAUDRATE */
#define USART_BAUDRATE      115200u


/******************************************************************************/
/* Interrupts *****************************************************************/
/******************************************************************************/
/**
 * USART1 interrupt handler
 */
void USART1_IRQHandler(void) {
    if ((USART1->ISR & USART_ISR_RXNE) == USART_ISR_RXNE) {
        USART1->TDR = USART1->RDR;
    }
}


/******************************************************************************/
/* Main ***********************************************************************/
/******************************************************************************/
int main(void) {
    /* Init system clock */
    SystemClock_Init();

    /* PORTA clock enable */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    /* PORTB clock enable */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    /* PA9 in USART1_Tx AF7 */
    GPIOA->AFR[1u] |= (7u << 4u);
    /* PB7 in USART1_Rx AF7 */
    GPIOB->AFR[0u] |= (7u << 28u);
    /* PA9 in USART1_Tx AF */
    GPIOA->MODER |= GPIO_MODER_MODER9_1;
    /* PB7 in USART1_Rx AF */
    GPIOB->MODER |= GPIO_MODER_MODER7_1;

    /* USART1 clock enable */
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    /* USART1 receive enable */
    USART1->CR1 |= USART_CR1_RE;
    /* USART1 transmit enable */
    USART1->CR1 |= USART_CR1_TE;
    /* USART1 Rx interrupt enable */
    USART1->CR1 |= USART_CR1_RXNEIE;
    /* Set USART1 baudrate */
    USART1->BRR = GetPCLK2Frequency() / USART_BAUDRATE;
    /* Set USART1 interrupt priority */
    NVIC_SetPriority(USART1_IRQn, 1u);
    /* Enable USART1 interrupts */
    NVIC_EnableIRQ(USART1_IRQn);
    /* Enable USART1 */
    USART1->CR1 |= USART_CR1_UE;

    while (1u) {

    }
}
