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



## What each part in the convex hull function does
```
// Find the bottommost point of the black set of points
	int ymin = points[0].y, min = 0;
	for (int i = 1; i < points.size(); i++)
	{
		int y = points[i].y;

		// Pick the bottom-most or choose the left
		// most point in case of tie
		// only chooses the bottom most black point (0)
		if (((y < ymin) || (ymin == y &&
			points[i].x < points[min].x)) &&
			points[i].color == 0)
			ymin = points[i].y, min = i;
	}
```
in a set of points choose the bottom most point. In the example below, it chooses the bottom left most point, represented by 0.

111111

111111

111111

011111

```
// Place the bottom-most point at first position
swap(points[0], points[min]);

// Sort n-1 points with respect to the first point.
// A point p1 comes before p2 in sorted output if p2
// has larger polar angle (in counterclockwise
// direction) than p1
p0 = points[0];
temp.push_back(points[0]);
black_points.push_back(points[0]);

qsort(&points[1], points.size() - 1, sizeof(Point), compare);

for (auto& elem : points) {
	if (elem.color == 1) { continue; }
	temp.push_back(elem);
}
```

set p0 (intital points we want to compare every other point to by polar angle)

places p0 at the start of a temp vector and the black points vector

sorts the rest of the points based on polar angle
