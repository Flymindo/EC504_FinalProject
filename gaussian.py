import numpy as np
import matplotlib.pyplot as plt
import cv2
from sklearn.mixture import GaussianMixture as GMM
 
image = cv2.imread('images/coins.jpg')
gray = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
#print(gray)
print(gray.shape[0])
np.savetxt('image.txt',gray )

img = image.reshape(-1,3)
print(img.shape)

gmm_model = GMM(n_components = 2, covariance_type ='tied').fit(img)


segmented_data = gmm_model.predict_proba(img)

# we can assign edge weights with prob = gmm_model.predict_proba(img), prob[:,0] => foreground to nodes, prob[:,1] => background to nodes

print(segmented_data.shape)
print(segmented_data[:,0])
