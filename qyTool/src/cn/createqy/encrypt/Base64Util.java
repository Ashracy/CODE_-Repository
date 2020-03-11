package cn.createqy.encrypt;



import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.Base64;

public class Base64Util
{
    final   Base64.Encoder encodeer=Base64.getEncoder();
    final   Base64.Decoder decoder= Base64.getDecoder();
    public  String encode(String text)
    {
        return encodeer.encodeToString(text.getBytes(StandardCharsets.UTF_8));
    }
    public  String decode(String encodedText)
    {
        return new String(decoder.decode(encodedText),StandardCharsets.UTF_8);
    }

    public static void main(String[] args) throws IOException {
        File f=new File("D:\\Steam\\steamapps\\common\\Doki Doki Literature Club\\characters\\yuri.txt");
        FileInputStream fis=new FileInputStream(f);
        byte[] buf=new byte[1024*1024];
        while(true) {
           int len= fis.read(buf);
          String str=new Base64Util().decode(new String(buf));
          System.out.println(str);
            if(len<0)break;
        }



    }
}