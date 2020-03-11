package cn.createqy.HttpClient;

import org.apache.http.client.config.RequestConfig;

import java.util.HashMap;
import java.util.LinkedList;

public class GetRequestInfo {
    private String urlinfo="";
    private LinkedList<String> parmer=new LinkedList<String>();
    private RequestConfig requestConfig=null;
    private String path="";
    private HashMap<String,String> headerInfo=new HashMap<String,String>();


    public void setRequestConfig(int ConnectTime,
                                 int ConnectRequestTime,int SocetTime)
    //连接超时时间,请求超时时间,读写超时时间
    {
        requestConfig= RequestConfig.custom().setConnectTimeout(ConnectTime)
                .setConnectionRequestTimeout(ConnectRequestTime).
                        setSocketTimeout(SocetTime).build();

    }

    public void setPath(String path)
    {
        this.path=path;
    }
    public void setParmer(String key,String value)
    {
        parmer.add(key+"="+value);
    }

    public void setHeader(String key,String value)
    {
        headerInfo.put(key,value);
    }

    public String getURL()
    {
        String allParmer="";
        for(int i=0;i<parmer.size();i++)
        {
            allParmer+=parmer.get(i);
            if(i<parmer.size())
            {
                allParmer+="&";
            }
        }
        if(allParmer!="")
            return  path+"/?"+allParmer;
        else
            return path;
    }
    public RequestConfig getRequestConfig()
    {
        return requestConfig;
    }

    public  HashMap<String ,String> getHeaderInfo()
    {
        return headerInfo;
    }
}
