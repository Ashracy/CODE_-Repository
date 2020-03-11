package cn.createqy.Exception;


public class FileMiss extends Exception
{
    public FileMiss()
    {
        super("file not found");
    }
}