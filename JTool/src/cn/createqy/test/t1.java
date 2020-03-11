package cn.createqy.test;
import cn.createqy.socket.udpModel;

import java.io.IOException;
import java.net.SocketException;

public class t1 {
    public static void main(String[] args) throws IOException {
        udpModel u=new udpModel("localhost",6666,1111);
        u.send("as");

        String str=new String("asd");

    }
}
