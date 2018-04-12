function xyFang()
% FANG Determine position with Fang's algorithm 
% Authors: Danial Mahmoud and Jonas Eiselt
%
% First base station (BS) needs to be located at (0,0), second BS at
% (x2,0) and third BS at (x3,y3) [1, p. 234].
% [1] J. Stefa?ski, Hyperbolic Position Location Estimation in the 
% Multipath Propagation Environment.
% 

x2 = 4; 
x3 = 2; 
y3 = 4;

% case 1
actualPos = [1, 1.5]; 
T = [0.0052, 0.0093, 0.0079];
[x,y] = calcPos(T);
fprintf('(%.4f, %.4f) vs (%.2f, %.2f)\n', x, y, actualPos(1), actualPos(2))

% case 2
actualPos = [3, 1.5]; 
T = [0.0099, 0.0050, 0.0079];
[x,y] = calcPos(T);
fprintf('(%.4f, %.4f) vs (%.2f, %.2f)\n', x, y, actualPos(1), actualPos(2))

% case 3
actualPos = [1, 3]; 
T = [0.0092, 0.0122, 0.0041];
[x,y] = calcPos(T);
fprintf('(%.4f, %.4f) vs (%.2f, %.2f)\n', x, y, actualPos(1), actualPos(2))

% case 4
actualPos = [3, 3]; 
T = [0.0122, 0.0092, 0.0041];
[x,y] = calcPos(T);
fprintf('(%.4f, %.4f) vs (%.2f, %.2f)\n', x, y, actualPos(1), actualPos(2))

% case 5
actualPos = [2, 2]; 
T = [0.0082, 0.0082, 0.0058];
[x,y] = calcPos(T);
fprintf('(%.4f, %.4f) vs (%.2f, %.2f)\n', x, y, actualPos(1), actualPos(2))

% case 6
actualPos = [1.5, 0.5]; 
T = [0.0047, 0.0076, 0.0103];
[x,y] = calcPos(T);
fprintf('(%.4f, %.4f) vs (%.2f, %.2f)\n', x, y, actualPos(1), actualPos(2))

% case 7
actualPos = [2.5, 0.5]; 
T = [0.0076, 0.0047, 0.0103];
[x,y] = calcPos(T);
fprintf('(%.4f, %.4f) vs (%.2f, %.2f)\n', x, y, actualPos(1), actualPos(2))

% case 8
actualPos = [1, 3.5]; 
T = [0.0105, 0.0134, 0.0032];
[x,y] = calcPos(T);
fprintf('(%.4f, %.4f) vs (%.2f, %.2f)\n', x, y, actualPos(1), actualPos(2))

% case 9
actualPos = [3, 3.5]; 
T = [0.0134, 0.0105, 0.0032];
[x,y] = calcPos(T);
fprintf('(%.4f, %.4f) vs (%.2f, %.2f)\n', x, y, actualPos(1), actualPos(2))

    function [x, y] = calcPos(T)
        flipPOV = 0;
        if T(2) < T(1)
            flipPOV = 1;
            t1 = T(2);
            t2 = T(1);
        elseif T(2) == T(1)
            t1 = T(1);
            t2 = T(2)+0.0001;
        else
            t1 = T(1);
            t2 = T(2);
        end
        t3 = T(3);
        
        v = 343;
        r21 = v*(t2-t1);
        r31 = v*(t3-t1);
        
        g = (r31*(x2/r21)-x3)/y3;
        h = (x3^2+y3^2-r31^2+(r31*r21)*(1-(x2/r21)^2))/(2*y3);
        d = -(1-(x2/r21)^2+g^2);
        e = x2*(1-(x2/r21)^2)-(2*g*h);
        f = (r21^2/4)*(1-(x2/r21)^2)^2-h^2;
        
        x = (-e-sqrt(e^2-(4*d*f)))/(2*d);
        y = g*x+h; 
        
        if flipPOV == 1
            x = x2 - x;
        end
    end
end
