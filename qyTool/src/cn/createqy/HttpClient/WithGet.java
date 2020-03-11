
package cn.createqy.HttpClient;

import cn.createqy.SSLIGNORE.SslUtils;
import org.apache.http.HttpEntity;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClientBuilder;

import java.io.IOException;
import java.util.HashMap;


public class WithGet {
    public CloseableHttpClient httpClient=null;
    public CloseableHttpResponse httpResponse=null;

    HttpGet httpGet=null;
    HttpEntity httpEntity=null;

   public WithGet(GetRequestInfo info)
   {
        httpClient= HttpClientBuilder.create().build();
       httpGet=new HttpGet(info.getURL());

       if(info.getRequestConfig()!=null)
       httpGet.setConfig(info.getRequestConfig());

       HashMap<String ,String> head=info.getHeaderInfo();

       for (HashMap.Entry<String ,String> entry:
               head.entrySet()
            ) {
           httpGet.setHeader(entry.getKey(), entry.getValue());
        //   System.out.println("test:"+entry.getKey()+entry.getValue());

       }


   }
   public boolean execute()  {//执行不到即出错
       try {
           SslUtils.ignoreSsl();
           try {
               httpResponse =
                       httpClient.execute(httpGet);
               httpEntity = httpResponse.getEntity();
           } catch (IOException e) {
               System.out.println("test:    Unfind url");
               return false;
           }



       }catch(Exception e)
       {
           System.out.println("test: execute ssl ");
       }
       return true;

   }

   public HttpEntity getEntity() throws Exception {
       execute();

       if(httpEntity==null)
       {
           throw new NullPointerException("invaild content");
       }
       else
           return httpEntity;

   }

}

