function [x0,y0,r] = ThreePointsDetermineCircle(p1,p2,p3)
    k1 = (p1.x - p2.x) / (p1.y - p2.y);
    k2 = (p1.x - p3.x) / (p1.y - p3.y);
    if (k1 ~= k2)
         a = p1.x - p2.x;
         b = p1.y - p2.y;
         c = p1.x - p3.x;
         d = p1.y - p3.y;
         e = ((p1.x^2 - p2.x^2) - (p2.y^2 - p1.y^2)) / 2;
         f = ((p1.x^2 - p3.x^2) - (p3.y^2 - p1.y^2)) / 2;
        x0 = - (d * e - b * f) / (b * c - a * d);
        y0 = - (a * f - c * e) / (b * c - a * d);
         r = sqrt((p1.x - x0)^2 + (p1.y - y0)^2);
    end
end
