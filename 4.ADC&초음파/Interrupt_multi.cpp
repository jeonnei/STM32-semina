/* USER CODE BEGIN PM */
uint16_t adcVal[2];
uint8_t adcIndex;
uint16_t result1, result2;
/* USER CODE END PM */

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  adcVal[adcIndex] = HAL_ADC_GetValue(&hadc1);

  if(adcIndex == 1)
  {
    result1 = adcVal[0] / 41;
    result2 = adcVal[1] / 41;
  }

  adcIndex++;
  if(adcIndex > 1) adcIndex = 0;

  HAL_ADC_Start_IT(&hadc1);

}
int main(void)
{
	/* USER CODE BEGIN 2 */
  HAL_ADC_Start_IT(&hadc1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  /* USER CODE END 2 */
   while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		htim1.Instance-> CCR2 = result1;
		htim1.Instance-> CCR3 = result2;

  }
   /* USER CODE END 3 */
}