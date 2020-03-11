package TEST;
import cn.createqy.Exception.MemoryOverflow;
import cn.createqy.Voice.JacobVoi;
import TEST.t2;

public class t1 {

    public String str[]=new String[1000];
    public void voice()
    {

            str[1]= "不多bb,看我操作";
            str[2]="你以为到这里就结束了吗,不,我要把这个装逼神器以及它是怎么编写出来的传授给你";
            str[3]="这个软件是通过读取一个mp4文件并对它的每一帧图片做分析,只后转化为cmd上你们看到的显示效果," +
                    "首先简绍一下它是怎么实现的,它是主要通过opencv和C++还有python实现的,当然,你不懂编程也没关系,因为这个程序主要读取的是一个config.ini文件," +
                    "从而达到播放效果,";
            str[4]="当你获得软件后,只需要修改config.ini里面的参数,就能播放任意视频";
            str[5]="下面,我介绍下如何修改它的参数,打开config.ini文件后,你会看到六个参数,H,W,delay_time,movie_path,1,0,ratio";
            str[6]="H属性表示图片在cmd中显示的高的像素\n" +
                    "W属性表示图片在cmd中显示的宽的像素\n" +
                    "ratio属性调分辨率:经量在1-2范围内调,如果不会多改改就明白怎么回事了\n" +
                    "delay_time属性表示的是帧率,具体修改方法为:\n" +
                    "\t如果你的电脑性能非常强大,可以将它设置为0,那么它就会按照视频原来的帧率运行,如果运行时你发现你的\n" +
                    "\t图像运行与声音对不上,或者说图像显示比声音慢(不可能出现比声音快的情况,而且它与你视频的宽高是有关系的,即上面的H和W属性)\n" +
                    "\t那么你就将其从100-1慢慢调节测试,直到声音与图像显示没有延时,我这里设置的是80,因为可能我的电脑比较垃圾吧,\n" +
                    "\t切记要从100-1慢慢调节,前往不要从1-100调节\n" +
                    "\n" +
                    "movie_path属性是你视频文件的路径:\n" +
                    "\t! ! !路径必须要用/隔开,不是\\,因为windows默认是用\\隔开,一定要改,例如E:/cxk.mp4 而不是E:\\cxk.mp4! ! !\n" +
                    "\t! ! !路径必须要用/隔开! ! !\n" +
                    "\t! ! !路径必须要用/隔开! ! !\n" +
                    "  ==============================重要的事情说三遍=============================\n" +
                    "1和0两个属性是设置视频显示的样式,相当于黑和白,你可以将其换为其他任意相同宽度的字符例如a # $ ) 等等,经量不要改,因为有些字符的宽度过宽会影响显示效果如A和a\n" +
                    "\n" +
                    "\t最后,config.ini文件只可以修改'='后面的内容,其它内容的修改会导致不可预知的错误";
            str[7]="同时,,里面还有一个create.py和moviepy两个python文件,其中create.py会将\n" +
                    "config.ini中movie_path路径的视频文件转化为当前文件夹下的一个temp.wav,这部操作很重要,因为你的视频想要有声音就必须得启动它\n" +
                    "而moviepy是一个依赖包,你不需要关注,你只要让它和create.py在同一路径下就行,\n" +
                    "并且create.py你不需要自己启动,启动vedio_script.exe可以自动启动这个python文件并生成temp.wav\n" +
                    "\n" +
                    "哦,差点忘了,要想启用python文件你的电脑必须配置python环境,\n" +
                    "\t当然即便没有python环境也没关系,vedio_script.exe就不会播放声音,只会显示图片\n" +
                    "python3环境配置教程:https://www.jb51.net/article/165639.htm\n" +
                    "\n" +
                    "配置好后,启动vedio_script.exe,并且要将这个窗口最大化,之后根据提示一直按enter键就行了\n" +
                    "注意:不要在cmd窗口内点击鼠标,否则会导致暂停,而暂停会导致一部分进程还在运行,一部分进程暂停的内容不匹配错误,按下窗口的最大化后置于根据提示按enter键就行,其它经量不要操作\n";
            str[8]="如果你听懂或者看懂我说的是啥玩意,那么我们下面来修改一个视频,当然,为了防止侵权,我通过opencv的人脸检测和过滤操作对视频进行了马赛克处理," +
                    "如果有些许没马赛克到,那请不要怪我,还请喷haarcascade_frontalface_default.xml这个数据包";
            str[9]="那么到这里为止,我们让这个视频通过软件现在来将其转化为命令行的形式播放播放";
            str[10]="首先,我们要来配置config.ini,修改movie_path为这个视频文件的地址,并且修改0和1让它根据的容易被看见";
            str[11]="这个视频就到这里,下一个视频我会介绍我是怎么一步一步实现它的";
    }
    public static void main(String[] args) throws MemoryOverflow {

        JacobVoi voi=new JacobVoi();
        t1 t=new t1();
        t.voice();
        voi.setLouder(90);
        voi.setSpeed(-3);
        voi.speak("点赞三连");


    }
}
