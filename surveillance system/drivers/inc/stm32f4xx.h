



#ifndef INC_STM32F4XX_H_
#define INC_STM32F4XX_H_
#include <stdint.h>

// PROCESSOR SPECIFIC DETAILS

#define SYSTICK_BASE				 ((volatile uint32_t*)0xE000E010U)

//ARM Cortex M4 Processor NVIC ISERx register addresses

#define NVIC_ISER0					( (volatile uint32_t*)0xE000E100U )
#define NVIC_ISER1					( (volatile uint32_t*)0XE000E104U )
#define NVIC_ISER2					( (volatile uint32_t*)0XE000E108U )
#define NVIC_ISER3					( (volatile uint32_t*)0XE000E10CU )

//ARM Cortex M4 Processor NVIC ICERx register addresses

#define NVIC_ICER0					( (volatile uint32_t*)0xE000E180U )
#define NVIC_ICER1					( (volatile uint32_t*)0XE000E184U )
#define NVIC_ICER2					( (volatile uint32_t*)0XE000E188U )
#define NVIC_ICER3					( (volatile uint32_t*)0XE000E18CU )


#define NVIC_PR_BASE_ADDR			((volatile uint32_t*)0xE000E400U)

#define NO_PR_BITS_IMPLEMENTED		4

/*base addresses of Flash and SRAM memories*/

#define FLASH_BASEADDR				0x08000000U
#define SRAM_BASEADDR				0x20000000U
#define ROM							0x1FFF0000U


/*AHBx and APBx Bus peripheral base addresses*/

#define PERIPH_BASE					0x40000000U
#define APB1PERIPH_BASE				0x40000000U
#define APB2PERIPH_BASE				0x40010000U
#define AHB1PERIPH_BASE 			0x40020000U
#define AHB2PERIPH_BASE 			0x50000000U

/*APB1 peripherals addresses*/

#define TIM2_BASEADDR				(APB1PERIPH_BASE + 0x0U)
#define TIM3_BASEADDR				(APB1PERIPH_BASE + 0x0400U)
#define TIM4_BASEADDR				(APB1PERIPH_BASE + 0x0800U)
#define TIM5_BASEADDR				(APB1PERIPH_BASE + 0x0C00U)
#define RTC_BKP_R_BASEADDR   		(APB1PERIPH_BASE + 0x2800U)
#define WWDG_BASEADDR				(APB1PERIPH_BASE + 0x2C00U)
#define IWDG_BASEADDR 				(APB1PERIPH_BASE + 0x3000U)
#define I2S2EXT_BASEADDR			(APB1PERIPH_BASE + 0x3400U)
#define SPI2_I2S2_BASEADDR			(APB1PERIPH_BASE + 0x3800U)
#define SPI3_I2S3_BASEADDR 			(APB1PERIPH_BASE + 0x3C00U)
#define I2S3EXT_BASEADDR			(APB1PERIPH_BASE + 0x4000U)
#define USART2_BASEADDR				(APB1PERIPH_BASE + 0x4400U)
#define I2C1_BASEADDR				(APB1PERIPH_BASE + 0x5400U)
#define I2C2_BASEADDR				(APB1PERIPH_BASE + 0x5800U)
#define I2C3_BASEADDR 				(APB1PERIPH_BASE + 0x5C00U)
#define PWR_BASEADDR 				(APB1PERIPH_BASE + 0x7000U)


/*APB2 peripherals addresses*/

#define TIM1_BASEADDR				(APB2PERIPH_BASE + 0x0U)
#define USART1_BASEADDR				(APB2PERIPH_BASE + 0x1000U)
#define USART6_BASEADDR				(APB2PERIPH_BASE + 0x1400U)
#define ADC1_BASEADDR				(APB2PERIPH_BASE + 0x2000U)
#define SDIO_BASEADDR				(APB2PERIPH_BASE + 0x2C00U)
#define SPI1_I2S1_BASEADDR			(APB2PERIPH_BASE + 0x3000U)
#define SPI4_I2S4_BASEADDR			(APB2PERIPH_BASE + 0x3400U)
#define SYSCFG_BASEADDR				(APB2PERIPH_BASE + 0x3800U)
#define EXTI_BASEADDR				(APB2PERIPH_BASE + 0x3C00U)
#define TIM9_BASEADDR				(APB2PERIPH_BASE + 0x4000U)
#define TIM10_BASEADDR				(APB2PERIPH_BASE + 0x4400U)
#define TIM11_BASEADDR				(APB2PERIPH_BASE + 0x4800U)
#define SPI5_I2S5_BASEADDR			(APB2PERIPH_BASE + 0x5000U)


/*AHB1 peripherals addresses*/

#define GPIOA_BASEADDR				(AHB1PERIPH_BASE + 0x0U)
#define GPIOB_BASEADDR				(AHB1PERIPH_BASE + 0x0400U)
#define GPIOC_BASEADDR				(AHB1PERIPH_BASE + 0x0800U)
#define GPIOD_BASEADDR				(AHB1PERIPH_BASE + 0x0C00U)
#define GPIOE_BASEADDR				(AHB1PERIPH_BASE + 0x1000U)
#define GPIOH_BASEADDR				(AHB1PERIPH_BASE + 0x1C00U)
#define CRC_BASEADDR				(AHB1PERIPH_BASE + 0x3000U)
#define RCC_BASEADDR				(AHB1PERIPH_BASE + 0x3800U)
#define FLASH_INTERFACE_R_BASEADDR	(AHB1PERIPH_BASE + 0x3C00U)
#define DMA1_BASEADDR				(AHB1PERIPH_BASE + 0x6000U)
#define DMA2_BASEADDR				(AHB1PERIPH_BASE + 0x6400U)


/*AHB2 peripherals addresses*/

#define USB_OTG_FS					(AHB2PERIPH_BASE + 0x0U)

/*structs*/

typedef struct{

	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2];
}GPIO_RegDef_t;

typedef struct{

	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t RESERVED0[2];
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t RESERVED1[2];
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t RESERVED2[2];
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t RESERVED3[2];
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t RESERVED4[2];
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	volatile uint32_t RESERVED5[2];
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t RESERVED6[2];
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
	volatile uint32_t RESERVED7;
	volatile uint32_t DCKCFGR;
}RCC_RegDef_t;

typedef struct{

	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_RegDef_t;

typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2SCFGR;
	volatile uint32_t I2SPR;
}SPI_RegDef_t;

typedef struct{

	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR[4];
	volatile uint32_t CMPCR;
}SYSCFG_RegDef_t;

typedef struct{
	volatile uint32_t CTRL;
	volatile uint32_t LOAD;
	volatile uint32_t VAL;
	volatile uint32_t CALIB;
}SysTick_RegDef_t;

typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t DR;
    volatile uint32_t SR1;
    volatile uint32_t SR2;
    volatile uint32_t CCR;
    volatile uint32_t TRISE;
} I2C_RegDef_t;

/*peripheral definitions*/

#define GPIOA					((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB					((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC					((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD					((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE					((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOH					((GPIO_RegDef_t*)GPIOH_BASEADDR)

#define RCC						((RCC_RegDef_t*)RCC_BASEADDR)

#define EXTI					((EXTI_RegDef_t*)EXTI_BASEADDR)

#define SYSCFG					((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

#define SPI1					((SPI_RegDef_t*)SPI1_I2S1_BASEADDR)
#define SPI2					((SPI_RegDef_t*)SPI2_I2S2_BASEADDR)
#define SPI3					((SPI_RegDef_t*)SPI3_I2S3_BASEADDR)
#define SPI4					((SPI_RegDef_t*)SPI4_I2S4_BASEADDR)
#define SPI5					((SPI_RegDef_t*)SPI5_I2S5_BASEADDR)

#define I2C1 					((I2C_RegDef_t *)I2C1_BASEADDR)

#define SysTick 				((SysTick_RegDef_t*)SYSTICK_BASE)

//HOW TO USE IT:
// GPIO_RegDef_t *pGPIOA = GPIOA;


/*Clock enable macros for GPIOx peripherals*/

#define GPIOA_PCLK_EN() (RCC->AHB1ENR |= (0b1 << 0))
#define GPIOB_PCLK_EN() (RCC->AHB1ENR |= (0b1 << 1))
#define GPIOC_PCLK_EN() (RCC->AHB1ENR |= (0b1 << 2))
#define GPIOD_PCLK_EN() (RCC->AHB1ENR |= (0b1 << 3))
#define GPIOE_PCLK_EN() (RCC->AHB1ENR |= (0b1 << 4))
#define GPIOH_PCLK_EN() (RCC->AHB1ENR |= (0b1 << 7))


/*Clock enable macros for I2Cx peripherals*/
#define I2C1_PCLK_EN() (RCC->APB1ENR |= (0b1 << 21))
#define I2C2_PCLK_EN() (RCC->APB1ENR |= (0b1 << 22))
#define I2C3_PCLK_EN() (RCC->APB1ENR |= (0b1 << 23))


/*Clock enable macros for SPIx peripherals*/
#define SPI1_PCLK_EN() (RCC->APB2ENR |= (0b1 << 12))
#define SPI2_PCLK_EN() (RCC->APB1ENR |= (0b1 << 14))
#define SPI3_PCLK_EN() (RCC->APB1ENR |= (0b1 << 15))
#define SPI4_PCLK_EN() (RCC->APB2ENR |= (0b1 << 13))
#define SPI5_PCLK_EN() (RCC->APB2ENR |= (0b1 << 20))

/*Clock enable macros for USARTx peripherals*/
#define USART1_PCLK_EN() (RCC->APB2ENR |= (0b1 << 4))
#define USART2_PCLK_EN() (RCC->APB1ENR |= (0b1 << 17))
#define USART6_PCLK_EN() (RCC->APB2ENR |= (0b1 << 5))

/*Clock enable macros for SYSCFG peripherals*/
#define SYSCFG_PCLK_EN() (RCC->APB2ENR |= (0b1 << 14))


/*Clock disable macros for GPIOx peripherals*/
#define GPIOA_PCLK_DIS() (RCC->AHB1ENR &=~ (0b1 << 0))
#define GPIOB_PCLK_DIS() (RCC->AHB1ENR &=~ (0b1 << 1))
#define GPIOC_PCLK_DIS() (RCC->AHB1ENR &=~ (0b1 << 2))
#define GPIOD_PCLK_DIS() (RCC->AHB1ENR &=~ (0b1 << 3))
#define GPIOE_PCLK_DIS() (RCC->AHB1ENR &=~ (0b1 << 4))
#define GPIOH_PCLK_DIS() (RCC->AHB1ENR &=~ (0b1 << 7))

/*Clock disable macros for I2Cx peripherals*/
#define I2C1_PCLK_DIS() (RCC->APB1ENR &=~ (0b1 << 21))
#define I2C2_PCLK_DIS() (RCC->APB1ENR &=~ (0b1 << 22))
#define I2C3_PCLK_DIS() (RCC->APB1ENR &=~ (0b1 << 23))

/*Clock disable macros for SPIx peripherals*/
#define SPI1_PCLK_DIS() (RCC->APB2ENR &=~ (0b1 << 12))
#define SPI2_PCLK_DIS() (RCC->APB1ENR &=~ (0b1 << 14))
#define SPI3_PCLK_DIS() (RCC->APB1ENR &=~ (0b1 << 15))
#define SPI4_PCLK_DIS() (RCC->APB2ENR &=~ (0b1 << 13))
#define SPI5_PCLK_DIS() (RCC->APB2ENR &=~ (0b1 << 20))

/*Clock disable macros for USARTx peripherals*/
#define USART1_PCLK_DIS() (RCC->APB2ENR &=~ (0b1 << 4))
#define USART2_PCLK_DIS() (RCC->APB1ENR &=~ (0b1 << 17))
#define USART6_PCLK_DIS() (RCC->APB2ENR &=~ (0b1 << 5))

/*Clock disable macros for SYSCFG peripherals*/
#define SYSCFG_PCLK_DIS() (RCC->APB2ENR &=~ (0b1 << 14))

/*Clock reset macros for GPIOx peripherals*/
#define GPIOA_REG_RESET()	  do {(RCC->AHB1RSTR |= (0b1 << 0)); (RCC->AHB1RSTR &=~ (0b1 << 0));}while(0)
#define GPIOB_REG_RESET()	  do {(RCC->AHB1RSTR |= (0b1 << 1)); (RCC->AHB1RSTR &=~ (0b1 << 1));}while(0)
#define GPIOC_REG_RESET()	  do {(RCC->AHB1RSTR |= (0b1 << 2)); (RCC->AHB1RSTR &=~ (0b1 << 2));}while(0)
#define GPIOD_REG_RESET()	  do {(RCC->AHB1RSTR |= (0b1 << 3)); (RCC->AHB1RSTR &=~ (0b1 << 3));}while(0)
#define GPIOE_REG_RESET()	  do {(RCC->AHB1RSTR |= (0b1 << 4)); (RCC->AHB1RSTR &=~ (0b1 << 4));}while(0)
#define GPIOH_REG_RESET()	  do {(RCC->AHB1RSTR |= (0b1 << 7)); (RCC->AHB1RSTR &=~ (0b1 << 7));}while(0)
// do while loop is a technique to execute more than one statement in one macro

/*Clock reset macros for SPIx peripherals*/
#define SPI1_REG_RESET()	  do {(RCC->APB2RSTR |= (0b1 << 12)); (RCC->AHB1RSTR &=~ (0b1 << 12));}while(0)
#define SPI2_REG_RESET()	  do {(RCC->APB1RSTR |= (0b1 << 14)); (RCC->AHB1RSTR &=~ (0b1 << 14));}while(0)
#define SPI3_REG_RESET()	  do {(RCC->APB1RSTR |= (0b1 << 15)); (RCC->AHB1RSTR &=~ (0b1 << 15));}while(0)
#define SPI4_REG_RESET()	  do {(RCC->APB2RSTR |= (0b1 << 13)); (RCC->AHB1RSTR &=~ (0b1 << 13));}while(0)
#define SPI5_REG_RESET()	  do {(RCC->APB2RSTR |= (0b1 << 20)); (RCC->AHB1RSTR &=~ (0b1 << 20));}while(0)

#define GPIO_BASEADDR_TO_CODE(x)	((x == GPIOA) ? 0 :\
									(x == GPIOB) ? 1 :\
									(x == GPIOC) ? 2 :\
									(x == GPIOD) ? 3 :\
									(x == GPIOE) ? 4 :\
									(x == GPIOH) ? 7 : 0)

//generic macros
#define ENABLE			1
#define DISABLE			0
#define SET				ENABLE
#define RESET			DISABLE
#define GPIO_PIN_SET 	SET
#define GPIO_PIN_RESET	RESET

//EXTI lines IRQ numbers
#define IRQ_NO_EXTI0		6
#define IRQ_NO_EXTI1		7
#define IRQ_NO_EXTI2		8
#define IRQ_NO_EXTI3		9
#define IRQ_NO_EXTI4		10
#define IRQ_NO_EXTI9_5		23
#define IRQ_NO_EXTI15_10	40


//IRQ PRIORITY
#define NVIC_IRQ_PRIO_0		0
#define NVIC_IRQ_PRIO_1		1
#define NVIC_IRQ_PRIO_2		2
#define NVIC_IRQ_PRIO_3		3
#define NVIC_IRQ_PRIO_4		4
#define NVIC_IRQ_PRIO_5		5
#define NVIC_IRQ_PRIO_6		6
#define NVIC_IRQ_PRIO_7		7
#define NVIC_IRQ_PRIO_8		8
#define NVIC_IRQ_PRIO_9		9
#define NVIC_IRQ_PRIO_10	10
#define NVIC_IRQ_PRIO_11	11
#define NVIC_IRQ_PRIO_12	12
#define NVIC_IRQ_PRIO_13	13
#define NVIC_IRQ_PRIO_14	14
#define NVIC_IRQ_PRIO_15	15


#include "stm32f411xx_gpio_driver.h"
#include "stm32f4xx_spi_driver.h"


#endif /* INC_STM32F4XX_H_ */
