## Writeup for Project 4 


---

**Advanced Lane Finding Project**

The goals / steps of this project are the following:

* Compute the camera calibration matrix and distortion coefficients given a set of chessboard images.
* Apply a distortion correction to raw images.
* Use color transforms, gradients, etc., to create a thresholded binary image.
* Apply a perspective transform to rectify binary image ("birds-eye view").
* Detect lane pixels and fit to find the lane boundary.
* Determine the curvature of the lane and vehicle position with respect to center.
* Warp the detected lane boundaries back onto the original image.
* Output visual display of the lane boundaries and numerical estimation of lane curvature and vehicle position.

[//]: # (Image References)

[image1]: ./Report/1.jpg "FindPointsinChessboard"
[image2]: ./Report/2.jpg "UndistortChessboard"
[image3]: ./Report/3.jpg "UndistortRoad"
[image4]: ./Report/4.jpg "Change to bird view"
[image5]: ./Report/5.jpg "Color Selection"
[image6]: ./Report/6.jpg "Gradient Selection"
[image7]: ./Report/7.jpg "Combining Selection"
[image8]: ./Report/8.jpg "MovingBoxandInterpolate"
[image9]: ./Report/9.jpg "MovingBoxandInterpolate"
[image10]: ./Report/10.jpg "Put everything on initial picture"

[video1]: ./Result_project_video.mp4 "Video"

## [Rubric](https://review.udacity.com/#!/rubrics/571/view) Points

### Here I will consider the rubric points individually and describe how I addressed each point in my implementation.  

#### Step 1: Find and draw points on the chessboard.

Useing _**cv2.findChessboardCorners()**_ to find the corner and _**cv2.drawChessboardCorners**_ to draw back the points on to original image.
![alt text][image1]

#### Step 2: Using a number of images to get the undistorted matrix.

Using for loop to get objpoints, imgpoints as many as possible. Then, apply _**cv2.calibrateCamera()**_ to get the undistorted matrix. After getting the undistorted matrix, I use this matrix to caliberate original images.
![alt text][image2]
![alt text][image3]

#### Step 3: Perspective Transform

Here is my source and destination points:

| Source        | Destination   | 
|:-------------:|:-------------:| 
| 575, 464      | 450, 0        | 
| 707, 464      | 450, 720      |
| 258, 682      | 830, 720      |
| 1049, 682     | 830, 0        |

I define a function with OpenCV's related function like this:
>
def unwarp(img, src, dst):
....h,w = img.shape[:2]
....# use cv2.getPerspectiveTransform() to get M, the transform matrix, and Minv, the inverse
....M = cv2.getPerspectiveTransform(src, dst)
....Minv = cv2.getPerspectiveTransform(dst, src)
....# use cv2.warpPerspective() to warp your image to a top-down view
....warped = cv2.warpPerspective(img, M, (w,h), flags=cv2.INTER_LINEAR)
....# limit the region
....warped[:,:380,:]=0
....warped[:,(w-380):,:]=0
....return warped, M, Minv

Then I apply this function to the original image, here is the result:
![alt text][image4]

#### Step 4: Filter the whole image with color.

According to the materials in this part, the S channel in HLS space is good at selecting yellow color pixels and the R channel in RGB space is good at selecting white color pixels. So I build a color selecting function which combine those two part. Here is my result:
![alt text][image5]

#### Step 5: Filter the whole image with gradient.

I choose the absolute gradient in x direction, the absolute gradient in y direction, the magnitude of gradient and the angle of gradient as the basic selecting method. I try and set the threshold for all those four individual selecting method and combine them together. Here is the result of the final combination.
![alt text][image6]

#### Step 6: Put all the things together.

Until now, we already have four steps to process the original image. We can undistorted the image, unwarped the image and then filter the image with color and gradient. Here I put them together to see the final result on the input image.
![alt text][image7]

#### Step 7: Sliding window.

I just follow the online materials in this part. Finding the point which has the most white pixels. Sliding 9 windows in the vertical direction. Drawing the bounding box and interpolate the lines. After that, I also follow the instruction to make the output image look better, and here is my result:
![alt text][image9]

#### Step 8: Add the result back on the original image.

We have already get the lane line, then we warp back the result to get the lane line on the image with the same size of original image. Finally, we use _**cv2.addWeighted()**_ function two add those two images together. And here is the result.
![alt text][image10]


---

### Pipeline (video)

#### 1. Provide a link to your final video output.  Your pipeline should perform reasonably well on the entire project video (wobbly lines are ok but no catastrophic failures that would cause the car to drive off the road!).

Here's a [link to my video result](./Result_project_video.mp4)

---

### Discussion

#### 1. Briefly discuss any problems / issues you faced in your implementation of this project.  Where will your pipeline likely fail?  What could you do to make it more robust?

Lots of part can lead to the failure of this method. In the challenge video, the shade of trees, the strong sun light, the curved lane, all those things will fail this method. And the other drawback of this method is the case sensitivity of choosing parameters. Some values of parameters work perfect on some situations. However, if we use those parameters to deal with the other situation, we will fail.

 
