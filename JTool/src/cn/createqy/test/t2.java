package cn.createqy.test;
import cn.createqy.socket.udpModel;

import java.io.IOException;

public class t2 {
    public static void main(String[] args) throws IOException {
        udpModel u=new udpModel("localhost",4567,6666);
        byte[] b=u.blockAccept(123);
        System.out.println(new String(b));
    }
}
