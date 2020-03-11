/*
void  init_ds18b20(void)                    //对18b20初始化函数
{
	uchar x=0;
	templete=0;
	delay5(120);                      //一次延迟5微秒的函数
	templete=1;
	delay5(16);
	delay5(80);
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
	return(retemp());

		
}
*/
 sbit DQ=P3^7;
void init_ds18b20()
{
	uchar x=0;	
	DQ=0;
	delay5(120);
	DQ=1;
	delay5(16);
	delay5(80);
}

uchar readbyte()
{
	uchar i=0;
	uchar date=0;
	for(i=8;i>0;i--)
	{
		DQ=0;
		delay5(1);
		DQ=1;
		date>>=1;
		if(DQ)date|=0x80;
		delay5(11);

		
	}

	return date;
}
void writebyte(uchar dat)
{
	uchar i=0;
	for(i=8;i>0;i--)
	{
		DQ=0;
		DQ=dat&0x01;
		delay5(12);
		DQ=1;
		dat>>=1;
		delay5(5);
	}
}
uchar retemp()
{
uchar a,b,tt;
uint t;
init_ds18b20();
writebyte(0xcc);
writebyte(0x44)	;
init_ds18b20();
writebyte(0xcc);
writebyte(0xbe);
a=readbyte();
b=readbyte();
t=b;
t<<=8;
t=t|a;
tt=t*0.0625;
return tt;

}