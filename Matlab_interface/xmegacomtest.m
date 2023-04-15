clearvars;
close all;

N = 128;
COM = 'COM12';

xmega = serialport(COM,115200,'Timeout',10);
flush(xmega);

while 1
    
    write(xmega, 1, "uint8");                                                    %Send start sign
    
    while xmega.NumBytesAvailable < (N*4)
        %Do nothing 
    end

    spectrum = read(xmega, N, "single");                                        %Read spectrum
    checksum = read(xmega, 1, "single");                                        %Read checksum
    stem(spectrum);                                                             %Plot spectrum
    drawnow
end