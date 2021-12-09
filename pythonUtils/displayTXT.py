import numpy as np 
import pandas as pd
import cv2
import matplotlib.pyplot as plt
import argparse

def parser():
    ap = argparse.ArgumentParser()
    ap.add_argument("-f", "--file", required=True,
        type=str, help="path to text file of mask")
    ap.add_argument("-i", "--image", required=True,
        type=str, help="path to original image file")
    ap.add_argument("-o", "--output_dir", default=".",
        type=str, help="output directory of images")
    args = ap.parse_args()

    return args

def loadTXT2IMG(path):
    txt = pd.read_csv(path, sep=" ")
    img = txt.values
    return img

def showImage(img, backend="cv2"):
    if (backend == "cv2"):
        cv2.imshow("image", img)
        key = cv2.waitKey(30)
        if (key & 0xFF) == ord('q'):
            cv2.destroyAllWindows()

    if (backend == "matplotlib"):
        plt.imshow(img)

if __name__ == "__main__":
    args = parser()
    mask = loadTXT2IMG(args.file)
    img = cv2.imread(args.image)
    res = cv2.bitwise_and(img, img, mask = mask)
    
    cv2.imshow("image", img)
    cv2.imshow("mask", mask)
    cv2.imshow("result", res)

    key = cv2.waitKey(30)
    if (key & 0xFF) == ord('q'):
        cv2.destroyAllWindow()

    cv2.imwrite(args.output_dir + "/mask.png", mask)
    cv2.imwrite(args.output_dir + "/result.png", res)