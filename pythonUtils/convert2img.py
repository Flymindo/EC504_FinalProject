import numpy as np
import matplotlib.pyplot as plt
import cv2
import sys
from matplotlib import pyplot as plt
 
def convert(file):
    image = cv2.imread("images/" + file)

    # Get rid of BGR to GRAY scale conversion if image scale is already in grayscale
    gray = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)

    label = np.loadtxt("data/result.txt")

    result = np.multiply(gray,label)

    plt.imshow(result, interpolation='nearest')
    plt.show()

if __name__ == '__main__':
    try:
        file = sys.argv[1]
        convert(file)
        
    except:
        print("Error occured")
