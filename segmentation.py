import sys
import subprocess





if __name__ == '__main__':
    try:
        file = sys.argv[1]
        subprocess.run("python3 pythonUtils/grab_cut.py -i images/" + file, shell=True, universal_newlines=True)
        subprocess.run("python3 pythonUtils/gaussian.py " + file, shell=True, universal_newlines=True)
#        subprocess.run("g++  -k", shell=True, universal_newlines=True)
        subprocess.run("./a.out", shell=True, universal_newlines=True)
        subprocess.run("python3 pythonUtils/convert2img.py", shell=True, universal_newlines=True)
    except:
        print("Enter a valid name of file existing in image directory")
        print("Format example: python3 segmentation.py coins.jpg")
    
    
    
    
