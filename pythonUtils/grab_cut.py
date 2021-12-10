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
        print(ix,iy)
    elif event == cv.EVENT_MOUSEMOVE:
        if drawing == True:
            if (mode == True):
                cv.circle(copied,(x,y),5,(255,255,255),-1)
                cv.circle(mask,(x,y),5,(255,255,255),-1)
            else:
                cv.circle(copied,(x,y),5,(0,0,0),-1)
                cv.circle(mask,(x,y),5,(0,0,0),-1)
    elif event == cv.EVENT_LBUTTONUP:
        drawing = False
        if (mode == True):
            cv.circle(mask,(x,y),5,(255,255,255),-1)
            cv.circle(copied,(x,y),5,(255,255,255),-1)
        else:
            cv.circle(copied,(x,y),5,(0,0,0),-1)
            cv.circle(mask,(x,y),5,(0,0,0),-1)

if __name__ == "__main__":
    args = parser() # get command line arguments

    drawing = False # true if mouse is pressed
    mode = True # if True, draw rectangle. Press 'm' to toggle to curve
    ix,iy = -1,-1

    img = cv.imread(args.image)
    copied = np.copy(img)
    mask = np.zeros((img.shape[0], img.shape[1], 1), np.uint8)
    # copied_mask = np.copy(mask)

    bgdModel = np.zeros((1,65), np.float64)
    fgdModel = np.zeros((1,65), np.float64)

    cv.namedWindow('image')
    cv.setMouseCallback('image',draw_circle)
    while(1):
        cv.imshow('mask', mask)
        cv.imshow('image', copied)
        k = cv.waitKey(1) & 0xFF
        if k == ord('m'):
            mode = not mode
        if k == 27 or k == ord('q'):
            break
    cv.destroyAllWindows()


    mask[mask == 0] = 0
    mask[mask == 255] = 1

    mask = mask.reshape(img.shape[:2])
    print(mask.shape)
    np.savetxt("marked.txt", mask)

    
    # mask, bgdModel, fgdModel = cv.grabCut(img,mask,(50,50,450,290),bgdModel,fgdModel,25,cv.GC_INIT_WITH_MASK)

    # mask = np.where((mask==2)|(mask==0),0,1).astype('uint8')
    # img = img*mask[:,:,np.newaxis]
    # plt.imshow(img),plt.colorbar(),plt.show()

