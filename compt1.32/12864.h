
		  #define uchar unsigned char
		  #define uint unsigned int
		  #define screen P0
		  #define left_screen 1
		  #define right_screen 2
		  #define full_screen 0
		  sbit EN=P2^0;
		  sbit RW=P2^1;
		  sbit RS=P2^2;
		  sbit CS2=P2^3;
		  sbit CS1=P3^0;
		  int row=0;
	//	  uchar END=1;

		  void writeCommand(uchar value)
		  {
		  RS=0;
		  RW=0;
		  screen=value;
		  EN=1;
		  EN=0;
		  }

		  void writeData(uchar dat)
		  {
		  	RS=1;
			RW=0;
			screen=dat;
			EN=1;
			EN=0;
		  }
		  void selectScreen(uchar n)
		  {
		  	switch(n)
			{
			case 0:CS1=0;CS2=0;break;
			case 1:CS1=0;CS2=1;break;
			case 2:CS1=1;CS2=0;break;
			default : break;
			}
		  }
		  void clearScreen()
		  {
		  uchar x,y;
		  selectScreen(0);;
		  for(x=0xb8;x<0xc0;x++)	 //页起始地址
		  {
		  writeCommand(x);
		  writeCommand(0x40);	//列起始地址
		  for(y=0;y<64;y++)
		  {
		  	writeData(0x00);	//清零
		  }

		  }

		  }

		 void init()
		 {
		 //	selectSreen(full_screen);
		 	writeCommand(0x3f);//打开显示屏
			
			writeCommand(0xc0);//行起始地址
			/*
			writeCommand(0xb8);	//页起始地址
			writeCommand(0x40);//列起始地址
			*/
		 }
		  
		 void show16x16(uchar s,uchar page,uchar col,uchar *ch)//列起始地址0x40,页起始地址0xb8,12864有八页,但这里为了方便,页请传0-4
		 {
		 	uchar i;
		 	selectScreen(s); 	
		 	writeCommand(0xb8+page*2);//选页
		 	writeCommand(0x40+col);//选列
		 for(i=0;i<16;i++)
		 {
		 	writeData(ch[i]);
		 }				 
		 	writeCommand(0xb8+page*2+1);
		 	writeCommand(0x40+col);//选列

		 for(i=0;i<16;i++)
		 {
		 	writeData(ch[i+16]);
		 }

		 } 

		  show8x16(uchar s,uchar page,uchar col,uchar *ch)
		 {
		  	uchar i;
		 	selectScreen(s); 	
		 	writeCommand(0xb8+page*2);//选页
		 	writeCommand(0x40+col);//选列
		 for(i=0;i<8;i++)
		 {
		 	writeData(ch[i]);
		 }				 
		 	writeCommand(0xb8+page*2+1);
		 	writeCommand(0x40+col);//选列

		 for(i=0;i<8;i++)
		 {
		 	writeData(ch[i+8]);
		 }

		 }
		 show4x8(uchar s,uchar page,uchar col,uchar *ch)	//也可显示8x8
		 {
			uchar i;
		 	selectScreen(s); 	
		 	writeCommand(0xb8+page);//选页
		 	writeCommand(0x40+col);//选列
		 for(i=0;i<8;i++)
		 {
		 	writeData(ch[i]);
		 }				 
		 
		 	
		 }

		void p1()
		{
		
		 	show16x16(left_screen,0,0,zhi);
		 	show16x16(left_screen,0,16,neng);
		 	show16x16(left_screen,0,16*2,dian);
		 	show16x16(left_screen,0,16*3,ti);
		 	show16x16(right_screen,0,0,kong);
		 	show16x16(right_screen,0,16,zhi2);
		 	show16x16(right_screen,0,16*2,xi);
			show16x16(right_screen,0,16*3,tong);
			show16x16(left_screen,1,0,tuan);
			show16x16(left_screen,1,16,dui); 
			show16x16(left_screen,1,16*3,fu1);
		 	show16x16(right_screen,1,0,wang);
		 	show16x16(right_screen,1,16,cheng);
		 	show16x16(right_screen,1,16*2,kui);
		 	show16x16(left_screen,2,0,xu);
		 	show16x16(left_screen,2,16,wei);
		 	show16x16(right_screen,2,0,qian);
		 	show16x16(right_screen,2,16,yu);
		}
		void p2()
		{	 /*
	
			show16x16(left_screen,0,0,dang);
		 	show16x16(left_screen,0,16,qian2);
		 	show16x16(left_screen,0,16*2,lou);
		 	show16x16(left_screen,0,16*3,ceng);
		  	show16x16(right_screen,0,0,fu1);
		  	show8x16(right_screen,0,16,num[CurrentFloor/10]);
		   	show8x16(right_screen,0,24,num[CurrentFloor%10]);
		  

		  //次处两种情况
		 	if(IsArriving==0){ 
			show16x16(left_screen,1,0,qian2);
		 	show16x16(left_screen,1,16,wang2);
		  	show16x16(left_screen,1,16*2,lou);
		 	show16x16(left_screen,1,16*3,ceng);
		  	show8x16(right_screen,1,0,num[floor/10]);
		   	show8x16(right_screen,1,8,num[floor%10]);
		   	}else{

		   	show16x16(left_screen,1,0,dao);
			show8x16(left_screen,1,16,fu2);
			show8x16(left_screen,1,32,fu2);
			 }

		  	show16x16(left_screen,2,0,shi);
		 	show16x16(left_screen,2,16,wen); 
		 	show16x16(left_screen,2,32,fu1); 
		  	show8x16(right_screen,2,0,num[t/10]);
		   	show8x16(right_screen,2,8,num[t%10]);
		    show16x16(right_screen,2,16,fu3); 

			*/
			// show4x8(uchar s,uchar page,uchar col,uchar *ch)
			int i;
			for(i=0;i<12;i++)
			{
			if(isArriving[i])
			{
			show4x8(right_screen,(i/4)*2,(i%4)*16,smal[i]);
				
			}
			else
			{
			show4x8(right_screen,(i/4)*2,(i%4)*16,blank);
		
			}
			}
			show16x16(left_screen,2,0,shi);
		 	show16x16(left_screen,2,16,wen); 
		 	show16x16(left_screen,2,32,fu1); 
		  	show8x16(left_screen,3,0,num[t/10]);
		   	show8x16(left_screen,3,8,num[t%10]);
		    show16x16(left_screen,3,16,fu3); 

		   if(isArriving[12]==1)
		   {
			show16x16(left_screen,0,0,yun);
		 	show16x16(left_screen,0,16,xing);
		 	show16x16(left_screen,0,16*2,zhong);
			show16x16(left_screen,1,0,qian2);
			show16x16(left_screen,1,16,wang2);
			show8x16(left_screen,1,16*2,num[floor/10]);
			show8x16(left_screen,1,16*2+8,num[floor%10]);
		
			
		 }
		 else
		 {
		
			show8x16(left_screen,0,0,num[CurrentFloor/10]);
			show8x16(left_screen,0,8,num[CurrentFloor%10]);
			show16x16(left_screen,0,16,ceng);
			show16x16(left_screen,0,16*2,dao);
			show16x16(left_screen,0,16*3,le);
				
			
		
		 }
		}
		
		void p3()		 //火灾报警
		{
			show16x16(left_screen,0,0,huo);
		 	show16x16(left_screen,0,16,zai);
		  	show8x16(left_screen,0,16*2,fu2);
		 	show8x16(left_screen,0,16*3,fu2);
		 	show16x16(left_screen,1,0,kuai);
		 	show16x16(left_screen,1,16,pao);
		  	show8x16(left_screen,1,16*2,fu2);
		 	show8x16(left_screen,1,16*3,fu2);
		}
			
		void startTimer()//5/64秒中断
		{
			selectScreen(full_screen);
			EA=1;
			ET0=1;
			TMOD=0x01;
			TH0=0xfc;
			TL0=0xf2;
			TR0=1;
		}
		void  move()   interrupt 1
		{
	
		 row++;
		 writeCommand(0xc0+row);
		 if(row==64){row=0;TR0=0;}


		}

	//	 unsigned char end()
	//	 {
	//	 return END;
	//	 }
   //
		 
			 