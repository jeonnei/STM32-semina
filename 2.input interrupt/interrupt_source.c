#include "main.h"

uint8_t flag = 0;
uint8_t flag_m=0;
uint16_t led = 0x08;
uint16_t led_m= 0x00;
uint8_t led_count = 1;//led 점등 갯수
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
		led=0xff;
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
		led=0xff;
	}
	else;
}
void sw2(){								//스위치 2번
	flag=0;
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
{
	if(GPIO_Pin == GPIO_PIN_0){flag_m=flag;flag=1;while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)==1);}
	else if(GPIO_Pin == GPIO_PIN_1){flag_m=flag;flag=2;while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)==1);}
	else if(GPIO_Pin == GPIO_PIN_3){flag_m=flag;flag=3;while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)==1);}
	else if(GPIO_Pin == GPIO_PIN_4){flag_m=flag;flag=4;while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)==1);}
}
void pd2()
{
	while(1)
	{
		HAL_GPIO_WritePin(GPIOA, led, 1);
		HAL_Delay(300);
		HAL_GPIO_WritePin(GPIOA, led, 0);

		if(flag==1)
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
		else{
			normally();
		}
	}
}