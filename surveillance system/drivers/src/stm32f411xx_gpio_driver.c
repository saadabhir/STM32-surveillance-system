/*
 * stm32f411xx_gpio.c
 *
 *  Created on: Oct 11, 2026
 *      Author: Windows
 */


#include "stm32f411xx_gpio_driver.h"

// Peripheral Clock Setup
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi){
	//this enables or disables the clock of a specific GPIO port, note the case statements arent functions but macros
	if(EnOrDi == ENABLE){
		switch((uint32_t)pGPIOx){ // casting the pGPIOx to an int so switch case can use it, not needed in if else
		 case(uint32_t)GPIOA: GPIOA_PCLK_EN(); break;
		 case(uint32_t)GPIOB: GPIOB_PCLK_EN(); break;
		 case(uint32_t)GPIOC: GPIOC_PCLK_EN(); break;
		 case(uint32_t)GPIOD: GPIOD_PCLK_EN(); break;
		 case(uint32_t)GPIOE: GPIOE_PCLK_EN(); break;
		 case(uint32_t)GPIOH: GPIOH_PCLK_EN(); break;
		}
	}else if(EnOrDi == DISABLE){
		switch((uint32_t)pGPIOx){
		 case(uint32_t)GPIOA: GPIOA_PCLK_DIS(); break;
		 case(uint32_t)GPIOB: GPIOB_PCLK_DIS(); break;
		 case(uint32_t)GPIOC: GPIOC_PCLK_DIS(); break;
	  	 case(uint32_t)GPIOD: GPIOD_PCLK_DIS(); break;
	 	 case(uint32_t)GPIOE: GPIOE_PCLK_DIS(); break;
		 case(uint32_t)GPIOH: GPIOH_PCLK_DIS(); break;
		}
	}

}

// Init and De-init
void GPIO_Init(GPIO_Handle_t *pGPIOHandle){

	uint32_t temp = 0;
	//enable the peripheral clock
	GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);
	//1 configure the mode of gpio pin
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){
		//non interrupt mode

		/* this creates a bit mask and stores it in temp, the MODER register is then assigned the temp variable
		 *
		 * for example if GPIO_PinMode is GPIO_MODE_ANALOG(which is decimal 3, 11 in binary) it is the exact mode as in the reference manual
		 * and the (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) is the pin number specified by the user multiplied by 2, for example if
		 * pin 5 is entered in PinNumber, then all that expression evaluates to 10, which is exactly on the reference manual the bit position
		 * to set the mode for pin5, 2 here means that the register has the pin mode bits in pairs of 2 in that table, after that a bit mask
		 * with only the bits of the PinNumber set to whatever the user wants on the register, after that the MODER register is called through
		 * the GPIOHandle and first the bits of the PinNumber register are cleared, then the new temp bit mask is assigned
		 */

		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &=~ (0b11 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER |= temp;
		temp = 0;
	} else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode > GPIO_MODE_ANALOG){
		//interrupt mode
		switch(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode){
		case GPIO_MODE_IT_FT:
			// configure the FTSR
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR &=~ (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

			break;
		case GPIO_MODE_IT_RT:
			// configure the RTSR
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR &=~ (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			break;
		case GPIO_MODE_IT_RFT:
			//configure both FTSR and RTSR
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			break;

		}

		// configure the GPIO port selection in SYSCFG_EXTICR
		SYSCFG_PCLK_EN();
		uint8_t EXTIRegNum = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4; // which EXTICR register to use
		uint8_t EXTIRegPinNum = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4; // which pin of the EXTICR register to use
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG->EXTICR[EXTIRegNum] = portcode << (EXTIRegPinNum * 4);

		// enable the exti interrupt delivery using IMR
		EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}

	//2 configure the speed, same principle as the first one
	temp = 0;
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_OUT || pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN){
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->OSPEEDR &=~ (0b11 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->OSPEEDR |= temp;
		temp = 0;
		}


	//3 configure the pupd settings

	temp = 0;

	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &=~ (0b11 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	//4 configure the optype
	temp = 0;
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_OUT || pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN){
	temp = (pGPIOHandle->GPIO_PinConfig.PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER &=~ (0b1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER |= temp;
			}
	//5 configure the alt functionality
	temp = 0;
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN){
		uint32_t altRegSelect,altBitStart; //altRegSelect selects the HIGH or LOW register, the altBitStart selects the pin number
		altRegSelect = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		altBitStart = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
		pGPIOHandle->pGPIOx->AFR[altRegSelect] &=~ (0b1111 << (4 * altBitStart));
		pGPIOHandle->pGPIOx->AFR[altRegSelect] |= (pGPIOHandle->GPIO_PinConfig.PinAltFunMode << (4 * altBitStart));
	}


}

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx){

	switch((uint32_t)pGPIOx){
	case ((uint32_t) GPIOA): GPIOA_REG_RESET(); break;
	case ((uint32_t) GPIOB): GPIOB_REG_RESET(); break;
	case ((uint32_t) GPIOC): GPIOC_REG_RESET(); break;
	case ((uint32_t) GPIOD): GPIOD_REG_RESET(); break;
	case ((uint32_t) GPIOE): GPIOE_REG_RESET(); break;
	case ((uint32_t) GPIOH): GPIOH_REG_RESET(); break;

	}
}

// Data read and write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){
	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
	return value;
}

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx){   // this reads the entire port
	uint16_t value;
	value = (uint16_t)(pGPIOx->IDR);
	return value;
}

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value){
	if (Value == GPIO_PIN_SET){
		pGPIOx->ODR |= (1 << PinNumber);
	}else if(Value == GPIO_PIN_RESET){
		pGPIOx->ODR &=~ (1 << PinNumber);
	}
}

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value){		// this writes to the entire port

	pGPIOx->ODR = Value;
}

void GPIO_ToggleOutput_Pin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){
	pGPIOx->ODR = pGPIOx->ODR ^ (1 << PinNumber);
}

// IRQ configuration and ISR handling
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi){
	if(EnorDi == ENABLE){
		if(IRQNumber <= 31){
			//program ISER0 register
			 *NVIC_ISER0 |= (1 << IRQNumber);
		}else if(IRQNumber > 31 && IRQNumber < 64){
			//program ISER1 register
			 *NVIC_ISER1 |= (1 << IRQNumber % 32);
		}else if(IRQNumber >=64 && IRQNumber < 96){
			//program ISER2 register
			 *NVIC_ISER2 |= (1 << IRQNumber % 64);
		}
	}else {
		if(IRQNumber <= 31){
			//program ICER0 register
			*NVIC_ICER0 |= (1 << IRQNumber);
		}else if(IRQNumber > 31 && IRQNumber < 64){
			//program ICER1 register
			*NVIC_ICER1 |= (1 << IRQNumber % 32);
		}else if(IRQNumber >=64 && IRQNumber < 96){
			//program ICER2 register
			*NVIC_ICER2 |= (1 << IRQNumber % 64);
		}
	}
}

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority){
	// FIRST FIND OUT THE IPR REGISTER
	uint8_t IPRx = IRQNumber / 4; // which IPRx register to use
	uint8_t IPRx_section = IRQNumber % 4; // which of the 8 bitfields of the IPRx register to use
	//since IPRx divided by 4 gives the offset because each IPRx register bitfields is 8, and there are 4 in 32 bits
	uint8_t shift_amount = (8 * IPRx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASE_ADDR + IPRx) |= (IRQPriority << shift_amount);
}

void GPIO_IRQHandling(uint8_t PinNumber){
	if(EXTI->PR & (1 << PinNumber)){
			EXTI->PR |= (1 << PinNumber);
	}
}
