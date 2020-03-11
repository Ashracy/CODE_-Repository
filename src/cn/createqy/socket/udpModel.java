package cn.createqy.socket;

import com.mysql.cj.x.protobuf.MysqlxDatatypes;

import javax.xml.crypto.Data;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.*;

public class udpModel{

    private String address="";
    private int sendPort=0;
    private int receivePort=0;
    private DatagramSocket server=null;



    //发送端初始化
    public udpModel(String address,int sendPort,int receivePort) throws SocketException {
        this.address=address;
        this.sendPort=sendPort;
        this.receivePort=receivePort;

      server=  new DatagramSocket(receivePort);

    }

    public int send(String message) throws IOException {
        byte[] datas=message.getBytes("utf-8");
        DatagramPacket packet=new DatagramPacket(datas,0,datas.length,new InetSocketAddress(address,sendPort));
        server.send(packet);
        return  datas.length;

    }
    public int send(byte[] datas) throws IOException {
        DatagramPacket packet = new DatagramPacket(datas, 0, datas.length, new InetSocketAddress(address, sendPort));
        server.send(packet);
        return datas.length;
    }



    public byte[] blockAccept(int receiveLength) throws IOException {
        byte[] b=new byte[receiveLength];
        DatagramPacket packet=new DatagramPacket(b,0,b.length);
        server.receive(packet);
        return  packet.getData();
    }



}

