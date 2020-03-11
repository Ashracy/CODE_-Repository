#include <reg51.h>
#include<intrins.h>
#include"complete.h"
#include"DelayClass.h"
#include"TIMEZONE.h"
#include"new12864.h"
 #include"wdj.h"
#include"fmq.h"
#include"KEYBORD.h"
#include"bjdj.h"

uint t5=0;
//int ketscan();
void newthread();
  void judge()
  {
  	uchar i;
	uchar shortdistance=12; 
	char temp=0;
  	for(i=0;i<12;i++)
		{
		if(isArriving[i]==1)
		{
			temp=(i+1)-CurrentFloor;
			if(temp<0)
			{
			temp=-temp;
			}
			
			if(temp<=shortdistance)
			{
			shortdistance=temp;
			floor=i+1;	
			}
		}
  	}
  }

  /*
   while(1)
 {
 showTime();
 i++;
 if(i==12)break;
 }
  */
  
void main()
{
	 
   LcdInit();
   Delay_xms(50);//等待系统稳定
 ds1302_init(); //DS1302初始化
 Delay_xms(10);
   Clr();
   
   
  gundong();
   Clr();
   screen1();

   newthread();
  
  
   
   while(1)
   {  
	  	if(!isArriving[12])
		{
		  Clr();
	  while(!isArriving[12])
	  {	  door=0;
	  TR1=0;
	  screen1();//门开着就判断下一个floor
	  TR1=1;
	  delay1ms(50);

	  judge();
	  }
	  t5=0;
	  door=1;
	  Clr();
	  }
		
	  TR1=0;

	  screen1();
	  TR1=1;

	
	  execute(); //电梯运转
   	 
   }
   
   			   
			   
	 
  

  }
 
 
  void newThread()
  {
  	EA=1;
	ET1=1;
	TMOD=0x10;
	TH0=0xfc;
	TL0=0x17;
	TR1=1;
  }


	
	void anjian() interrupt 3
	{
	uchar i;	 
	TH0=0xfc;
	TL0=0x17;	
	tem=retemp();	 //读取一次温度
	key_bord();		  //键盘检测一次

	if(isArriving[12]==0&&CurrentFloor!=5&&isArriving[0]==0&&isArriving[1]==0&&isArriving[2]==0&&isArriving[3]==0&&isArriving[4]==0&&isArriving[9]==0&&isArriving[8]==0&&isArriving[7]==0&&isArriving[6]==0&&isArriving[5]==0&&isArriving[10]==0&&isArriving[11]==0)
	{

		t5++;
		if(t5==15)
		{	
			isArriving[4]=1;
			isArriving[12]=1;
		}
	 
	
	
	}
if(isArriving[13]==1&&isArriving[12]==0)
{
	Clr();
	while(1)
 {
 	showTime();
 	i++;
 	if(i==12)
	{
	i=0;
	break;
	}
 }
 
 Clr();
 isArriving[13]=0;

	}


	}
	
