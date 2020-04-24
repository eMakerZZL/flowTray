close all;
clear all;
clc;

hold on;

Vs = 0;
Ve = Vs;
Vc = 200;
L = 3000;

J = 500;

T = sqrt((Vc - Vs) / J);
Sa = (Vc + Vs) * T;

T1 = T;
T2 = T;
T3 = (L - 2 * Sa) / Vc;
T4 = T;
T5 = T;

t1 = linspace(0          , T          , 1000);
t2 = linspace(T          , 2 * T      , 1000);
t3 = linspace(2 * T      , 2 * T + T3 , 1000);
t4 = linspace(2 * T + T3 , 3 * T + T3 , 1000);
t5 = linspace(3 * T + T3 , 4 * T + T3 , 1000);

a1 = J * t1;
a2 = 2 * J * T - J * t2;
a3 = 0;
a4 = 2 * J * T - J * (t4 - T3);
a5 = -4 * J * T + J * (t5 - T3);

v1 = Vs + 1/2 * J * t1.^2;
v2 = Vs -     J * T^2 + 2 * J * T * t2 - 1/2 * J * t2.^2;
v3 = Vc * ones(1,1000);
v4 = Vs -     J * T^2 + 2 * J * T * (t4 - T3) - 1/2 * J * (t4 - T3).^2;
v5 = Vs - 4 * J * T * (t5 - T3) + 1/2 * J * (t5 - T3).^2 + 8 * J * T^2;

subplot(2,1,1);
plot(t1,a1,t2,a2,t3,a3,t4,a4,t5,a5);
grid on;

subplot(2,1,2);
plot(t1,v1,t2,v2,t3,v3,t4,v4,t5,v5);
grid on;

