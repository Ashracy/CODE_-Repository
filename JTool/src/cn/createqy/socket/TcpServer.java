package cn.createqy.socket;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;


public class TcpServer {
    private int port =0;
    private ServerSocket server;
    private Socket clientModel;
    private Thread createConnect=new Thread()
    {
        @Override
        public void run() {

            try {
                InputStream is= clientModel.getInputStream();
                OutputStream os= clientModel.getOutputStream();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    };


    public TcpServer(int port) throws IOException {
        this.port=port;
    server=new ServerSocket(port);
    new Thread()
    {
        @Override
        public void run() {
            while (true)
            {
                try {
                    clientModel=server.accept();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    };
    }
}
