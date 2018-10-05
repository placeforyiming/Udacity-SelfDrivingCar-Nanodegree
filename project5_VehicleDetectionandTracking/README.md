

## Vehicle Detection Project

The goals / steps of this project are the following:

* Perform a Histogram of Oriented Gradients (HOG) feature extraction on a labeled training set of images and train a classifier Linear SVM classifier
* Optionally, you can also apply a color transform and append binned color features, as well as histograms of color, to your HOG feature vector. 
* Note: for those first two steps don't forget to normalize your features and randomize a selection for training and testing.
* Implement a sliding-window technique and use your trained classifier to search for vehicles in images.
* Run your pipeline on a video stream (start with the test_video.mp4 and later implement on full project_video.mp4) and create a heat map of recurring detections frame by frame to reject outliers and follow detected vehicles.
* Estimate a bounding box for vehicles detected.

[//]: # (Image References)
[image1]: ./report/0.png
[image2]: ./report/1.png
[image3]: ./report/2.png
[image4]: ./report/3.png

[video1]: ./Res_Project_video.mp4

### Color Histogram

I choose all those three color spaces that we have learned before, and gather the histogram in each channel. Then, I concatenate them together, here is the result.
![alt text][image1]


### Histogram of Oriented Gradients (HOG)

#### 1. Explain how (and identify where in your code) you extracted HOG features from the training images.

The code for this step is contained in the fouth code cell of the IPython notebook, I define a function **HOG()** here to extract the feature.  

I started by setting all the parameters the same with the course materials, and then apply this function on one car image and one non-car image. Here is the result:
![alt text][image2]



#### 2. Explain how you settled on your final choice of HOG parameters.

I try to tuning the parameters when I want to detect the car in test images. However, I found those paraeters still need to be changed further when I change to video part. So, finally I choose a combination with $pix_per_cell = 16, cell_per_block = 2, orient = 11$ which make the final result looks better.

#### 3. Describe how (and identify where in your code) you trained a classifier using your selected HOG features (and color features if you used them).

The code for this step is contained in the tenth code cell of the IPython notebook. In the beginning, I trained the SVC model with grid_search for parameters. Although the test accuracy is perfect, I can not make it looks good for the real image. I guess it may be overfitting. So I change the model to linear SVC, which is both good for the classifier and the real image.

![alt text][image4]

### Sliding Window Search

#### 1. Describe how (and identify where in your code) you implemented a sliding window search.  How did you decide what scales to search and how much to overlap windows?

I abondan the top half image, since there is just sky or tree. The minimum size of box is (64,64) which can keep the stable of the HOG feature. I set the scale of the box to three types, [64,80,96]. Bigger box will contain too much information which is useless. 

#### 2. Show some examples of test images to demonstrate how your pipeline is working.  What did you do to optimize the performance of your classifier?

First, I create a all zero matrix(heat map) which has the same shape with the input image. Then, I pick the region of interest and crop information in those 3 kinds of scale and do the classification. If the predicting result is 1, I add 1 in the corresponding part in heat map. Next, I use a threshold to filter all those pixels who's value is smaller than the threshold. Finally, I use label function to choose the four points for the final bounding box.

![alt text][image3]
---

### Video Implementation

#### 1. Provide a link to your final video output.  Your pipeline should perform reasonably well on the entire project video (somewhat wobbly or unstable bounding boxes are ok as long as you are identifying the vehicles most of the time with minimal false positives.)
Here's a [link to my video result](./Res_Project_video.mp4)


#### 2. Describe how (and identify where in your code) you implemented some kind of filter for false positives and some method for combining overlapping bounding boxes.

I recorded the positions of positive detections in 5 frames of the video.  From the positive detections I created a heatmap and then thresholded that map to identify vehicle positions.  I then used `scipy.ndimage.measurements.label()` to identify individual blobs in the heatmap.  I then assumed each blob corresponded to a vehicle.  I constructed bounding boxes to cover the area of each blob detected.  



---

### Discussion

#### 1. Briefly discuss any problems / issues you faced in your implementation of this project.  Where will your pipeline likely fail?  What could you do to make it more robust?

The bounding box is not stable, and the prediction speed is too slow to be used in the rael situation.

