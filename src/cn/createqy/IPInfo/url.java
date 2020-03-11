package cn.createqy.IPInfo;


import java.io.IOException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;

public class url {
    private URL u=null;
    public  url(String address) throws MalformedURLException {
        u=new URL(address);
    }
    public String getProtocol()
    {
        return u.getProtocol();
    }
    public  String getHostName()
    {
        return u.getHost();
    }
    public  String getPath()
    {
        return u.getPath();
    }
    public String getName()
    {
        return u.getRef();
    }
    public InputStream getIS() throws IOException {
        return u.openStream();
    }

}
