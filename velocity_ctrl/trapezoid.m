%v_min less than v_tray
clear all;
close all;
clc;

v_tray = 20;
v_max  = 200;
v_min  = 30;

a = 20;

tray_s1 = 100;

steps = 100;


if (v_min < v_tray) 
    endEffecotrs_s1 = (v_tray^2 - v_min^2) / (2*a);
    endEffecotrs_t1 = (v_tray - v_min) / a;

    tray_s2 = v_tray * endEffecotrs_t1 - endEffecotrs_s1;

    s = tray_s1 + tray_s2;

    % endEffecotrs_s2 = (v_max^2 - v_tray^2) / (2 * a);
    endEffecotrs_s2 = (v_max - v_tray)^2 / (2 * a);
    s1 = s - 2 * endEffecotrs_s2;
    if (s1 > 0)
        %can reach target v_max and have uniform velocity
        endEffecotrs_s3 = s1;
        endEffecotrs_t3 = s1 / v_tray;

        T = (v_max - v_tray) / a;
        endEffecotrs_t2 = T;
        endEffecotrs_s4 = endEffecotrs_s2;
        endEffecotrs_t4 = endEffecotrs_t2;

        V0 = ones(1,steps) * v_tray;
        V1 = v_min + a * linspace(0,endEffecotrs_t1,steps);
        V2 = v_tray + a * linspace(0,T,steps);
        V3 = ones(1,steps) * v_max;
        V4 = v_max - a * linspace(0,T,steps);

        t0 = tray_s1 / v_tray;
        T1 = linspace(t0      , endEffecotrs_t1 + t0      , steps);
        T2 = linspace(T1(end) , T1(end) + T               , steps);
        T3 = linspace(T2(end) , T2(end) + endEffecotrs_t3 , steps);
        T4 = linspace(T3(end) , T3(end) + T               , steps);
        T0 = linspace(0,T4(end),steps);

        plot(T0,V0,T1,V1,T2,V2,T3,V3,T4,V4);
        title('can reach target v_m_a_x and have uniform velocity');
    elseif (s1 == 0)
        %can reach target vmax but not have uniform velocity
        endEffecotrs_s3 = endEffecotrs_s2;
        T = (v_max - v_tray) / a;
        endEffecotrs_t2 = T;
        endEffecotrs_t3 = T;

        V0 = v_tray * ones(1,steps);
        V1 = v_min  + a * linspace(0,endEffecotrs_t1,steps);
        V2 = v_tray + a * linspace(0,T,steps);
        V3 = v_max  - a * linspace(0,T,steps);

        t0 = tray_s1 / v_tray;
        T1 = linspace(t0,t0 + endEffecotrs_t1,steps);
        T2 = linspace(T1(end),T1(end) + T,steps);
        T3 = linspace(T2(end),T2(end) + T,steps);
        T0  = linspace(0,T3(end),steps);

        plot(T0,V0,T1,V1,T2,V2,T3,V3);
        title('can reach target v_m_a_x but not have uniform velocity');
    else
        %can't reach target v_max
        endEffecotrs_s2 = s / 2;
        endEffecotrs_s3 = endEffecotrs_s2;

        T = sqrt((2 * endEffecotrs_s2) / (a));
        v_max = v_tray + a * T;

        endEffecotrs_t2 = T;
        endEffecotrs_t3 = T;

        V0 = v_tray * ones(1,steps);
        V1 = v_min  + a * linspace(0,endEffecotrs_t1,steps);
        V2 = v_tray + a * linspace(0,T,steps);
        V3 = v_max  - a * linspace(0,T,steps);

        t0 = tray_s1 / v_tray;
        T1 = linspace(t0,t0 + endEffecotrs_t1,steps);
        T2 = linspace(T1(end),T1(end) + T,steps);
        T3 = linspace(T2(end),T2(end) + T,steps);
        T0  = linspace(0,T3(end),steps);

        plot(T0,V0,T1,V1,T2,V2,T3,V3);
        title('can not reach target v_m_a_x');
    end
else
    v_min = v_tray;

    endEffecotrs_s1 = (v_max - v_min)^2 / (2 * a);

    s = tray_s1;
    s1 = s - 2 * endEffecotrs_s1;

    t0 = s / v_tray;
    if (s1 >= 0)
        if (s1 > 0.001)
            endEffecotrs_t1 = (v_max - v_min) / a;

            endEffecotrs_s2 = s1;
            endEffecotrs_t2 = endEffecotrs_s2 / v_max;

            endEffecotrs_s3 = endEffecotrs_s1;
            endEffecotrs_t3 = endEffecotrs_t1;

            T1 = linspace(t0      , endEffecotrs_t1 + t0      , steps);
            T2 = linspace(T1(end) , T1(end) + endEffecotrs_t2 , steps);
            T3 = linspace(T2(end) , T2(end) + endEffecotrs_t3 , steps);
            T0 = linspace(0,T3(end),steps);

            V1 = v_min + a * linspace(0,endEffecotrs_t1,steps);
            V2 = v_max * ones(1,steps);
            V3 = v_max - a * linspace(0,endEffecotrs_t3,steps);
            V0 = v_tray * ones(1,steps);

            plot(T0,V0,T1,V1,T2,V2,T3,V3);
            title('can reach target v_m_a_x and have uniform velocity');
        else
            endEffecotrs_t1 = (v_max - v_min) / a;

            endEffecotrs_s2 = endEffecotrs_s1;
            endEffecotrs_t2 = endEffecotrs_t1;

            T1 = linspace(t0      , endEffecotrs_t1 + t0      , steps);
            T2 = linspace(T1(end) , T1(end) + endEffecotrs_t2 , steps);
            T0 = linspace(0       , T2(end)                   , steps);

            V1 = v_min + a * linspace(0,endEffecotrs_t1,steps);
            V2 = v_max - a * linspace(0,endEffecotrs_t2,steps);
            V0 = v_tray * ones(1,steps);

            plot(T0,V0,T1,V1,T2,V2);
            title('can reach target v_m_a_x but not have uniform velocity');
        end
    else
        endEffecotrs_s1 = s / 2;
        endEffecotrs_t1 = sqrt((2 * endEffecotrs_s1) / a);

        v_max = v_tray + a * endEffecotrs_t1;

        endEffecotrs_s2 = endEffecotrs_s1;
        endEffecotrs_t2 = endEffecotrs_t1;

        T1 = linspace(t0      , endEffecotrs_t1 + t0      , steps);
        T2 = linspace(T1(end) , T1(end) + endEffecotrs_t2 , steps);
        T0 = linspace(0       , T2(end)                   , steps);

        V1 = v_min + a * linspace(0,endEffecotrs_t1,steps);
        V2 = v_max - a * linspace(0,endEffecotrs_t2,steps);
        V0 = v_tray * ones(1,steps);

        plot(T0,V0,T1,V1,T2,V2);
        title('can not reach target v_m_a_x');
    end
end

axis([0 T0(end) 0 v_max]);
grid on;

