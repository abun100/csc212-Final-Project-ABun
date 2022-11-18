# csc212-Final-Project-ABun
## Convex hull initial plan
```
We could use color picker concept to map out convex hull
make a simpler map given a real life google maps
Select the borders of main features in a map (ex. house, streets, highways)
ignore noise in pictures (random objects, like cars, people, and envirnment)
```

## Psuedocode

- Given an image convert each pixel image into there rgb value

&emsp; While we are not at the end of the img pixels 

&emsp; if(pixel is this color) : convert pixel to that rgb value 

- We pick a random pixel in the image

- Based on that pixel’s image color, we used the graham scan to find surrounding similar pixels

&emsp; Use graham scan to find the outline of shape we’re choosing

&emsp; Has to have pixels connect from the chosen pixel to the outer border

&emsp; Push those pixels into a vector

- Return the convex hull 

&emsp; Return the set of pixels in there original positions and only include that area

- Convert the convex hull back to a picture

- Copy picture to clipboard

- Paste picture into external software (ex. paint)
