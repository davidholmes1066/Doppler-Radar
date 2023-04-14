clearvars;
close all;

N = 512;
COM = 'COM12';

xmega = serialport(COM,115200,'Timeout',10);
flush(xmega);

write(xmega, 1, "uint8");                                                   %Send start sign

spectrum = read(xmega, N*2, "single");                                      %Read spectrum

stem(spectrum)                                                              %Plot spectrum