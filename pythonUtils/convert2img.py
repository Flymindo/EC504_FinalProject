import numpy as np
import matplotlib.pyplot as plt
import cv2
from matplotlib import pyplot as plt
 
def convert():
#    image = cv2.imread("../images/" + filename)

    # Get rid of BGR to GRAY scale conversion if image scale is already in grayscale
#    gray = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
    image = cv2.loadtxt("../data/image.txt")


    label = np.loadtxt("result.txt")

    result = np.multiply(gray,label)

    plt.imshow(result, interpolation='nearest')
    plt.show()

if __name__ == '__main__':
    try:
        convert(file)
        
    except:
        print("Error occured")
