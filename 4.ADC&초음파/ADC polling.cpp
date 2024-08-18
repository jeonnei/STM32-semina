/*
 * ADCsemina.c
 *
 *  Created on: Oct 30, 2023
 *      Author: jsg48
 */
#include "main.h"
#include "ADCsemina.h"

void adcadc();


uint16_t ADC_VAL[2];


void adcadc()
{
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	while(1)
	{
		HAL_ADC_Start(&hadc1);                     //ADC 시작
		HAL_ADC_PollForConversion(&hadc1,100);    //1000ms 동안 데이터 받는다.
		ADC_VAL[0]=HAL_ADC_GetValue(&hadc1)/41;
		htim2.Instance-> CCR1 = ADC_VAL[0];
		HAL_ADC_Start(&hadc1);                     //ADC 시작
		HAL_ADC_PollForConversion(&hadc1,100);    //1000ms 동안 데이터 받는다.
		ADC_VAL[1]=HAL_ADC_GetValue(&hadc1)/41;
		htim2.Instance-> CCR2 = ADC_VAL[1];
	}
}

