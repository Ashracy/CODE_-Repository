import threading
from playsound import playsound
def run(n):
    playsound("E:/source/xxm.wav")
def vedio_demo():
    face_cascade = cv.CascadeClassifier("D:\\TOOLS\opencv\\build\\etc\\haarshare\\haarcascade_frontalface_default.xml ")
    capture=cv.VideoCapture('E:/source/xxm.mp4')
    fps=capture.get(cv.CAP_PROP_FPS)
    total=capture.get(cv.CAP_PROP_FRAME_COUNT);
    i=0;
    rate=int(1000//fps);
    print(rate)
    t=time.time()
    t1= threading.Thread(target=run,args=('t1',))
    t1.start()
    while i<total-2:

        ret,frame=capture.read()
        faces=face_cascade.detectMultiScale(frame,1.1,3)

        for x,y,w,h in faces:
            image=frame[y:y+h,x:x+w]
            image=cv.GaussianBlur(image,(0,0),15)
            frame[ y:y + h,x:x + w]=image

        cv.imshow('video',frame)
        cv.waitKey(1)
        i=i+1
    print(time.time()-t)


