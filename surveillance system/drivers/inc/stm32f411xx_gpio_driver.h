
#ifndef INC_STM32F411XX_GPIO_DRIVER_H_
#define INC_STM32F411XX_GPIO_DRIVER_H_

#include "stm32f4xx.h"


typedef struct{

	uint8_t GPIO_PinNumber;			// possible values from @GPIO_PIN_NUM
	uint8_t GPIO_PinMode;			// possible values from @GPIO_PIN_MODES
	uint8_t GPIO_PinSpeed;			// possible values from @GPIO_PIN_SPEED
	uint8_t GPIO_PinPuPdControl;	// possible values from @GPIO_PIN_PUPD
	uint8_t PinOPType;				// possible values from @GPIO_PIN_OUTPUT_TYPE
	uint8_t PinAltFunMode;			// possible values from @GPIO_PIN_ALTERNATE_FUNCTION_MODE
}GPIO_PinConfig_t;


typedef struct{
	GPIO_RegDef_t *pGPIOx;				// choosen port
	GPIO_PinConfig_t GPIO_PinConfig; 	//configuration of the pin
}GPIO_Handle_t;

// GPIO pin possible modes			@GPIO_PIN_MODES
#define GPIO_MODE_IN		0
#define GPIO_MODE_OUT		1
#define GPIO_MODE_ALTFN		2
#define GPIO_MODE_ANALOG 	3
#define GPIO_MODE_IT_FT		4
#define GPIO_MODE_IT_RT		5
#define GPIO_MODE_IT_RFT	6

//GPIO pin possible output types	@GPIO_PIN_OUTPUT_TYPE
#define GPIO_OP_TYPE_PP		0
#define GPIO_OP_TYPE_OD		1

//GPIO pin possible output speeds	@GPIO_PIN_SPEED
#define GPIO_SPEED_LOW		0
#define GPIO_SPEED_MEDIUM	1
#define GPIO_SPEED_FAST		2
#define GPIO_SPEED_HIGH		3

//GPIO pin pull up pull down configuration macros	@GPIO_PIN_PUPD
#define GPIO_NO_PUPD		0
#define GPIO_PIN_PU			1
#define GPIO_PIN_PD			2

//GPIO pin numbers 			@GPIO_PIN_NUM
#define GPIO_PIN_0			0
#define GPIO_PIN_1			1
#define GPIO_PIN_2			2
#define GPIO_PIN_3			3
#define GPIO_PIN_4			4
#define GPIO_PIN_5			5
#define GPIO_PIN_6			6
#define GPIO_PIN_7			7
#define GPIO_PIN_8			8
#define GPIO_PIN_9			9
#define GPIO_PIN_10			10
#define GPIO_PIN_11			11
#define GPIO_PIN_12			12
#define GPIO_PIN_13			13
#define GPIO_PIN_14			14
#define GPIO_PIN_15			15



/***********         APIs supported by this driver             ***********/


// Peripheral Clock Setup
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi);

// Init and De-init
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

// Data read and write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx); // this reads the entire port
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value); // this writes to the entire port
void GPIO_ToggleOutput_Pin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

// IRQ configuration and ISR handling
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t IRQNumber);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);



#endif
