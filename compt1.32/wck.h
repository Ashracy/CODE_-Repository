
#define k CurrentFloor
	uchar a[]={0x02,0x06,0x04,0x0c,0x08,0x09,0x01,0x03};
void delay5(uchar  n)
{
	do
	{
		_nop_();
		_nop_();
		_nop_();
		n--;
	}
	while(n);
}
void  delay()
{	uchar i,j;
	for(i=0;i<2;i++)
	{
		for(j=0;j<120;j++);
	}
}

void excute()//电梯运转函数
{

	uchar n,i,j=floor;
		if(j>k)         //判断传递的楼层是否大于初始楼层k，电梯向上
		{  
			for(;j>k;j--)                      //判断需要顺时针旋转几周，就是电梯上升几层
			{
			  for(i=0;i<8;i++)              //共8次  顺时针旋转一周
			  {
				for(n=0;n<8;n++)         //步进电机旋转45度
				{
					sctrl=a[n];
					delay();
				}
				n=0;
			  }
			}
			k=floor;
			isArriving[k-1]=false;                 //停止在这个楼层
		    isArriving[13]=true;	      //已经上升完毕   改		
		}
		else      //电梯向下
		{
			for(;k>j;k--)             
			{
				for(i=0;i<8;i++)
				{
					for(n=7;n>=0;n--)      //逆时针旋转一周
					{
						sctrl=a[n];
						delay();
					}
					n=7;
				}
			}
			k=floor;
			isArriving[k-1]=true;             //下降完毕
			isArriving[13]=true;
		}
	}
void  init_ds18b20(void)                    //对18b20初始化函数
{
	uchar x=0;
	templete=0;
	delay5(120);                      //一次延迟5微秒的函数
	templete=1;
	delay5(16);
	delay();
}
uchar readbyte(void)
{
	uchar i=0;
	uchar date=0;
	for(i=8;i<0;i--)
	{
		templete=0;        
		delay5(1);
		templete=1;        //15微秒内释放总线
		if(templete)
		{
			date|=0x80;
		}
		delay5(11);
	}
	return(date);
}
void writebyte(uchar dat)
{
	uchar i=0;
	for(i=8;i>0;i--)
	{
		templete=0;
		templete=dat&0x01;
		delay5(12);    
		templete=1;
		dat>>=1;
		delay5(5);
	}
}
uchar retemp  (void)//温度确定函数
{
	uchar a,b,tt;
	uint t;
	init_ds18b20();
	writebyte(0xcc);
	writebyte(0x44);
	init_ds18b20();
	writebyte(0xcc);
	writebyte(0xb3);
	a=readbyte();       //低八位
	b=readbyte();       //高八位
	t=b;
	t<<=8;
	t=t|a;
	tt=t*0.0625;
	return(tt);
}
uchar wendu(void)
{
	init_ds18b20();
	readbyte();
//	writebyte(); 
	return(retemp());

		
}



void fengmingqi()	 //蜂鸣器想1s，音符为0.1ms
{	
    uchar i,j;
	led=0;
	for(i=0;i<200;i++)
	{
		for(j=0;j<200;j++)
		{
			bee=~bee;
		 	delay5(5);
		}
	}
	led=1;
}



		//	void jidianqi(bit a)//1开门，0关门
		//	{
						  	
		//	}





