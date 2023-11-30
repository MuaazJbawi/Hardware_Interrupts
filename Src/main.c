/**
  ******************************************************************************
  * @file    Hardware_Intrrupts
  * @author  Muaaz Al-Jbawi
  * @brief   This example describes how to use hardware interrupts to for example open and close
  * doors in a smart home system.
  ******************************************************************************
  **/

#include "main.h"

/**
 * @class SystemConfig
 * @brief Class to configure system settings like clock and interrupts.
 */
class SystemConfig {
public:
    /**
     * @brief Configures the system clock.
     */
    static void SystemClock_Config();

    /**
     * @brief Configures the EXTI0 (External Interrupt 0) handler.
     */
    static void EXTI0_IRQHandler_Config();
};

/**
 * @brief Main function.
 * @return int Returns the exit code.
 */
int main() {
    HAL_Init();

    // Configure system clock and external interrupt.
    SystemConfig::SystemClock_Config();
    BSP_LED_Init(LED1);
    SystemConfig::EXTI0_IRQHandler_Config();

    while (1) {
        // Infinite loop
    }
}

/**
 * @brief Configures the system clock.
 */
void SystemConfig::SystemClock_Config() {
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;
    HAL_StatusTypeDef ret = HAL_OK;

    // Enable Power Control clock and set voltage scaling.
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    // Oscillator configuration.
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;

    #if defined(USE_STM32469I_DISCO_REVA)
    RCC_OscInitStruct.PLL.PLLM = 25;
    #else
    RCC_OscInitStruct.PLL.PLLM = 8;
    #endif
    RCC_OscInitStruct.PLL.PLLN = 360;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    RCC_OscInitStruct.PLL.PLLR = 6;

    // Configure the main PLL.
    ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
    if (ret != HAL_OK) {
        while (1) { /* Error Handler */ }
    }

    // Enable OverDrive mode to reach the maximum frequency.
    ret = HAL_PWREx_EnableOverDrive();
    if (ret != HAL_OK) {
        while (1) { /* Error Handler */ }
    }

    // Clock configuration.
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    // Apply the clock configuration.
    ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
    if (ret != HAL_OK) {
        while (1) { /* Error Handler */ }
    }
}

/**
 * @brief Configures the EXTI0 interrupt handler.
 */
void SystemConfig::EXTI0_IRQHandler_Config() {
    GPIO_InitTypeDef GPIO_InitStructure;

    // Enable clock for GPIOA.
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Configure GPIO pin : PA0.
    GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING; // Interrupt mode on rising edge.
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Pin = GPIO_PIN_0;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Set the priority and enable the EXTI0 interrupt.
    HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

/**
 * @brief Callback function for handling GPIO EXTI interrupt.
 * @param GPIO_Pin Specifies the pin connected to the EXTI line.
 */
extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == GPIO_PIN_0) {
        BSP_LED_Toggle(LED1);
    }
}

#ifdef USE_FULL_ASSERT
/**
 * @brief Reports the name of the source file and the source line number where the assert_param error occurred.
 * @param file Pointer to the source file name.
 * @param line Assert_param error line source number.
 */
void assert_failed(uint8_t *file, uint32_t line) {
    while (1) {
        // Infinite loop
    }
}
#endif
