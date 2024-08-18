/* USER CODE BEGIN PM */
uint32_t Result[2];
/* USER CODE END PM */

int main(void)
{
  HAL_ADC_Start_DMA(&hadc1,(uint32_t*)Result,2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  while(1)
  {
	htim1.Instance-> CCR2 = Result[0]/41;
	htim1.Instance-> CCR3 = Result[1]/41;
  }
}