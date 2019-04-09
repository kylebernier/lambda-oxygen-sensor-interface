clear;
clc;
clf;
%% Verification for PWM voltages
% Spec is 0 to 12Vrms +- 200mV
fid = fopen("RMS_DATA.txt");
PWM = textscan(fid,"%f,%f", 'HeaderLines', 1);
fclose(fid);
ref_voltages = PWM{:,1};
measured_voltages = PWM{:,2};

figure(1);
scatter(ref_voltages, measured_voltages, 12, 'o', 'b');
%scatter(ref_voltages, ref_voltages, 'x', 'm');
line([0 12], [0 12], 'Color', 'magenta');
line([0 12], [0.2 12.2], 'Color', 'red','LineStyle','-.');
line([0 12], [-0.2 11.8], 'Color', 'red','LineStyle','-.');
xlabel("Desired Voltage (V_{RMS})");
ylabel("Measured Voltage (V_{RMS})");
xlim([0 12]);
ylim([-0.2 12.2]);
yticks([0:1:12]);
xticks([0:1:12]);
set(gca,'FontSize',18);
legend("Measured Voltages", "Desired Voltage", "Specification Bounds", 'Location', 'northwest');
grid on;

%% Verification of Temperature output
fid = fopen("2019-03-14T16_38_19.396608");
UART = textscan(fid, "(%d, %d, %d)","HeaderLines", 224);
t = 0:1254;

figure(2);
plot(t/5, UART{:, 2});
yline(780+39, '--r');
yline(780-39, '--r');
xlabel("Time (s)");
ylabel("Temperature (C)");
ylim([740 820]);
xlim([0 length(t)/5]);
xticks([0:30:length(t)/5]);
set(gca,'FontSize',18);
legend("Temperature of Sensor", "Specification Bounds");
grid on;

%% Verification of DAC Spec
data = csvread("PureLambda.csv", 1068, 0);
desired = linspace(0.65, 1.36, 4966);
lambda = data(:,2);

figure(3);
plot(desired, lambda(1:6034-1068));
line([0.65 1.36],[0.65 1.36], 'Color', 'magenta');
line([0.65 1.36],[0.7 1.41], 'Color', 'red', 'LineStyle', '-.');
line([0.65 1.36],[0.6 1.31], 'Color', 'red', 'LineStyle', '-.');
xlim([0.65 1.36]);
set(gca,'FontSize',18);
xlabel("Desired Lambda (λ)");
ylabel("Actual Lambda (λ)");
legend("Measure Lambda", "Desired Lambda", "Error Bounds", 'Location', 'northwest');
grid on;