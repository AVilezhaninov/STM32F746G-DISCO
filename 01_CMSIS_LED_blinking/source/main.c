#include "stm32f7xx.h"


#define TOGGLE_DELAY    160000


int main(void) {
    /* Enable GPIOI clock */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;
    /* GPIOI pin 1 in push-pull mode */
    GPIOI->MODER |= GPIO_MODER_MODER1_0;

    while (1) {
        /* Toggle GPIOI pin 1 */
        GPIOI->ODR ^= GPIO_ODR_ODR_1;
        /* Toggle delay */
        for (volatile int i = 0; i < TOGGLE_DELAY; ++i) {
            ;
        }
    }
}
