clc
clear all

start_angle = 0;
end_angle = pi / 2;
x0 = 0;
y0 = 0;
r = 5;
theta = start_angle : pi / 180 : end_angle;
x1 = x0 + r * cos(theta);
y1 = y0 + r * sin(theta);
plot(x1,y1);
axis equal;
hold on;

h = 0.5;
k = sqrt((2 * r - h) * h);
l = end_angle - start_angle;
segments = floor(l * r / 2 * k);
theta_per_segment = asin(k * 2 / (2 * r));

lines = zeros(segments,2);
lines(1,1) = x0 + r * cos(start_angle);
lines(1,2) = y0 + r * sin(start_angle);
for i = 1 : segments
    x = x0 + r * cos(theta_per_segment * i);
    y = y0 + r * sin(theta_per_segment * i);
    lines (i + 1,1) = x;
    lines (i + 1,2) = y;
end
lines(segments + 2,1) = x0 + r * cos(end_angle);
lines(segments + 2,2) = y0 + r * sin(end_angle);

plot(lines(:,1),lines(:,2),'-ro');
% 
% step_unit = 0.1;
% [row,column] = size(lines);
% insert_line = [0 0];
% for i = 2 : row
%     line_start = lines(i - 1,:);
%     line_end = lines(i,:);
% 
%     delta_x = line_end(1) - line_start(1);
%     delta_y = line_end(2) - line_start(2);
%     totle_count = abs(delta_x / step_unit) + abs(delta_y / step_unit);
% 
%     f = 0;
%     step_coord = line_start;
%     for j = 1 : totle_count
%         f = step_coord(1) * (line_end(2)) - (line_end(1)) * step_coord(2);
%         if f >= 0
%             if delta_x >= 0  
%                 step_coord(1) = step_coord(1) + step_unit;
%             else 
%                 step_coord(1) = step_coord(1) - step_unit;
%             end
%             f = f + (line_end(2));
%         else
%             if delta_y >= 0
%                 step_coord(2) = step_coord(2) + step_unit;
%             else 
%                 step_coord(2) = step_coord(2) - step_unit;
%             end
%             f = f - (line_end(1));
%         end
%         insert_line = [insert_line;step_coord];
%     end
% end
% plot(insert_line(:,1),insert_line(:,2),'-g');
