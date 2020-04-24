clc;
clear;

x = 1;
y = 2;
z = 3;

start_point = [ 0; 0; 0 ];
end_point = [ 0; 0; 10 ];

delta_x = end_point(x) - start_point(x);
delta_y = end_point(y) - start_point(y);
delta_z = end_point(z) - start_point(z);

length = sqrt(delta_x^2 + delta_y^2 + delta_z^2);s
