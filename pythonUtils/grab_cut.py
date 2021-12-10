from matplotlib.backend_bases import FigureManagerBase
import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt
import argparse

def parser():
    ap = argparse.ArgumentParser()
    ap.add_argument('-i', '--image', required=True,
        type=str, help='path to image')
    args = ap.parse_args()
    return args

# mouse callback function
def draw_circle(event,x,y,flags,param):
    global ix,iy,drawing,mode
    if event == cv.EVENT_LBUTTONDOWN:
        drawing = True
        ix,iy = x,y
    elif event == cv.EVENT_MOUSEMOVE:
        if drawing == True:
            if (mode == True):
                cv.circle(copied,(x,y),5,(255,255,255),-1)
                cv.circle(mask,(x,y),5,(255,255,255),-1)
            else:
                cv.circle(copied,(x,y),5,(1,1,1),-1)
                cv.circle(mask,(x,y),5,(1,1,1),-1)
    elif event == cv.EVENT_LBUTTONUP:
        drawing = False
        if (mode == True):
            cv.circle(mask,(x,y),5,(255,255,255),-1)
            cv.circle(copied,(x,y),5,(255,255,255),-1)
        else:
            cv.circle(copied,(x,y),5,(1,1,1),-1)
            cv.circle(mask,(x,y),5,(1,1,1),-1)

if __name__ == "__main__":
    args = parser() # get command line arguments

    drawing = False # true if mouse is pressed
    mode = True # if True, draw rectangle. Press 'm' to toggle to curve
    ix,iy = -1,-1

    img = cv.imread(args.image)
    copied = np.copy(img)
    mask = np.zeros((img.shape[0], img.shape[1], 1), np.uint8)

    cv.namedWindow('image')
    cv.setMouseCallback('image',draw_circle)
    print("press 'm' to to switch from drawing foreground to background and 'q' to quit\n")
    while(1):
        cv.imshow('mask', mask)
        cv.imshow('image', copied)
        k = cv.waitKey(1) & 0xFF
        if k == ord('m'):
            mode = not mode
            if mode:
                print("drawing foreground points")
            else:
                print("drawing background points")
        if k == 27 or k == ord('q'):
            break
    cv.destroyAllWindows()

    gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY).flatten()
    mask = mask.flatten()

    bgPoints = gray[mask == 1]
    fgPoints = gray[mask == 255]

    assert len(fgPoints) > 0, "must have at least one foreground point labeled!"
    assert len(bgPoints) > 0, "must have at least one background point labeled!"

    bgMean = bgPoints.mean()
    fgMean = fgPoints.mean()

    print("Background Mean: ", bgMean) 
    print("Foreground Mean: ", fgMean)
    