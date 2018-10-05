# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program




## PID Explain

* P is proportional control. Proportinal means the more you leave the right direction, the more change you should make. This part of controller can push the car go toward the right direction. However, P control also will cause the fluctuation of the movement, since the constant proportional rate may change the direction too much.

* D is differential control. Differential means the slower the direction was changed, the less change you should make. The constant P control rate means if the car get closer to the right direction, the changing speed will decrease. Then, the D control can further decrease the changing speed which can help the car drive smoothly. 

* I is integral control. PD control has no idea about systematic error. The I controller can help the car remember accumulated erorr, the larger the accumulated erorr is, the more change the car should make.

## How to choose the right parameters for PID controller.

Basically, I change the parameters manually.

The P control is the major part of the PID control, so I set D and I with zero in the beginning. The proportional rate should be a value between 0 and 1, so I set P = 0.2. I try (P,I,D)=(0.2,0.0,0.0), and the car can drive for a while but fail in the first circle. So I use a less P with 0.15 which still fail in the first circle but perform pretty stable.

In order to overcome fluctuation, I set D with 4. So I try (P,I,D)=(0.15, 0.0, 4.0), but the car fail very quick in the beginning. Next, I decrease the D a half, I try (P,I,D)=(0.15, 0.0, 2.0). This time, the car can drive much better than before, then I decrease the D further a little. With (P,I,D)=(0.15, 0.0, 1.5), I successfully make the car drive the whole track.

Since I is about the accumulated error, I don't think it can be a large number. So I start with I = 0.01. After trying (P,I,D)=(0.15, 0.01, 1.5), I found the car just become a little bit unstable. I guess maybe there is no systematic error in this case, then I just set I with 0.001.

Finally, I use the setting of (P,I,D)=(0.15, 0.001, 1.5) to make the car successfully drive the whole track.







---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

