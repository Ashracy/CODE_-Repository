package cn.createqy.socket;




import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

public class TcpClient {
    private Socket client=null;
    private OutputStream os=null;
    private Thread accept=new Thread()
    {
        @Override
        public void run() {
            //super.run();
            try {
                InputStream is=client.getInputStream();
                byte[] flush=new byte[65535];
                while(true)
                {
                    is.read(flush);
                    System.out.println( new String(flush));
                }
            } catch (IOException e) {
                e.printStackTrace();
            }

        }
    };


    public TcpClient(String address,int port) throws IOException {
        client=new Socket(address,port);
        os=client.getOutputStream();
        accept.start();
    }
    public void send(byte[] b) throws IOException {
        os.write(b);
        os.flush();
    }
    public void send(String message) throws IOException {
        os.write(message.getBytes());
        os.flush();
    }
}
