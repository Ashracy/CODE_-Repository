
package cn.createqy.HttpClient;

import org.apache.http.HttpEntity;

import java.io.IOException;
import java.io.InputStream;

public class GetResponseInfo {
    public HttpEntity httpEntity=null;
    public WithGet withget=null;
    public GetResponseInfo(WithGet withget) throws Exception {
        this.withget=withget;
        httpEntity= withget.getEntity();
    }
    public  GetResponseInfo(GetRequestInfo info) throws Exception {
        withget=new WithGet(info);
        httpEntity= withget.getEntity();
    }

    public long getLength()
    {
        return httpEntity.getContentLength();
    }

    public InputStream getContent()
    {
        try {
            return  httpEntity.getContent();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    public String getStatus()
    {
        return withget.httpResponse.getStatusLine().toString();
    }
    public void close() throws IOException {
        withget.httpResponse.close();
        withget.httpResponse.close();
    }
}