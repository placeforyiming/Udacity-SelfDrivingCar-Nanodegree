#OpenCV

* cv2.cvtColor()
Change the color form. If we have a RGB image **_img_**, we can use cv2.cvtColor(img,cv2.COLOR_BGR2GRAY) to change it to Grey. cv2.COLOR_BGR2HSV will change RGB to HSV. （HSV is an another human friendly color formation.https://www.thoughtco.com/what-is-hsv-in-design-1078068）

* cv2.inRange() 
For color selection, we can combine cv2.inRange() with cv2.COLOR_BGR2HSV to pick the area with certain color.
If input is a 3D image, then this function will return a 1D image with two value 255 and 0. 

* cv2.fillPoly()
Select an area according to given points and fill with colors. The code below draw a triangle and fill it with green.
> triangles=np.array([[(200,240),(145,333),(255,333)]])
cv2.fillPoly(image,triangles,(0,255,0))

* cv2.line()
Draw a line with given points, color and width.
> cv2.line(img,(0,0),(200,300),(255,255,255),50)  (original_img, start point, end point, color, width)

* cv2.addWeighted()
Image blending, like:
> dst = cv2.addWeighted(img1,0.7,img2,0.3,0)

* cv2.imwrite()
Output the image, with cv2.imwrite('filename', img)

* cv2.bitwise_and()
* cv2.bitwise_or()
* cv2.bitwise_not()
If we have Img1, Img2 and mask, cv2.bitwise_and(Img1,Img2,mask) operate Img1&Img2 on the certain place masked by mask. 

* cv2.Canny()
gray is the input image, all the pixels whose gradients lower than low_threshold will be rejected, all the pixels whose gradients higher than high_threshold will be kept, the pixels whose gradients are between low_threshold and high_threshold will be kept only if those pixels are next to strong gradient pixels. The default of L2gradient is false which means we will use L1 norm to calculate the gradient.
> edges = cv2.Canny(gray, low_threshold, high_threshold,L2gradient)

* cv2.GaussianBlur()
We should specify the width and height of the kernel which should be positive and odd. We also should specify the standard deviation in the X and Y directions, sigmaX and sigmaY respectively. If only sigmaX is specified, sigmaY is taken as equal to sigmaX. If both are given as zeros, they are calculated from the kernel size. 
> blur = cv2.GaussianBlur(img,(5,5),0) **(kernel must be odd)**

* cv2.HoughLinesP()
A line can be represented as y = mx+c or in parametric form, as $\rho = x \cos \theta + y \sin \theta$ where \rho is the perpendicular distance from origin to the line, and \theta is the angle formed by this perpendicular line and horizontal axis measured in counter-clockwise.
cv2.HoughLines() returns the two parameters $\rho$ and $\theta$.
cv2.HoughLinesP() returns the four value of start and end points.


