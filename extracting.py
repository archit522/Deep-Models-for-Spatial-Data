import cv2

def facechop(image, count):
    facedata = "/Users/architaggarwal/anaconda2/lib/python2.7/site-packages/cv2/data/haarcascade_frontalface_default.xml"
    cascade = cv2.CascadeClassifier(facedata)

    img = cv2.imread(image)

    minisize = (img.shape[1],img.shape[0])
    miniframe = cv2.resize(img, minisize)

    faces = cascade.detectMultiScale(miniframe)

    for f in faces:
        r = start;
        x, y, w, h = [ v for v in f ]
        cv2.rectangle(img, (x,y), (x+w,y+h), (255,255,255))

        sub_face = img[y:y+h, x:x+w]
        face_file_name = "/Users/architaggarwal/Downloads/faces/face_" + str(count) + ".jpg"
        count = count + 1
        cv2.imwrite(face_file_name, sub_face)

    cv2.imshow(image, img)

    return count

if __name__ =='__main__':
    start = input()
    end = input()
    count = int(start)
    for i in range(int(start), int(end)):
        count = facechop("/Users/architaggarwal/Downloads/frame_" + str(i) + ".jpg", count)

    while(True):
        key = cv2.waitKey(20)
        if key in [27, ord('Q'), ord('q')]:
            break
