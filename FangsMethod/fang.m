function [ x, y ] = fang( )
% FANG Summary of this function goes here
%   Detailed explanation goes here

t1 = 0.0061;
t2 = 0.0085-t1;
t3 = 0.0074-t1;

t1 = 0.0151;
t2 = abs(0.0063-t1);
t3 = abs(0.0066-t1);

t1 = 0.0063;
t2 = 0.0105-t1;
t3 = 0.0066-t1;

% x1 = 0;
% y1 = 0;

x2 = 4;
% y2 = 0;

x3 = 2;
y3 = 4;

v = 343;
r21 = v*t2; %(t2-t1);
r31 = v*t3; %(t3-t1);

g = (r31*(x2/r21)-x3)/y3;
h = (x3^2+y3^2-r31^2+(r31*r21)*(1-(x2/r21)^2))/(2*y3);
d = -(1-(x2/r21)^2+g^2);
e = x2*(1-(x2/r21)^2)-(2*g*h);
f = (r21^2/4)*(1-(x2/r21)^2)^2-h^2;

x = (-e-sqrt(e^2-(4*d*f)))/(2*d)
y = g*x+h



% R1 = sqrt(x^2+y^2)
% R2 = sqrt((x2-x)^2+(y2-y)^2)
% R3 = sqrt((x3-x)^2+(y3-y)^2)

end
