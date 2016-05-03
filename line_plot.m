clear all
clc
D = importdata('data.txt');
x = D(1:end,1);
y = D(1:end,2);

figure;
subplot(2,1,1);
scatter(x,y);
title('Raw data');
subplot(2,1,2);
D = importdata('r_data.txt');
x = D(1:end,1);
y = D(1:end,2);
scatter(x,y);
title('Result');
print('hello','-djpeg');


