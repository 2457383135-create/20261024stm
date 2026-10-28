#ifndef __KEY_H
#define __KEY_H

#include "./SYSTEM/sys/sys.h"

/* 引脚定义 */
#define KEY0_GPIO_PORT          GPIOA
#define KEY0_GPIO_PIN           GPIO_PIN_0
#define KEY0_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOF_CLK_ENABLE(); } while (0)
#define KEY1_GPIO_PORT          GPIOE
#define KEY1_GPIO_PIN           GPIO_PIN_4
#define KEY1_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOF_CLK_ENABLE(); } while (0)


/* IO操作 */
#define key0(x)                 do { (x) ?                                                              \
                                    HAL_GPIO_WritePin(KEY0_GPIO_PORT, KEY0_GPIO_PIN, GPIO_PIN_SET):     \
                                    HAL_GPIO_WritePin(KEY0_GPIO_PORT, KEY0_GPIO_PIN, GPIO_PIN_RESET);   \
                                } while (0)
#define key1(x)                 do { (x) ?                                                              \
                                    HAL_GPIO_WritePin(KEY1_GPIO_PORT, KEY1_GPIO_PIN, GPIO_PIN_SET):     \
                                    HAL_GPIO_WritePin(KEY1_GPIO_PORT, KEY1_GPIO_PIN, GPIO_PIN_RESET);   \
                                } while (0)




#define key0_TOGGLE()           do { HAL_GPIO_TogglePin(KEY0_GPIO_PORT, KEY0_GPIO_PIN); } while (0)
#define key1_TOGGLE()           do { HAL_GPIO_TogglePin(KEY1_GPIO_PORT, KEY1_GPIO_PIN); } while (0)



/* 函数声明 */
void key_init(void);    /* 初始化LED */

#endif
