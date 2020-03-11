package cn.createqy.test;


import cn.createqy.Exception.MemoryOverflow;
import cn.createqy.Voice.JacobVoi;

public class t1 {

    public static void main(String[] args) throws MemoryOverflow {
        String str=
                "" +
                        "大家好,我是使用JACOB技术实现的语音功能" +
                        "今天,我将为各位带来如何使用java,C++," +
                        "以及adb,jni,opencv等技术来实现崩坏3的自动" +
                        "化共计脚本,本视频只做学习使用,请勿用做任何商业用途," +
                        "我是雷,我将持续为你讲解次技术是如何一步一步实现的!" +
                        "";
        JacobVoi jacobVoi= new JacobVoi();
      jacobVoi.setSpeed(-2);
        jacobVoi.speak(str);
    }
}