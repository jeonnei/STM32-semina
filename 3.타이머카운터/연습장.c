void ledwrite(uint16_t led,uint8_t i,) i = 100 or 0입력으로
{
	
	htim2.Instance-> CCR4 = i;
	htim2.Instance-> CCR3 = i;
	htim2.Instance-> CCR2 = i;
	htim2.Instance-> CCR1 = i;	
}


만약 led = 0x0f다.