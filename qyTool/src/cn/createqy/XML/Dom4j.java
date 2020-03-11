package cn.createqy.XML;

import cn.createqy.Exception.FileMiss;
import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.Node;
import org.dom4j.io.OutputFormat;
import org.dom4j.io.SAXReader;
import org.dom4j.io.XMLWriter;
import java.io.*;
import java.util.List;

public class Dom4j {
    private String path="";
    private Element root=null;
    private Document document=null;
    private  boolean isBack=false;

    //构造器
    Dom4j(String path) throws FileMiss, DocumentException {
        File f = new File(path);
        if (!f.exists()) {
            System.out.println("file is not exists");
            throw new FileMiss();
        } else
        {
            this.path=path;
            SAXReader saxreader =new SAXReader();
           document=saxreader.read(f);
            root=document.getRootElement();
        }

    }
    //获取根结点
    public Element getRoot()
    {
        return root;
    }
    //回写到本地路径
    public void writeBack() throws IOException {
        XMLWriter xmlwriter =new XMLWriter(new FileOutputStream(path), OutputFormat.createCompactFormat());
        xmlwriter.write(document);
        xmlwriter.close();
        isBack=true;
    }
    //指定路径保存
    public void writeBack(String savepath) throws IOException {
        XMLWriter xmlwriter =new XMLWriter(new FileOutputStream(savepath), OutputFormat.createCompactFormat());
        xmlwriter.write(document);
        xmlwriter.close();
        isBack=true;

    }
    //在e下添加结点
    public void add(Element e,String name)
    {
        e.addElement(name);
    }
    //删除结点
    public void remove(Element e) {
        Element parent =e.getParent();
        parent.remove(e);
    }
    //获取内容
    public String getText(Element e)
{
    return e.getText();
}
    //获取结点属性
    public String getValue(Element e,String name)
    {
        return e.attributeValue(name);
    }
    //在指定结点写添加属性
    public void addAttribute(String key,String value,Element e){
        e.addAttribute(key,value);
    }
    //析构(存在无法被调用的问题)
    @Override
    protected void finalize() throws Throwable {
        if(isBack=false) {
            this.writeBack();
            System.out.println("sad");
        }
        System.out.println("a");
    }
    //XPath
    /*
    第一种形式
/AAA/BBB/DDD;表示一层一层的,AAA下面的BBB.BBB下面的DDD
            第二种形式
//BBB:表示和这个名称相同,表示只要名称是BBB都能得到;
//BBB/AAA:表示获取所有名称为BBB下面的AAA
    第三种形式:
            /:所有元素
    第四种形式:
            ** //BBB[1]//表示获得所有名为BBB下面的第一个元素ps:一般用于selectSingleNode方法里面
    第五种形式:
//BBB[@id]//表示只要BBB元素上加了id属性的都会获取到
//BBB[@id=‘id1’]//表示只要元素名称是BBB,并且有id属性,并且id的属性值为b1;
  */
       public  List<Node> findByXpath(String format)
    {
        List<Node> ln=document.selectNodes(format);
       return ln;
    }


    public static void main(String[] args) throws FileMiss, DocumentException, IOException {


    }
}
