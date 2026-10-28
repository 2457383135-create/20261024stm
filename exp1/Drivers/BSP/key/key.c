#include "./BSP/key/key.h"

/**
 * @brief   初始化LED
 * @param   无
 * @retval  无
 */
void key_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    /* 使能GPIO端口时钟 */
    KEY0_GPIO_CLK_ENABLE();
    KEY1_GPIO_CLK_ENABLE();

    /* 配置KEY0控制引脚 */
    gpio_init_struct.Pin = KEY0_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(KEY0_GPIO_PORT, &gpio_init_struct);
    
    /* 配置KEY1控制引脚 */
    gpio_init_struct.Pin = KEY1_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(KEY1_GPIO_PORT, &gpio_init_struct);


    /* 关闭LED0、LED1 */
    key0(1);
    key1(1);


}