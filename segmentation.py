import sys
import subprocess





if __name__ == '__main__':
    try:
        file = sys.argv[1]
        print(file)
#        res = subprocess.check_output(f"{cmd} {key}", shell=True, universal_newlines=True)
        subprocess.run("python3 gaussian.py", shell=True, universal_newlines=True)
        subprocess.run("./a.out", shell=True, universal_newlines=True)
        subprocess.run("python3 convert2img.py", shell=True, universal_newlines=True)
    except:
        print("Enter name of file")
    
    
    
    
