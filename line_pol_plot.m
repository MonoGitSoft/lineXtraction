clear all
clc
D = importdata('p_data.txt');
raw_D = importdata('p_raw_data.txt');
r = D(1:end,1);
alfa = D(1:end,2);
figure;
polar(0,600)
hold on
polar(raw_D(1:end,2),raw_D(1:end,1),'.');
figure;
polar(0,600)
hold on
r_temp = r(1:2);
alfa_temp = alfa(1:2);
polar(alfa_temp,r_temp)
for i =3:2:length(r) - 1,
    r_temp = r(i:i + 1)
    alfa_temp = alfa(i:i + 1)
    polar(alfa_temp,r_temp)
end
