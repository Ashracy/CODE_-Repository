
			#define uchar unsigned char
			#define uint unsigned int
			#define false 0
			#define true 1

		
		
	
			sbit bee =P3^6;	//蜂鸣器
			sbit door=P0^0;
			sbit led=P0^2;	//蜂鸣器灯
	  	    uchar floor=0;	 //前往楼层
			uchar CurrentFloor=5; //当前楼层
	  		uchar isArriving[16]={0};//1表示有人按下，2表示到达相应楼层			 //isArriving[12]为门开位 0开1关
 			uint tem=0;			//当前温度
	  /*
	  电梯启动，显示屏显示名字滚动5s，楼层显示一层，，wck判断上升几层，qy传递一个楼层数字
	  上升成功后，isArriving=true 传递给qy ，显示屏显示到达几层，isArriving=false， wck传递温度给qy，如果温度超过35摄氏度
	  火灾报警蜂鸣器会一直响，灯会一直亮，继电器强行打开。屏幕显示，火灾来了，大家快跑。
	  */
	  /*
	  门开着，有多人按下按键，比如173，对应按键变成true，一开始在5楼，按下关闭电梯门，excute先执行上去最近的，门打开，
	  */



	  
