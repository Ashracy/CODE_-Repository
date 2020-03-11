package cn.createqy.DataBase;

import com.mysql.cj.x.protobuf.MysqlxDatatypes;
import com.mysql.cj.xdevapi.Result;

import java.sql.*;
import java.util.ArrayList;

public class qyMySql {
    String url="";
    String username="";
    String password="";
    String driverClassName="com.mysql.cj.jdbc.Driver";
    Connection con;
    Statement stmt;

    //Address:地址+端口+库;例如:localhost:3306/mm
    public qyMySql(String Address ,String username,String password) throws ClassNotFoundException, SQLException {
        this.url="jdbc:mysql://"+Address+"?serverTimezone=UTC";
        this.username=username;
        this.password=password;
        Class.forName(driverClassName);
        con= DriverManager.getConnection(url,username,password);
        stmt=con.createStatement();

    }
    //此
    public qyMySql(String Address ,String username,String password,String parameter) throws ClassNotFoundException, SQLException {
        this.url="jdbc:mysql://"+Address+"?serverTimezone=UTC?"+parameter;
        this.username=username;
        this.password=password;
        Class.forName(driverClassName);
        con= DriverManager.getConnection(url,username,password);
        stmt=con.createStatement();

    }
    public boolean isConnect() throws SQLException {
        if(con.isClosed())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    public  int excute(String order) throws SQLException {
        //返回影响的行数
        return stmt.executeUpdate(order);
    }
    public ArrayList<String> query(String order,String id) throws SQLException {
        //查询第id名列下的数据
        ArrayList<String > lis=new ArrayList<String>();
        ResultSet result=  stmt.executeQuery(order);
        StringBuffer buffer=new StringBuffer();
        while(result.next())
        {
            lis.add(result.getString(id));


        }
        return  lis;


    }
    public ArrayList<String> query(String order,int id) throws SQLException {
        //查询第id行的数据
        ArrayList<String > lis=new ArrayList<String>();
        ResultSet result=  stmt.executeQuery(order);
        StringBuffer buffer=new StringBuffer();
        while(result.next())
        {
          lis.add(result.getString(id));


        }
        return  lis;


    }
