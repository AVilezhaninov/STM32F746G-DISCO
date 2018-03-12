#include "RCC.h"


/******************************************************************************/
/* Extern *********************************************************************/
/******************************************************************************/
extern uint32_t SystemCoreClock;
extern const uint8_t APBPrescTable[];
extern void SystemCoreClockUpdate(void);


/******************************************************************************/
/* Define *********************************************************************/
/******************************************************************************/
#define PLL_M   25
#define PLL_N   432
#define PLL_P   2
#define PLL_Q   2

#define AHB_PRESCALER     RCC_CFGR_HPRE_DIV1
#define APB1_PRESCALER    RCC_CFGR_PPRE1_DIV4
#define APB2_PRESCALER    RCC_CFGR_PPRE2_DIV2


/******************************************************************************/
/* Exported functions *********************************************************/
/******************************************************************************/
/**
 * Set system clocks
 */
void SystemClock_Init(void) {
    /* Configure the main internal regulator output voltage */
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;

    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);
    /* Wait till HSE is ready */
    while ((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY) {
        ;
    }

    /* Configure the main PLL clock source */
    RCC->PLLCFGR = PLL_M |
                   (PLL_N << 6u) |
                   (((PLL_P >> 1u) - 1u) << 16u) |
                   (RCC_PLLCFGR_PLLSRC_HSE) |
                   (PLL_Q << 24u);

    /* Enable the main PLL */
    RCC->CR |= RCC_CR_PLLON;
    /* Wait till PLL is ready */
    while ((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY) {
        ;
    }

    /* Enable the Over-drive */
    PWR->CR1 |= PWR_CR1_ODEN;
    while ((PWR->CSR1 & PWR_CSR1_ODRDY) != PWR_CSR1_ODRDY) {
        ;
    }

    /* Enable the Over-drive switch */
    PWR->CR1 |= PWR_CR1_ODSWEN;
    while ((PWR->CSR1 & PWR_CSR1_ODSWRDY) != PWR_CSR1_ODSWRDY) {
        ;
    }

    /* Configure Flash prefetch and wait state */
    FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_7WS;

    /* Set HCLK division factor */
    RCC->CFGR |= AHB_PRESCALER;
    /* Set PCLK1 division factor */
    RCC->CFGR |= APB1_PRESCALER;
    /* Set PCLK2 division facror */
    RCC->CFGR |= APB2_PRESCALER;

    /* Select the main PLL as system clock source */
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    /* Wait till the main PLL is used as system clock source */
    while ((RCC->CFGR & RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL) {
        ;
    }

    SystemCoreClockUpdate();
}


/**
 * Get HCLK frequency
 * @return  HCLK frequency
 */
uint32_t GetHCLKFrequency(void) {
    return SystemCoreClock;
}


/**
 * Get PCLK1 frequency
 * @return  PCLK1 frequency
 */
uint32_t GetPCLK1Frequency(void) {
    return (GetHCLKFrequency() >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos]);
}


/**
 * Get PCLK2 frequency
 * @return  PCLK2 frequency
 */
uint32_t GetPCLK2Frequency(void) {
    return (GetHCLKFrequency() >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos]);
}


/**
 * Blocking delay in us
 * @param delay [us]
 */
void StupidDelay_us(volatile uint32_t delay) {
    delay *= (SystemCoreClock / 1000000u);

    while (delay-- > 0u) {
        ;
    }
}


/**
 * Blocking delay in ms
 * @param delay [ms]
 */
void StupidDelay_ms(volatile uint32_t delay) {
    delay *= (SystemCoreClock / 1000u);

    while (delay-- > 0u) {
        ;
    }
}
