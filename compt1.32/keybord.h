
		   #define KEY_API P1
		  
	
				unsigned char getKey()	//无延时
				{
					unsigned char buf_1,buf_2;
					KEY_API=0x0f;
					if(KEY_API!=0x0f)
					{
					buf_1=KEY_API;//行
					 KEY_API=0xf0;
					 buf_2=KEY_API;//列
					 delay_ms(200);
					 KEY_API=0xf0;
					 return (buf_1+buf_2);
			
					}
					else return 0;

				}
				void key_bord()
				{
					uchar key=getKey();
					if(key!=0)
					{
						switch(key)
						{
						case 0xe7: 	isArriving[0]=1;break;//0
						case 0xd7: 	isArriving[1]=1;break;//1
						case 0xb7:	isArriving[2]=1;break;//2
						case 0x77:	isArriving[3]=1;break; //3
						case 0xeb:	isArriving[4]=1;break;//4
						case 0xdb:	isArriving[5]=1;break;//5
						case 0xbb:	isArriving[6]=1;break;//6
						case 0x7b:	isArriving[7]=1;break;//7
						case 0xed:	isArriving[8]=1;break;//8
						case 0xdd:	isArriving[9]=1;break;//9
						case 0xbd:	isArriving[10]=1;break;//10
						case 0x7d:	isArriving[11]=1;break;//11
						case 0xee:  isArriving[12]=1;break;//12
						case 0xde:	isArriving[13]=1;break;//13
						case 0xbe:	isArriving[14]=1;break;//14
						case 0x7e:	isArriving[15]=1;break;//15
						}
					}
				}

 
		   