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
```

In order to run the code, visual studios is needed. In order to recreate The name of the repo folder is call "termproject". In the folder it will include the standard files that come with visual studios such as the solution file and the resources for the code


## What each part in the convex hull function does

### Choose the bottom most point

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

### Sort the vector of "Points"

```
// Place the bottom-most point at first position
swap(points[0], points[min]);

// Sort n-1 points with respect to the first point.
// A point p1 comes before p2 in sorted output if p2
// has larger polar angle in counterclockwise
// direction than p1
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

![image](https://user-images.githubusercontent.com/114605559/203659957-bcc8b650-3b90-41f7-afe0-478c7fff6eb3.png)

### Remove points that are in a line, execpt for the furthest point

```
for (int i = 1; i < temp.size(); i++)
{
	// Keep removing i while angle of i and i+1 is same
	// with respect to p0
	while ((i < temp.size() - 1 && orientation(p0, temp[i],
		temp[i + 1]) == 0))
		i++;

	black_points.push_back(temp[i]);
}
```

If two points happen to on the same line from the p0. Then we just add the furthest point to the black_points vector.

The black_points vector only contains pixels that are black 

Ex. In the image below, our code will skip p2, and add p3 to the black_points vector

![image](https://user-images.githubusercontent.com/114605559/203660490-73927f36-ab4c-4d72-8d5e-b41eb0d431fe.png)


### Determine orientation and Print convex hull

```
if (black_points.size() < 3) return;

// Create an empty stack and push first three points
// to it.
stack<Point> S;
S.push(black_points[0]);
S.push(black_points[1]);
S.push(black_points[2]);

// Process remaining n-3 points
for (int i = 3; i < black_points.size(); i++)
{
	// Keep removing top while the angle formed by
	// points next-to-top, top, and points[i] makes
	// a non-left turn
	while (S.size() > 1 && orientation(nextToTop(S), S.top(), black_points[i]) != 2)
		S.pop();
	S.push(black_points[i]);
}

// Now stack has the output points, print contents of stack
while (!S.empty())
{
	Point p = S.top();
	cout << p.x << ";" << p.y << endl;
	S.pop();
}
```

Depending on the orientation of the points, either add them or remove them from stack

Basically, this is the driving code that outlines our convex hull.
