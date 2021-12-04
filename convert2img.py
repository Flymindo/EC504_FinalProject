import numpy as np
import matplotlib.pyplot as plt
import cv2
from matplotlib import pyplot as plt
 

image = cv2.imread('images/coins.jpg')
#print(image.shape)

# Get rid of BGR to GRAY scale conversion if image scale is already in grayscale
gray = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
#gray = gray.reshape(-1,1)

count = 0
label = np.loadtxt("result.txt")

#print(label)
#print(gray)

result = np.multiply(gray,label)
print(result)
plt.imshow(result, interpolation='nearest')
plt.show()


#gray = gray.reshape(-1,1)
#
#gmm_model = GMM(n_components = 2, covariance_type ='tied').fit(gray)
#
#
##segmented_data = gmm_model.predict_proba(gray)
#segmented_data = gmm_model.predict(gray)
#segmented_data = segmented_data.reshape(240,180)
#print(segmented_data.shape)
#
#
## we can assign edge weights with prob = gmm_model.predict_proba(img), prob[:,0] => foreground to nodes, prob[:,1] => background to nodes
#
#
##foreground = segmented_data[:,0]
##background = segmented_data[:,1]
##foreground = foreground.reshape(240,180)
##background = background.reshape(240,180)
##
##np.savetxt('foreground.txt',foreground)
##np.savetxt('background.txt',background)
#np.savetxt('segmented.txt',segmented_data)

