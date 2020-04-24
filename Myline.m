clc;
clear;
hold on

x = 1;
y = 2;

start_point = [0;0];
end_point   = [2;5];

line_start = [start_point(x) end_point(x)];
line_end =   [start_point(y) end_point(y)];
plot(line_start,line_end);

delta_x = end_point(x) - start_point(x);
delta_y = end_point(y) - start_point(y);
distance = sqrt(delta_x^2 + delta_y^2);

k = delta_y / delta_x;

unit_length = 0.7;
line_segment = floor(distance / unit_length);
last_line_length = distance - line_segment * unit_length;

target_Point = zeros(1,2);

Insert_Point= start_point;
Insert_Line = start_point';

for i = 1 : 1 : line_segment
    target_Point(x) = unit_length * i;
    target_Point(y) = target_Point(x) * k;

     if (k == Inf) 
         Insert_Point(y) = Insert_Point(y) + unit_length;
         Insert_Line = [Insert_Line;Insert_Point'];
         continue;
     end

     if (k == 0)
         Insert_Point(x) = Insert_Point(x) + unit_length;
         Insert_Line = [Insert_Line;Insert_Point'];
         continue;
     end

     if (target_Point(x) > 0 && target_Point(y) > 0)
         if (k > 0 && k < 1)
             epsilon_single_axis = Insert_Point(y) - target_Point(y);
             epsilon_double_axis = Insert_Point(y) - target_Point(y) + unit_length;
             res = epsilon_single_axis + epsilon_double_axis;
             if(res > 0)
                 Insert_Point(x) = Insert_Point(x) + unit_length;
             else
                 Insert_Point(x) = Insert_Point(x) + unit_length;
                 Insert_Point(y) = Insert_Point(y) + unit_length;
             end
         else
             epsilon_single_axis = Insert_Point(x) - target_Point(x);
             epsilon_double_axis = Insert_Point(x) - target_Point(x) + unit_length;
             res = epsilon_single_axis + epsilon_double_axis;
             if(res > 0)
                 Insert_Point(y) = Insert_Point(y) + unit_length;
             else
                 Insert_Point(x) = Insert_Point(x) + unit_length;
                 Insert_Point(y) = Insert_Point(y) + unit_length;
             end
         end
            if(Insert_Point(x) > end_point(x) || Insert_Point(y) > end_point(y)) break
            end
    end

    if (target_Point(x) < 0 && target_Point(y) > 0)
        if (k < -1)
             epsilon_single_axis = Insert_Point(x) - target_Point(x);
             epsilon_double_axis = Insert_Point(x) - target_Point(x) - unit_length;
             res = epsilon_single_axis + epsilon_double_axis;
             if(res > 0)
                 Insert_Point(x) = Insert_Point(x) - unit_length;
                 Insert_Point(y) = Insert_Point(y) + unit_length;
             else
                 Insert_Point(y) = Insert_Point(y) + unit_length;
             end
        else
             epsilon_single_axis = Insert_Point(y) - target_Point(y);
             epsilon_double_axis = Insert_Point(y) - target_Point(y) + unit_length;
             res = epsilon_single_axis + epsilon_double_axis;
             if(res > 0)
                 Insert_Point(x) = Insert_Point(x) - unit_length;
             else
                 Insert_Point(x) = Insert_Point(x) - unit_length;
                 Insert_Point(y) = Insert_Point(y) + unit_length;
             end
        end
    end

    Insert_Line = [Insert_Line;Insert_Point'];
end

plot(Insert_Line(:,1),Insert_Line(:,2),'r');
