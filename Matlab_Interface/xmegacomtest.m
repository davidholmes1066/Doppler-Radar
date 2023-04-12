clearvars;
close all;
xmega = serialport('COM12',115200,'Timeout',10);

%write(xmega, 10, "uint8");
test = read(xmega, 32, "uint16");
stem(test)