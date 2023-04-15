clearvars;
close all;

N = 128;
COM = 'COM12';

xmega = serialport(COM,115200,'Timeout',10);
flush(xmega);

write(xmega, 1, "uint8");                                                    %Send start sign

spectrum = read(xmega, N, "single");                                         %Read spectrum
checksum = read(xmega, 1, "single");

stem(spectrum)                                                               %Plot spectrum