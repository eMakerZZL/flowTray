function [center,radius] = ThreePointsDetermineCircle3D(p1,p2,p3)
    handle = figure;
    L12 = p2 - p1;
    L13 = p3 - p1;
    
    k1 = L13(1) / L12(1);
    k2 = L13(2) / L12(2);
    k3 = L13(3) / L12(3);
    
    if (k1 == k2 && k1 == k3)
       error('three points in one line\r\n');
    end
    
    n = cross(L12,L13);
    n = n / norm(n);
    
    if (max(n) == 1)
        sprintf('2D circle\r\n')
        pause();
    end

    n12 = cross(n,L12);
    n13 = cross(n,L13);

    C12 = (p1 + p2) ./ 2;
    C13 = (p1 + p3) ./ 2;
    
    draw_point = @(n,style) plot3(n(1),n(2),n(3),style);
    draw_point(p1,'ro');
    hold on;
    draw_point(p2,'ro');
    draw_point(p3,'ro');
    draw_point(C12,'go');
    draw_point(C13,'go');

    A = [n12(1) -n13(1);n12(2) -n13(2)];
    B = [C13(1)-C12(1); C13(2)-C12(2)];
    
    X = A \ B;
    
    t = X(1);
    x = C12(1) + t * n12(1);
    y = C12(2) + t * n12(2);
    z = C12(3) + t * n12(3);
    center = [x y z];
    draw_point(center, 'mo');
    
    r = sqrt(sum((p1 - center).^2));
    radius = r;

    alpha = linspace(0, 2*pi, 1000);
    a = p1 - center;
    b = cross(a, n);
    a = a / norm(a);
    b = b / norm(b);

    point_x = x + r * cos(alpha) * a(1) + r * sin(alpha) * b(1);
    point_y = y + r * cos(alpha) * a(2) + r * sin(alpha) * b(2);
    point_z = z + r * cos(alpha) * a(3) + r * sin(alpha) * b(3);

    plot3(point_x,point_y,point_z);
    
    axis equal;

    h = 0.2;
    k = (2*r - h) * h;
    l = 2 * k;
    delta_radian = asin(l / (2 * r));
    beta = 0 : delta_radian : 2 * pi;
    if (beta(end) ~= 2 * pi)
        beta = [beta 2*pi];
    end

    point_x1 = x + r * cos(beta) * a(1) + r * sin(beta) * b(1);
    point_y1 = y + r * cos(beta) * a(2) + r * sin(beta) * b(2);
    point_z1 = z + r * cos(beta) * a(3) + r * sin(beta) * b(3);
    
    axis equal;

    break_line_handle = plot3(point_x1(1),point_y1(1),point_z1(1),'ro');
    
    for i = 2 : length(point_x1)
        set(break_line_handle,'xdata',point_x1(i),'ydata',point_y1(i),'zdata',point_z1(i));
        pause(0.1);
    end
end        
