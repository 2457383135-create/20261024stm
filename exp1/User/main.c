

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/key/key.h"
#include "./STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    sys_stm32_clock_init(336, 8, 2, 7); /* 配置时钟，168MHz */
    delay_init(168);                    /* 初始化延时 */
    usart_init(115200);                 /* 初始化串口 */
    led_init();                         /* 初始化LED */
    
    while (1)
    {
        //顺时针
        LED0(0);
        delay_ms(500); 
        LED1(0);
        delay_ms(500);
        //逆时针
        LED0(1);
        LED1(1);
        delay_ms(1000);
        LED1(0);
        delay_ms(500); 
        LED0(0);
        delay_ms(500);
        
        // button event 
        uint8_t gpim0 = HAL_GPIO_ReadPin(GPIOA, KEY0_GPIO_PIN);
        uint8_t gpim1 = HAL_GPIO_ReadPin(GPIOE, KEY1_GPIO_PIN);
        if((gpim0 == GPIO_PIN_SET) || (gpim1 == GPIO_PIN_SET)){
            delay_ms(2000);
        }

    }
}
