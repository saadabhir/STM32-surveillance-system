
#include <stdint.h>
#include <string.h>
#include "stm32f4xx.h"
volatile uint8_t tiltYorN = 0;
typedef struct {
    I2C_RegDef_t *pI2Cx;
    uint8_t I2C_SCLSpeed;
    uint8_t I2C_ACKControl;
} I2C_Config_t;

typedef struct {
    I2C_Config_t I2C_Config;
} I2C_Handle_t;

#define I2C_SCL_SPEED_SM   0
#define I2C_SCL_SPEED_FM   1
#define I2C_ACK_ENABLE     1
#define I2C_ACK_DISABLE    0

#define LCD_BL  0x08
#define LCD_EN  0x04
#define LCD_RS  0x01

volatile static uint32_t current_time = 0;
volatile static uint32_t last_read_time = 0;

typedef struct {
    uint8_t humidity_int;
    uint8_t humidity_dec;
    uint8_t temp_int;
    uint8_t temp_dec;
    uint8_t checksum;
} DHT11_Data_t;


void DHT11_DelayUs(uint32_t mics){
	SysTick->LOAD = (16 * mics) - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = 0x05;
	while(!(SysTick->CTRL & 0x10000)){}
		SysTick->CTRL = 0x00;

}

void DHT11_DelayMs(uint32_t ms){
	for(uint32_t i = 0;i < ms;i++){
		DHT11_DelayUs(1000);
	}
}

uint8_t DHT11_WaitForPinState(uint8_t HighOrLow, uint32_t timeoutus)
{
    uint32_t start = SysTick->VAL;
    uint32_t timeout_cycles = timeoutus * 16U;

    while (GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_0) != HighOrLow) {
        uint32_t now = SysTick->VAL;
        uint32_t elapsed = (start >= now)
            ? start - now
            : start + (SysTick->LOAD + 1U - now);

        if (elapsed >= timeout_cycles) {
            return 0;
        }
    }

    return 1;
}

void DHT11_SetPinOut(void){
	GPIO_Handle_t DHT11ConfigOUT;
		memset(&DHT11ConfigOUT,0,sizeof(DHT11ConfigOUT));

		DHT11ConfigOUT.pGPIOx = GPIOA;
		DHT11ConfigOUT.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
		DHT11ConfigOUT.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_0;
		DHT11ConfigOUT.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
		DHT11ConfigOUT.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
		DHT11ConfigOUT.GPIO_PinConfig.PinOPType = GPIO_OP_TYPE_OD;

		GPIO_Init(&DHT11ConfigOUT);

}

void DHT11_SetPinIn(void){
	GPIO_Handle_t DHT11ConfigIN;
		memset(&DHT11ConfigIN,0,sizeof(DHT11ConfigIN));

		DHT11ConfigIN.pGPIOx = GPIOA;
		DHT11ConfigIN.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
		DHT11ConfigIN.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_0;
		DHT11ConfigIN.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
		DHT11ConfigIN.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
		GPIO_Init(&DHT11ConfigIN);

}

uint8_t DHT11_ReadData(DHT11_Data_t *data)
{
    uint8_t bytes[5] = {0};

    memset(data, 0, sizeof(*data));

    DHT11_SetPinOut();
    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_0, 0);
    DHT11_DelayMs(20);

    DHT11_SetPinIn();
    DHT11_DelayUs(30);
    SysTick->LOAD = 15999U;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x07;

    if (!DHT11_WaitForPinState(0, 120)) return 0;
    if (!DHT11_WaitForPinState(1, 120)) return 0;
    if (!DHT11_WaitForPinState(0, 120)) return 0;

    for (uint32_t i = 0; i < 40; i++) {
        if (!DHT11_WaitForPinState(1, 120)) return 0;

        uint32_t start = SysTick->VAL;
        if (!DHT11_WaitForPinState(0, 120)) return 0;
        uint32_t now = SysTick->VAL;
        uint32_t high_cycles = (start >= now)
            ? start - now
            : start + (SysTick->LOAD + 1U - now);

        bytes[i / 8] <<= 1;
        if (high_cycles > 720U) {
           bytes[i / 8] |= 1U;
        }
    }

    if ((uint8_t)(bytes[0] + bytes[1] + bytes[2] + bytes[3]) != bytes[4]) {
      return 0;
    }
    data->humidity_int = bytes[0];
    data->humidity_dec = bytes[1];
    data->temp_int = bytes[2];
    data->temp_dec = bytes[3];
    data->checksum = bytes[4];

    return 1;
}

void SysTick_Handler(void) {
    current_time++;
}
volatile DHT11_Data_t latest_reading = {0};

void I2C1_Init(void) {
	//SCL
	GPIO_Handle_t PB6I2C1;
	memset(&PB6I2C1,0,sizeof(PB6I2C1));

	PB6I2C1.pGPIOx = GPIOB;
	PB6I2C1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	PB6I2C1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_6;
	PB6I2C1.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	PB6I2C1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	PB6I2C1.GPIO_PinConfig.PinOPType = GPIO_OP_TYPE_OD;
	PB6I2C1.GPIO_PinConfig.PinAltFunMode = 4;

	GPIO_Init(&PB6I2C1);

	//SDA
	GPIO_Handle_t PB7I2C1;
	memset(&PB7I2C1,0,sizeof(PB7I2C1));

	PB7I2C1.pGPIOx = GPIOB;
	PB7I2C1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	PB7I2C1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_7;
	PB7I2C1.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	PB7I2C1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	PB7I2C1.GPIO_PinConfig.PinOPType = GPIO_OP_TYPE_OD;
	PB7I2C1.GPIO_PinConfig.PinAltFunMode = 4;

	GPIO_Init(&PB7I2C1);

    I2C1->CR2 = (I2C1->CR2 & ~(0x3F)) | 16;
    I2C1->CCR = 80;
    I2C1->TRISE = 17;
    I2C1->CR1 |= (1U << 10) | (1U << 0);
}



void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr) {

    I2C_RegDef_t *pI2Cx = pI2CHandle->I2C_Config.pI2Cx;

    while(pI2Cx->SR2 & (1U << 1));
    pI2Cx->CR1 |= (1U << 8);
    while(!(pI2Cx->SR1 & (1U << 0)));
    pI2Cx->DR = (SlaveAddr << 1);
    while(!(pI2Cx->SR1 & (1U << 1)));
    pI2Cx->SR1;
    pI2Cx->SR2;

    for(uint32_t i = 0; i < Len; i++) {
        while (!(pI2Cx->SR1 & (1U << 7)));

        pI2Cx->DR = pTxBuffer[i];
    }
    while(!(pI2Cx->SR1 & (1U << 2)));
    pI2Cx->CR1 |= (1U << 9);
    for(volatile int d = 0; d < 50000; d++);
}

void LCD_WriteNibble(I2C_Handle_t *pI2CHandle, uint8_t nibble, uint8_t is_data){

    uint8_t value = (nibble & 0xF0) | LCD_BL | (is_data ? LCD_RS : 0);

    I2C_MasterSendData(pI2CHandle, &value, 1, 0x27);
    value |= LCD_EN;
    I2C_MasterSendData(pI2CHandle, &value, 1, 0x27);
    value &= ~LCD_EN;
    I2C_MasterSendData(pI2CHandle, &value, 1, 0x27);
}

void LCD_SendByte(I2C_Handle_t *pI2CHandle, uint8_t byte, uint8_t is_data)
{
    LCD_WriteNibble(pI2CHandle, byte & 0xF0, is_data);
    LCD_WriteNibble(pI2CHandle, (uint8_t)(byte << 4), is_data);
}

void LCD_Init(I2C_Handle_t *pI2CHandle){

    DHT11_DelayMs(50);
    LCD_WriteNibble(pI2CHandle, 0x30, 0);
    DHT11_DelayMs(5);
    LCD_WriteNibble(pI2CHandle, 0x30, 0);
    DHT11_DelayUs(150);
    LCD_WriteNibble(pI2CHandle, 0x30, 0);
    DHT11_DelayUs(150);
    LCD_WriteNibble(pI2CHandle, 0x20, 0);
    LCD_SendByte(pI2CHandle, 0x28, 0);
    LCD_SendByte(pI2CHandle, 0x08, 0);
    LCD_SendByte(pI2CHandle, 0x01, 0);
    DHT11_DelayMs(2);
    LCD_SendByte(pI2CHandle, 0x06, 0);
    LCD_SendByte(pI2CHandle, 0x0C, 0);
}

void LCD_SendChar(I2C_Handle_t *pI2CHandle, char c){
    LCD_SendByte(pI2CHandle, (uint8_t)c, 1);
}


void LCD_DisplayString(I2C_Handle_t *pI2CHandle, const char *str){
    while (*str) {
        LCD_SendChar(pI2CHandle, *str++);
    }
}

char *IntToString(int value, char *buffer){
    char temp[11];
    int i = 0;
    int j = 0;
    unsigned int n;
    if (value < 0) {
        buffer[j++] = '-';
        n = 0u - (unsigned int)value;
    }else {
        n = (unsigned int)value;
    }

    do{
        temp[i++] = '0' + (n % 10);
        n /= 10;
    }while (n > 0);

    while(i > 0) {
        buffer[j++] = temp[--i];
    }

    buffer[j] = '\0';
    return buffer;
}

int main(void){
	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_PeriClockControl(GPIOB, ENABLE);

	RCC->APB1ENR |= (0b1 << 21);
	SysTick->LOAD = 15999;
	SysTick->VAL = 0;
	SysTick->CTRL = 0x07;

	I2C_Handle_t I2C1_Handle;
	GPIO_Handle_t Tilt_Handle;
	/*tilt config*/

	memset(&Tilt_Handle,0,sizeof(Tilt_Handle));

	Tilt_Handle.pGPIOx = GPIOA;
	Tilt_Handle.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RFT;
	Tilt_Handle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_1;
	Tilt_Handle.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	Tilt_Handle.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;

	GPIO_Init(&Tilt_Handle);
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI1, NVIC_IRQ_PRIO_5);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI1, ENABLE);


	I2C1_Handle.I2C_Config.pI2Cx = I2C1;
	I2C1_Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;
	I2C1_Handle.I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE;
	I2C1_Init();
	LCD_Init(&I2C1_Handle);
	DHT11_Data_t sensor = {0};
	char buffIntTemp[4] = "000";
	char buffDecTemp[4] = "000";
	char buffIntHumid[4] = "000";
	char buffDecHumid[4] = "000";
	DHT11_DelayMs(2000);

	while(1){
		if(tiltYorN){
		     tiltYorN = 0;
		      if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_1) == 1){
		        LCD_SendByte(&I2C1_Handle, 0x01, 0);
		        DHT11_DelayMs(2);
		        LCD_DisplayString(&I2C1_Handle, "TILT DETECTED");
		    }
		}
		 DHT11_DelayMs(2000);

		 DHT11_ReadData(&sensor);
		 IntToString(sensor.temp_int, buffIntTemp);
		 IntToString(sensor.temp_dec, buffDecTemp);
		 IntToString(sensor.humidity_int, buffIntHumid);
		 IntToString(sensor.humidity_dec, buffDecHumid);

		 LCD_SendByte(&I2C1_Handle, 0x01, 0);
		 DHT11_DelayMs(2);

		 LCD_SendByte(&I2C1_Handle, 0x80, 0);
		 LCD_DisplayString(&I2C1_Handle, "Temp: ");
		 LCD_DisplayString(&I2C1_Handle, buffIntTemp);
		 LCD_DisplayString(&I2C1_Handle, ".");
		 LCD_DisplayString(&I2C1_Handle, buffDecTemp);
		 LCD_DisplayString(&I2C1_Handle, "C");

		 LCD_SendByte(&I2C1_Handle, 0xC0, 0);
	     LCD_DisplayString(&I2C1_Handle, "Humidity: ");
		 LCD_DisplayString(&I2C1_Handle, buffIntHumid);
		 LCD_DisplayString(&I2C1_Handle, ".");
		 LCD_DisplayString(&I2C1_Handle, buffDecHumid);
		 LCD_DisplayString(&I2C1_Handle, "%");

	}
}

void EXTI1_IRQHandler(void){

    GPIO_IRQHandling(GPIO_PIN_1);
    tiltYorN = 1;
}
