
void beep()
{	
	bee=0;
	delay500us();
	bee=1;
	delay500us();
}
			   
void notify()  //œÏ÷Æ∫Û≈∑Õ£1s
{
uint t;

led=0;
	for(t=0;t<1000;t++)
	{beep();}
	bee=0;
	delay1ms(200);
	led=1;
}