clear;
clc;
clf;

t=0:1000;
temp=4445*t.^(-0.4449)+428.6;
figure(1);
loglog(t, temp);
grid on;

