import cv2
import sys
try:
    if len(sys.argv)==2:
        img = cv2.imread(sys.argv[1],0)
        if img.shape != [28,28]:
            img2 = cv2.resize(img,(28,28))
            img = img2.reshape(28,28,-1)
        else:
            img = img.reshape(28,28,-1)
        #img = 1.0 - img/255.0

        f=open("data.txt","wt")

        for i in range(len(img)-1):
            for j in range(len(img[0])):
                f.write(str(1-img[i][j][0]/255.0) + "\n")

        for k in range(len(img[0])-1):
            f.write(str(1-img[len(img)-1][k][0]/255.0) + "\n")
        f.write(str(1-img[len(img)-1][len(img)-1][0]/255.0))
        f.close()
    else:
        print "Please check the argument list and readme for further help."
except Exception as e:
    print e
    print "There is something wrong with the image file you provided. Please check the argument list and readme for further help."
