package cn.createqy;

import java.io.IOException;


    public class t1 {
        public native  int myadd(int a,int b);
      //  public native int add(int a,int b);
       // public native int speak(int a,String b);
        public static void main(String[] args) throws IOException {
            System.load("E:/VS C++/hello3/x64/Release/hello3.dll");
            cn.createqy.t1 t=new cn.createqy.t1();
            t.myadd(1,2);

        }
    }

