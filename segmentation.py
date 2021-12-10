import sys
import subprocess





if __name__ == '__main__':
    try:
        file = sys.argv[1]
        print(file)
        subprocess.run("python3 gaussian.py", shell=True, universal_newlines=True)
        subprocess.run("./a.out", shell=True, universal_newlines=True)
        subprocess.run("python3 convert2img.py", shell=True, universal_newlines=True)
    except:
        print("Enter a valid name of file existing in image directory")
        print("Format example: python3 segmentation.py coins.jpg")
    
    
    
    
