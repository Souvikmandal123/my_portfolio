#include<bits/stdc++.h>
using namespace std;
struct Point {
    int x, y;
};
// Comparator function to sort points based on x-coordinate (and y-coordinate in case of a tie)
bool comparePoints(const Point &a, const Point &b) {
    return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}
// Cross product of vectors (p1-p0) and (p2-p0)
int crossProduct(const Point &p0, const Point &p1, const Point &p2) {
    int x1 = p1.x - p0.x;
    int y1 = p1.y - p0.y;
    int x2 = p2.x - p0.x;
    int y2 = p2.y - p0.y;
    return x1 * y2 - x2 * y1;
}
// Graham's Scan algorithm to find the convex hull
vector convexHull(vector &points) {
    int n = points.size();
    if (n <= 3) return points;
    // Sort the points based on x-coordinate (and y-coordinate in case of a tie)
    sort(points.begin(), points.end(), comparePoints);
    // Initialize the upper and lower hulls
    vector upperHull, lowerHull;
    // Build the upper hull
    for (int i = 0; i < n; i++) {
        while (upperHull.size() >= 2 && crossProduct(upperHull[upperHull.size() - 2], upperHull.back(), points[i]) <= 0) {
            upperHull.pop_back();
        }
        upperHull.push_back(points[i]);
    }
    // Build the lower hull
    for (int i = n - 1; i >= 0; i--) {
        while (lowerHull.size() >= 2 && crossProduct(lowerHull[lowerHull.size() - 2], lowerHull.back(), points[i]) <= 0) {
            lowerHull.pop_back();
        }
        lowerHull.push_back(points[i]);
    }
    // Combine the upper and lower hulls to get the convex hull
    upperHull.pop_back(); // Remove the last point to avoid duplication
    lowerHull.pop_back();
    upperHull.insert(upperHull.end(), lowerHull.begin(), lowerHull.end());
    return upperHull;
}
// Calculate the area of a polygon
double calculateArea(vector &polygon) {
    int n = polygon.size();
    if (n < 3) return 0.0; // Not a valid polygon
    double area = 0.0;
    for (int i = 0; i < n; i++) {
        int x1 = polygon[i].x;
        int y1 = polygon[i].y;
        int x2 = polygon[(i + 1) % n].x;
        int y2 = polygon[(i + 1) % n].y;
        area += (x1 * y2 - x2 * y1);
    }
    return abs(area) / 2.0;
}
int main() {
    int n;
    cin >> n;
    vector points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }
    vector convexHullPoints = convexHull(points);
    double maxArea = calculateArea(convexHullPoints);
    cout << maxArea << endl;
    return 0;
}