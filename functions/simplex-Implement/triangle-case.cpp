//Created this utilizing the plan that Matt had outlined previously
//Since I was unsure about how we would incorporate the triangle case tests back into our other functions, I commented two approaches as to how it would move forward
//Also included a cross product function as it was missing on a previous file I used and I needed it for the implementation
//This is only the functions, which can just be copy-pasted into the original GJK.cpp.

//The cross product function I needed
Point GJK::cross(Point a, Point b)
{
    return {{a.x * b.y},{b.x * a.y}};
}

//The rough skeleton for a triangle case. I switched the function type to bool though it originated as void.
bool GJK::triangle_case()
{
    Point A = simplex[0]; // Declaring all points for usage in the triangle case (for the sake of simplification)
    Point B = simplex[1];
    Point C = simplex[2];
    //Initializes each edge of the simplex triangle
    Point CB = {{B.x - C.x},{B.y - C.y}};
    Point CA = {{A.x - C.x},{A.y - C.y}};
    Point CO = {-C.x, -C.y};
    //Finds the CB and AB perpendiculars utilizing triple cross product
    Point CBperp = cross(cross(CA,CB),CB);
    Point CAperp = cross(cross(CB,CA),CA);
    //Each edge case that needs to be tested
    if(dot(CBperp,CO) > 0){
        simplex.erase(simplex.begin()); // removes A from the simplex vector
        direction = CBperp;
        //some return case where it tosses the simplex back to the line case to find the next point on the Minkowski or
        //return false
    }
    else if(dot(CAperp,CO) > 0){
        simplex.erase(simplex.begin()+1); // Removes B from the simplex vector
        direction = CAperp;
        //some return case where it tosses the simplex back to the line case to find the next point on the Minkowski or
        //return false
    }
    //If it fails the prior two edge cases, the origins lies within the polygon, therefore there is collision
    else{
        //Some return case that defines the collision as true
        //return true
    }
}
