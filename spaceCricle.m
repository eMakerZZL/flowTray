close all;
clear all;
clc;

draw_point = @(point,style) plot3(point(1),point(2),point(3),style,'LineWidth',5);
unit_vector = @(vec) vec / norm(vec);

point_a = [3 7 5];
% point_b = [5 3 8];
% point_c = [8 5 1];
point_b = [8 5 1];
point_c = [5 3 8];

v_ab = point_b - point_a;
v_ac = point_c - point_a;

n = cross(v_ab, v_ac);
n = unit_vector(n);

if (norm(n) == 0)
    error('three points collinear!\r\n');
    exit;
end

v_abn = cross(n, v_ab);
v_acn = cross(n, v_ac);

v_abn = unit_vector(v_abn);
v_acn = unit_vector(v_acn);

c_ab = (point_a + point_b) ./ 2;
c_ac = (point_a + point_c) ./ 2;

a = n(n == 1);
if (isempty(a))
    a = 0;
end

A = zeros(2,2);
B = zeros(2,1);
if (a == 1)
    A(1,1) = v_abn(2);
    A(2,1) = v_abn(3);
    A(1,2) = -v_acn(2);
    A(2,2) = -v_acn(3);

    B(1) = c_ac(2) - c_ab(2);
    B(2) = c_ac(3) - c_ab(3);
elseif (a == 2)
    A(1,1) = v_abn(1);
    A(2,1) = v_abn(3);
    A(1,2) = -v_acn(1);
    A(2,2) = -v_acn(3);
    
    B(1) = c_ac(1) - c_ab(1);
    B(2) = c_ac(3) - c_ab(3);
elseif (a == 3)
    A(1,1) = v_abn(1);
    A(2,1) = v_abn(2);
    A(1,2) = -v_acn(1);
    A(2,2) = -v_acn(2);

    B(1) = c_ac(1) - c_ab(1);
    B(2) = c_ac(2) - c_ab(2);
else
    A = [v_abn(1:2).' -v_acn(1:2)'];
    B = (c_ac(1:2) - c_ab(1:2))';
end

C = A \ B;

center = v_abn .* C(1) + c_ab;
r = norm(point_a - center);

v_a = unit_vector(v_ab);
v_b = unit_vector(v_abn);
alpha = linspace(0, 2*pi, 1000);

x = center(1) + r .* v_a(1) .* cos(alpha) + r .* v_b(1) .* sin(alpha);
y = center(2) + r .* v_a(2) .* cos(alpha) + r .* v_b(2) .* sin(alpha);
z = center(3) + r .* v_a(3) .* cos(alpha) + r .* v_b(3) .* sin(alpha);

h = 0.001;
k = sqrt(h * (2 * r - h));
delta_beta = asin(k / r);
beta = 0 : delta_beta : 2 * pi;

v_oa = point_a - center;
k = n;
s = cross(k,v_oa);

points = zeros(length(beta),3);
for i = 1 : length(beta)
    a1 = cos(beta(i)) .* v_oa;
    a2 = (1 - cos(beta(i))) * dot(v_oa,k) .* v_oa;
    a3 = sin(beta(i)) .*s;
    points(i,:) = a1 + a2 + a3;
    points(i,:) = points(i,:) + center;
end

figure;
hold on;
grid on;
axis equal;
view(3);
plot3(x,y,z);
plot3(points(:,1),points(:,2),points(:,3), 'ko');
move_p = plot3(points(1,1),points(1,2),points(1,3),'ko','LineWidth',5);
draw_point(point_a,'ro');
draw_point(point_b,'go');
draw_point(point_c,'bo');
draw_point(center,'mo');
arrow3(point_a,point_b);
arrow3(point_a,point_c);

for i = 1 : length(beta)
    set(move_p,'xdata',points(i,1),'ydata',points(i,2),'zdata',points(i,3));
    pause(0.01);
end
