import numpy as np
import matplotlib.pyplot as plt
import cv2
 
#image = cv2.imread('images/coins.jpg')
image = cv2.imread('../images/dog.jpg')
 
image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
 
plt.imshow(image)
plt.show()

pixel_vals = image.reshape((-1,1))
 

pixel_vals = np.float32(pixel_vals)

criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 100, 0.85)
 

k = 2
retval, labels, centers = cv2.kmeans(pixel_vals, k, None, criteria, 10, cv2.KMEANS_RANDOM_CENTERS)
 

centers = np.uint8(centers)
segmented_data = centers[labels.flatten()]

 

segmented_image = segmented_data.reshape((image.shape))
print(np.unique(segmented_image))
 
plt.imshow(segmented_image)
plt.show()
