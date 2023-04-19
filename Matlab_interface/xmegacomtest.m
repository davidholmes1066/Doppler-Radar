clearvars;
close all;

N = 512;
COM = 'COM12';

xmega = serialport(COM,115200,'Timeout',10);
flush(xmega);

write(xmega, 1, "uint8");                                                       %Write cal state
checksum = read(xmega, 1, "single");                                            %Get checksum from device

while 1
    
    write(xmega, 2, "uint8");                                                    %Send start sign
    
    while xmega.NumBytesAvailable < (N*4)
        %Do nothing 
    end

    spectrum = read(xmega, N, "single");                                        %Read spectrum
    checksum = read(xmega, 1, "single");                                        %Read checksum
    stem(spectrum);                                                             %Plot spectrum
    ylim([0, 1E+5])
    drawnow
end