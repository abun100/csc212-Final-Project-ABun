# csc212-Final-Project-ABun
## Convex hull Project
```
IMPORTANT 

Our source code is implemented with sfml. 
The Project files include :

App.cpp, App.h 

ScanImage.cpp, ScanImage.h

Minkowski.cpp, Minkowski.h 

GJK.cpp, GJK.h

main.cpp

All code for the files will be uploaded in the folder call "FinalProduct"

Dot File is under "dot" folder

NONFINAL PRODUCT : The "Front End" Folder and "Function" Folder are previous work folder
```
### Instructions for the initial setup for sfml

In order to run the code, visual studios and sfml is needed. To recreate our project repo in visual studios, you will need to download the sfml external folder. Here is the link to the sfml downlaod folder https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-64-bit.zip . 

It will be downloaded in a zip file and you must extract the files within the zip. Once this is done, you must create an additionaly folder called external. From the sfml file, copy the folders called "include" and "lib" and paste them into the external folder. 

The next step is to create a new c++ project and copy all the source code from the "FinalProduct" folder in our github repo. You will also need to place the external folder into the c++ project repo. 

Go into the Project Properties, find C/C++ and go under general, click on "Additional Include Directories" and click edit

![image](https://user-images.githubusercontent.com/114605559/205793804-b826c28e-b5fa-4ab3-99e9-f8803e560989.png)

Paste this into the first box `$(SolutionDir)\External\include`

You will need to do the same process under the Linker tab under general. 

![image](https://user-images.githubusercontent.com/114605559/205794184-7b39872e-7bfe-4614-bacf-4d411caa823d.png)

Paste this `$(SolutionDir)\External\lib`

Go under Linker tab, then input

![image](https://user-images.githubusercontent.com/114605559/205794433-a8f55c60-f7ca-4bb6-bd6c-f6d621704f6a.png)

Paste these into the additional dependecies 
```
sfml-system-d.lib
sfml-graphics-d.lib
sfml-window-d.lib
sfml-audio-d.lib
sfml-network-d.lib
```
## Before you run

Our application takes in two binary images represented in a text file format. Here is a useful link to convert any image into a binary image. https://www.dcode.fr/binary-image

You will need to create a two text files and copy the image text values from the website and paste them in text files. However, two text files will be provided in our github repo. `shilouette1.txt` and `shilouette2.txt` . Place the text files into a folder where you can access them.

## Command line
```
&.\Directory file_name.txt file_name2.txt
```
Once you have all the source code files copied into the project, inputed the command line in visual studios, you can hit the green run button in visual studios. (Or hit ctrl + f5)

## Inside the application
Once you run the application, a new windown will pop up it should look this. 

![image](https://user-images.githubusercontent.com/114605559/205797463-a8530de0-f5ca-4ac5-ba83-2afd04c59159.png)

The red polygon in the middle represents the minkowski difference

The blue and green polygon are the outline (convex hull) from the images include in the project

### Controls
W, S, A, D : controls to move up, down, left, right

space bar : to rotate the shape

G : test collisions 
