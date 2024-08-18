#include "main.h"
#include "ADCsemina.h"

/// adc 다중채널 예시
void adcadc();


uint16_t ADC_VAL[2];


void adcadc()
{
	while(1)
	{
		HAL_ADC_Start(&hadc1);                     //ADC 시작
		HAL_ADC_PollForConversion(&hadc1,100);    //1000ms 동안 데이터 받는다.
		ADC_VAL[0]=HAL_ADC_GetValue(&hadc1);
		HAL_ADC_Start(&hadc1);                     //ADC 시작
		HAL_ADC_PollForConversion(&hadc1,100);    //1000ms 동안 데이터 받는다.
		ADC_VAL[1]=HAL_ADC_GetValue(&hadc1);
	}
}