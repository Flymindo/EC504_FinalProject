import numpy as np
import matplotlib.pyplot as plt
import cv2
import sys
from sklearn.mixture import GaussianMixture as GMM
 
def gaussianMixture(filename):

    image = cv2.imread("images/" + filename)
        
    # Get rid of BGR to GRAY scale conversion if image scale is already in grayscale
    gray = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
    print("================================")
    print("Displaying grayscaled original image. Please close the image to proceed")
    print("================================")
    plt.imshow(gray, interpolation='nearest')
    plt.show()

    np.savetxt('images/image.txt',gray )
    np.savetxt('images/imageSize.txt', gray.shape, fmt='%i')

    height = gray.shape[0]
    width = gray.shape[1]

    gray = gray.reshape(-1,1)
    
    means = np.loadtxt('data/means.txt')

    gmm_model = GMM(n_components = 2, means_init = [[means[0]],[means[1]]], covariance_type ='tied').fit(gray)


    segmented_data = gmm_model.predict_proba(gray)



    # we can assign edge weights with prob = gmm_model.predict_proba(img), prob[:,0] => foreground to nodes, prob[:,1] => background to nodes

    foreground = segmented_data[:,0]
    background = segmented_data[:,1]
    foreground = foreground.reshape(height,width)
    background = background.reshape(height,width)

    np.savetxt('images/foreground.txt',foreground)
    np.savetxt('images/background.txt',background)




if __name__ == '__main__':
    try:
        file = sys.argv[1]
        gaussianMixture(file)
    except:
        print("Failed")

