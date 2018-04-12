function xyzTdoa()
% Determine position with someone's algorithm 
% Authors: Danial Mahmoud and Jonas Eiselt
%
% [1] A Synthesizable Low Power VHDL Model of the Exact Solution of
% Three Dimensional Hyperbolic Positioning System
% 

v = 343;

di = 1.939;
dj = 3.4264;
dk = 2.7821;
dl = 3.9674;

di = 4.2308;
dj = 3.9370;
dk = 2.4290;
dl = 1.8708;


xi = 0;
xj = 4;
xk = 0;
xl = 4;

yi = 0;
yj = 0;
yk = 4;
yl = 4;

zi = 2;
zj = 2;
zk = 2;
zl = 2;

Rik = di-dk;
Rij = di-dj;
Rkl = dk-dl;
Rkj = dk-dj;
Rkl = dk-dl;

xji = xj - xi;
xki = xk-xi;
xjk = xj-xk;
xlk = xl-xk;

yki = yk-yi;
yji=yj-yi;
ylk = yl-yk;
yjk=yj-yk;

zki = zk-zi;
zji = zj-zi;
zjk = zj-zk;
zlk = zl-zk;



A = (Rik*xji-Rij*xki)/(Rij*yki-Rik*yji);
B = (Rik*zji-Rij*zki)/(Rij*yki-Rik*yji);
C = (Rik*(Rij^2+xi^2-xj^2+yi^2-yj^2+zi^2-zj^2)-(Rij*(Rik^2+xi^2-xk^2+yi^2-yk^2+zi^2-zk^2)))/(2*(Rij*yki-Rik*yji));
D = (Rkl*xjk-Rkj*xlk)/(Rkj*ylk-Rkl*yjk);
E = (Rkl*zjk-Rkj*zlk)/(Rkj*ylk-Rkl*yjk);
F = (Rkl*(Rkj^2+xk^2-xj^2+yk^2-yj^2+zk^2-zj^2)-(Rkj*(Rkl^2+xk^2-xl^2+yk^2-yl^2+zk^2-zl^2)))/(2*(Rkj*ylk-Rkl*yjk));
G = (E-B)/(A-D);
H = (F-C)/(A-D);
I = A*G + B;
J = A*H + C;
K = Rik^2+xi^2-xk^2+yi^2-yk^2+zi^2-zk^2+2*xki*H+2*yki*J;
L = 2*(xki*G+yki*I+2*zki);
M = 4*Rik^2*(G^2+I^2+1)-L^2;
N = 8*Rik^2*(G*(xi-H)+I*(yi-J)+zi)+(2*L*K);
O = 4*Rik^2*((xi-H)^2+(yi-J)^2+zi^2)-K^2;

%z1 = (N/(2*M))+sqrt((N/(2*M))^2-(O/M))
z2 = (N/(2*M))-sqrt((N/(2*M))^2-(O/M))

x = G*z2 + H
y = I*z2 + J

end


