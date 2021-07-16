import cv2
import glob
import numpy as np

frameSize = (1280, 796)

out = cv2.VideoWriter('dsmc-U.mp4v',cv2.VideoWriter_fourcc(*'MP42'), 15, frameSize)

for filename in glob.glob('D:/ucf/cfal/nsf/career/tsr/cases/cavity/test/cv/img/*.png'):
    img = cv2.imread(filename)
    out.write(img)
    print(filename)

out.release()
