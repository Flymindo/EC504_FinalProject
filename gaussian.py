import numpy as np
import matplotlib.pyplot as plt
import cv2
from sklearn.mixture import GaussianMixture as GMM
 

image = cv2.imread('images/coins.jpg')
#print(image.shape)

# Get rid of BGR to GRAY scale conversion if image scale is already in grayscale
gray = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)

np.savetxt('image.txt',gray )
np.savetxt('imageSize.txt', gray.shape, fmt='%i')



gray = gray.reshape(-1,1)

gmm_model = GMM(n_components = 2, covariance_type ='tied').fit(gray)


segmented_data = gmm_model.predict_proba(gray)

# we can assign edge weights with prob = gmm_model.predict_proba(img), prob[:,0] => foreground to nodes, prob[:,1] => background to nodes

print(segmented_data.shape)

foreground = segmented_data[:,0]
background = segmented_data[:,1]
foreground = foreground.reshape(240,180)
background = background.reshape(240,180)

np.savetxt('foreground.txt',foreground)
np.savetxt('background.txt',background)

