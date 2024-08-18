/*
 * timercount.c
 *
 *  Created on: Sep 26, 2023
 *      Author: jsg48
 */
#include "main.h"
#include "timercount.h"

uint8_t flag = 0;
uint8_t flag_m=0;
uint16_t led = 0x08;
uint16_t led_m= 0x00;
uint8_t led_count = 1;//led 점등 갯수
uint8_t light = 10;//led 밝기
uint16_t current_tick_0=0;	//디바운싱 변수
uint16_t current_tick_1=0;
uint16_t current_tick_3=0;
uint16_t current_tick_4=0;
uint16_t old_tick_0=0;
uint16_t old_tick_1=0;
uint16_t old_tick_3=0;
uint16_t old_tick_4=0;



void ledwrite(uint16_t LED,uint8_t i);
void normally();
void sw1();
void sw2();
void sw3();
void sw4();
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void maincount()
{
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
	while(1)
	{
		ledwrite(led,light);
		HAL_Delay(300);
		ledwrite(led,0);
		if(flag==0)
		{
			normally();
		}
		else if(flag==1)
		{
			sw1();
		}
		else if(flag==2)
		{
			sw2();
		}
		else if(flag==3)
		{
			sw3();
		}
		else if(flag==4)
		{
			sw4();
		}
		else;
	}
}
void normally()//평상시

{
	led>>=1;
	if(led_count==1){
		if(led==0x00)led=0x08;
		else;
	}
	else if(led_count==2)
	{
		if(led==0x01)led=0x09;
		else if(led==0x04)led=0x0c;
		else;
	}
	else if(led_count==3)
	{
		if(led==0x03)led=0x0b;
		else if(led==0x05)led=0x0d;
		else if(led==0x06)led=0x0e;
		else;
	}
	else if(led_count==4)
	{
		led=0x0f;
	}
	else;
}
void sw1(){								//스위치 1번
		led<<=1;
		if(led_count==1)
		{
			if(led==0x10)led=0x01;
			else;
		}
		else if(led_count==2)
		{
			if(led==0x18)led=0x09;
			else if(led==0x12)led=0x03;
			else;
		}
		else if(led_count==3)
		{
			if(led==0x1c)led=0x0d;
			else if(led==0x1a)led=0x0b;
			else if(led==0x16)led=0x07;
			else;
		}
		else if(led_count==4)
		{
			led=0x0f;
		}
		else;
}
void sw2(){								//스위치 2번 밝기조절
	flag = flag_m;
}
void sw3(){								//스위치3번
	led_count++;// 카운트+1;
	if(led_count>=4)led_count=4; //카운트값이 4이상 일 때, 4고정
	led_m = led;//현재의 led 값 저장
	led = (led_m<<1)|led;//현재의 값에서 왼쪽에서+1된값 마스크
	if((led==0x18)&&led_count==2)led = 0x09;
	else if((led==0x1c)&&led_count==3)led = 0x0d;
	else if((led==0x19)&&led_count==3)led = 0x0b;
	flag = flag_m;
}
void sw4(){
	led_count = 1;
	led = 0x08;
	flag = 0;
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{	if(GPIO_Pin == GPIO_PIN_0){
		current_tick_0 = HAL_GetTick();
	}
	if(GPIO_Pin == GPIO_PIN_1)
	{
		current_tick_1 = HAL_GetTick();
	}
	if(GPIO_Pin == GPIO_PIN_3)
	{
		current_tick_3 = HAL_GetTick();
	}
	if(GPIO_Pin == GPIO_PIN_4)
	{
		current_tick_4 = HAL_GetTick();
	}
	if((GPIO_Pin == GPIO_PIN_0)&&(current_tick_0 - old_tick_0>30)){
		while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)==1);
		flag_m=flag;
		if(flag_m==0)flag=1;
		else if(flag_m==1)flag=0;
		else;
		old_tick_0 = current_tick_0;
	}
	if((GPIO_Pin == GPIO_PIN_1)&&(current_tick_1 - old_tick_1>30))
	{
		while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)==1);
		flag_m=flag;flag=2;if(light>=100)light=10;
		light= light+10;
		old_tick_1 = current_tick_1;
	}
	if((GPIO_Pin == GPIO_PIN_3)&&(current_tick_3 - old_tick_3>30))
	{
		while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)==1);
		flag_m=flag;flag=3;
		old_tick_3 = current_tick_3;
	}
	if((GPIO_Pin == GPIO_PIN_4)&&(current_tick_4 - old_tick_4>30))
	{
		while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)==1);
		flag_m=flag;flag=4;
		old_tick_4 = current_tick_4;
	}
	/*if(GPIO_Pin == GPIO_PIN_0){		>>디바운싱 안한거
	  while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)==1);
		flag_m=flag;
		if(flag_m==0)flag=1;
		else if(flag_m==1)flag=0;
		else;
	}
	if(GPIO_Pin == GPIO_PIN_1)
	{
		while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)==1);
		flag_m=flag;flag=2;if(light>=100)light=10;
		light= light+10;
	}
	if(GPIO_Pin == GPIO_PIN_3)
	{
		while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)==1)
		flag_m=flag;flag=3;
	}
	if(GPIO_Pin == GPIO_PIN_4)
	{	while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)==1);
		flag_m=flag;flag=4;
	}*/
}
void ledwrite(uint16_t LED,uint8_t i)
{
	uint16_t a,b,c,d;
	a=led/8;
	b=(led%8)/4;
	c=((led%8)%4)/2;
	d=((led%8)%4)%2;
	if(a==1)htim2.Instance-> CCR4 = i;else htim2.Instance-> CCR4 = 0;
	if(b==1)htim2.Instance-> CCR3 = i;else htim2.Instance-> CCR3 = 0;
	if(c==1)htim2.Instance-> CCR2 = i;else htim2.Instance-> CCR2 = 0;
	if(d==1)htim2.Instance-> CCR1 = i;else htim2.Instance-> CCR1 = 0;
}
