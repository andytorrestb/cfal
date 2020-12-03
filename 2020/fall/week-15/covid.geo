// Author: Andy Torres

// x - coordinates
x0 = 0;
x1 = 2;
x2 = 3;
x3 = 9;
x4 = x3 + 1;
x5 = 13;
x6 = 14;
x7 = 15;

// y - coordinates
y0 = 0;
y1 = 10;
y2 = 11;
y3 = 12;
y4 = 13;
y5 = 14;

// z - coordinates
zmin = 0;

// bottom left
Point(1) = {x0, y0, zmin, 1.0};

// bottom right
Point(2) = {x5, y0, zmin, 1.0};


// top left
Point(3) = {x0, y3, zmin, 1.0};

// top right
Point(4) = {x7, y3, zmin, 1.0};

// left wall inlet
Point(5) = {x0, y1, zmin, 1.0};
Point(6) = {x0, y2, zmin, 1.0};

// right wall inlet
Point(7) = {x7, y1, zmin, 1.0};
Point(8) = {x7, y2, zmin, 1.0};

// left vent opening
Point(9) = {x1, y3, zmin, 1.0};
Point(10) = {x2, y3, zmin, 1.0};

// right vent opening
Point(11) = {x6, y3, zmin, 1.0};
Point(12) = {x5, y3, zmin, 1.0};

// left vent elbow
Point(13) = {x1, y4, zmin, 1.0};
Point(14) = {x2, y4, zmin, 1.0};
Point(15) = {x2, y5, zmin, 1.0};

// right vent elbow
Point(16) = {x6, y4, zmin, 1.0};
Point(17) = {x5, y4, zmin, 1.0};
Point(18) = {x5, y5, zmin, 1.0};

// top vent base
Point(19) = {x3, y5, zmin, 1.0};
Point(20) = {x4, y5, zmin, 1.0};
