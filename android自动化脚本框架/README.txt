大家好,我是Ray,今天给大家带来一个使用
	adb进行对安卓的模拟点击,等其它操作
	opencv进行分析图片是否匹配以及匹配位置,匹配相似度,截图等操作
	jni进行联系C++写的opencv的操作

首先,想要使用adb,就要把这个文件所在文件夹的adb文件加入系统环境变量path,
具体操作我就不描述了,跟配置jdk环境变量一样,之后在cmd输入adb如果有信息出
来就代表配置成功.

一般来说这步操作不需要,当如果运行时老是出异常或者报缺少dll,请把
opencv_world347.dll放入一下文件夹中:
C:\Windows\System32
C:\Windows\SysWOW64

之后就可以使用了jar包了,我把所有的框架都放在adb_jni_opencv_auto.jar内
因此使用时就需要导入这个jar包就行
======================================
adb_jni_opencv_auto.jar有三个主要的类,分别是
ADB_Model, Dection, FeatureDection
这三个类都放在cn.createqy.autoScripts这个package内
以下是adb_jni_opencv_auto.jar的帮助文档
==================================
ADB_Model类的附类point类//此类只为了方便操作,不使用此类ADB_Model内的方法也能实现
	class point
	{
    	int x=-1;
    	int y=-1;
    	public point(int x,int y)
    	{
      		  this.x=x;
        		this.y=y;
    	}
	}
===========================	
ADB_Model类:	//这个类主要负责对android进行模拟操作
对外公共方法:
	public String connect_WIFI_ROOT(String ipPAth);
		/*adb有两种连接方式,一种是通过usb直接连接,
		 *连接的同时需要打开usb调试,允许管理文件,ps:就是只要你的电脑能够访问到手机文件就行了
		 *如果你是通过wifi连接,那么就需要先调用这个方法,但是这个需要手机root
		 *参数ipPath是你手机的ip地址,返回值是cmd返回的信息,如果返回null就说明失败*/

	public String touch(point p) ;
		//模拟按下手机上位于p的点
		
	 public String touch(int x,int y);
		//模拟按下手机上位于(x,y)坐标的点

	public String input_string(String s);
		//模拟在手机的焦点处输入字符串s

	public String   swipe(point a,point b,int time_m);
		//模拟在时间m内从手机上a点滑到b点,m为毫秒
		//如果a和b相当,就可以按住某一点m毫秒

	 public String   swipe(int x1,int y1,int x2,int y2,int time_m) ;
		//模拟在时间m内从(x1,y1)坐标滑动到(x2,y2)坐标
		//如果(x1,y1)和(x2,y2)
		
	 public String home() ;
		//模拟返回主页面,相当于手机的home键
	
	public String back();
		//模拟返回,相当于手机的back键
	
	 public String turnLeft();
		//模拟向左滑动屏幕#不太好用,有时会失灵,可以用swipe代替
	
	public String turnRight()
		//模拟向右滑动屏幕#不太好用,有时会失灵,可以用swipe代替

	public String Screen_Shot(String path) 
		//对手机进行截屏,截屏图片放在path路径的文件内
===========================================================
Dection类:
/*这是一个依赖talk.dll的原始封装类,如果没学过jni或者没看过源码,那么不推荐新手使用这个类,它会因为你的
 *操作不当导致
 *jni报一些你看不懂的异常,但是使用这个类也是很有好处的,这个类相对于它的封装类FeatureDection来说,
 *它的效率比FeatureDection高好多倍*/

//这个类不允许使用new来构造,你只可以使用它的静态方法getInstance来获得这个类的唯一类对象

	 public static void set_TALK_DLL_PATH(String path);
		/*使用这个类对象一定要先调用这个静态方法,path是talk.dll(这个文件已放在当前文件夹中)
		*的完整路径,路径绝对
		*要写完整,不然会出异常,不允许用src/..代替,这个方法只需调用一次即可
		*/

	 public static Detection getInstance() ;
		/*
		*这个方法是获得Dection唯一类对象的方法,使用之前一定要void set_TALK_DLL_PATH
		因为Dection类只允许拥有一个类对象,不允许拥有其他对象
		*/

	public native void input_Image(String primary_image_path,String match_image_path) ;
		/*放入两张图片,其中primary_image_path是要原始图片路径,
		*match_image_path是要匹配的图片路径,这个图片可以是原始图片的一小部分
		*这相当于是对talk.dll的初始化
		*想要跟换图片也只需改变这个函数的参数的路径即可,需要注意的是,改变后也会对
		*以下的get_x,get_y,get_sample方法进行刷新
		*/
	public native float get_sample();
		/*
			当调用input_image方法后,再调用这个方法获得这两个图片的相似度,一般认为返回的值大于0.93即为相似
		*/
		
    	public native int    get_x();
		/*
			
			当调用input_image方法后,再调用这个方法获得匹配图片在原始图片上最相似的x坐标的位置

		*/
    	public native int    get_y();
		/*
			
			当调用input_image方法后,再调用这个方法获得匹配图片在原始图片上最相似的y坐标的位置

		*/
   	public native void debug_show_Image();
		/*
			当调用input_image方法后,这个方法会将匹配图像用方框与原始图像重合,并且在屏幕上显示灰度图像

		*/
    
    public native void Image_Cap(int x, int y, int width, int height, String read_path, String save_path) ;
		/*
			这个方法不依赖于input_image方法,它是为了实现图像的裁剪
			x为裁剪位置的x坐标
			y为裁剪位置的y坐标
			width为裁剪图片的宽度
			height为裁剪图片的高度
			read_path为读取要被裁剪的图片的路径
			save_path为裁剪后要保存的路径
		*/

//由于这个类有点小复杂,这个类的示例代码将放在example文件中
=============================================
FeatureDection类为Dection的封装类,可以由new创建,而且也简单的多
构造方法:
	FeatureDection(String full_path,String primary_image_path,String match_image_path);
		//第一个参数为talk.dll的完整路径,第二个参数为原始图片,第三个参数为要匹配的图片
类参数
	x:匹配最佳位置的x坐标
	y:匹配最佳位置的y坐标
	sample:匹配相似度
对外方法
	void showImage()
		//显示匹配后的图片,与debug_show_Image()类似
	public  void Image_Cap(int x, int y, int width, int height, String read_path, String save_path)
		//截图.与Image_Cap相似