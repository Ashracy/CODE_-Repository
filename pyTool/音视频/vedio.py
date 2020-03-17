import cv2 as cv
import  numpy as np

filepath="E:/source/cxk.mp4"
vediocapture=cv.VideoCapture(filepath)
h=vediocapture.get(cv.CAP_PROP_FRAME_HEIGHT)
w=vediocapture.get(cv.CAP_PROP_FRAME_WIDTH)
fps=vediocapture.get(cv.CAP_PROP_FPS)
videowriter=cv.VideoWriter('test.mp4',
                           cv.VideoWriter_fourcc('m', 'p', '4', 'v'),
                           fps,
                           (int(w),int(h)))
while 1:
    ret,frame=vediocapture.read();
    if ret==False:
        break;
    videowriter.write(frame);

    cv.imshow("asd",frame);
    cv.waitKey(1)
