/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef RCC_H
#define RCC_H


/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx.h"


/* Exported functions --------------------------------------------------------*/
void SystemClock_Init(void);

uint32_t GetHCLKFreq(void);
uint32_t GetPCLK1Freq(void);
uint32_t GetPCLK2Freq(void);


#endif /* RCC_H */
