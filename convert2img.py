import numpy as np
import matplotlib.pyplot as plt
import cv2
from matplotlib import pyplot as plt
 

image = cv2.imread('images/coins.jpg')

# Get rid of BGR to GRAY scale conversion if image scale is already in grayscale
gray = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)

count = 0
label = np.loadtxt("result.txt")

result = np.multiply(gray,label)
print(result)
plt.imshow(result, interpolation='nearest')
plt.show()

cv2.imwrite("segmented.png", cv2.bitwise_not(result))

