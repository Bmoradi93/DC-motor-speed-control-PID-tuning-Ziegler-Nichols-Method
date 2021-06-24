clc; clear all; close all
V = dlmread('capture.txt');
for i = 1:1:size(V)
   inp(i) = 5;
end
inp = inp';

figure;
plot(V, 'LineWidth', 2);
title('DC Motor Output Speed');
ylabel('Output Shaft Speed(Rotation/Sec)');
xlabel('Time(ms)')

figure;
plot(inp, 'LineWidth', 2);
title('DC Motor Voltage');