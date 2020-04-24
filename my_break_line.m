close all;
clear all;
clc;

steps = 1000;
delta_radian = linspace(0, 2 * pi, steps);

p1.x = 0;
p1.y = 0;

p2.x = 3;
p2.y = 3;

p3.x = 2;
p3.y = 1;

[x0,y0,r] = ThreePointsDetermineCircle(p1,p2,p3);

circle.radius = r; 
circle.x0 = x0;
circle.y0 = y0;
circle.x = circle.x0 + circle.radius * cos(delta_radian);
circle.y = circle.y0 + circle.radius * sin(delta_radian);

plot(circle.x, circle.y);
axis equal;
grid on;
hold on;

delta_l = 1/2 * circle.radius;
delta_alpha = asin(delta_l / (2 * circle.radius));
alpha = 0 : delta_alpha : 2 * pi;
alpha = [alpha, 2 * pi];
x = circle.x0 + circle.radius * cos(alpha);
y = circle.y0 + circle.radius * sin(alpha);

line(x,y,'Color','r');

