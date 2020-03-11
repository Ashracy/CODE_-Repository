
void delay1ms(unsigned int i)
{
	unsigned char j;
	while(i--)
	{	
		for(j=0;j<255;j++)
		{;}
	}
}

void delay500us()
{
uchar j;

for(j=0;j<57;j++)
{;}
}
 delay_ms(int n)	//1000²î²»¶àÒ»Ãë
		   {  int i ,j;
		   for(;i<n;i++)
		   {
		   for(j=0;j<255;j++);
		   }
		   }


		   void delay128(int ms)                //å»¶æ—¶ms
{
        while(ms--)
        {
                int i;
                for(i=25;i>0;i-- ); 
        }
}
 void delay5(uint n)
		 {
		 	do
			{
				_nop_();
				_nop_();
				_nop_();
				n--;
			}while(n);
		 }