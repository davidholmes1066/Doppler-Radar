clearvars;
close all;

N = 512;
fb = (-N/2):1:((N/2)-1);
COM = 'COM9';

xmega = serialport(COM,115200,'Timeout',10);
flush(xmega);

i = 1;

%write(xmega, 1, "uint8");                                                       %Write cal state
%checksum = read(xmega, 1, "single");                                            %Get checksum from device

while 1
    
    write(xmega, 2, "uint8");                                                    %Send start sign
    
    while xmega.NumBytesAvailable < (2*4)
        %Do nothing 
    end

    %spectrum = read(xmega, N, "single");                                        %Read spectrum
    speed(i) = read(xmega, 1, "single");
    checksum = read(xmega, 1, "single");                                        %Read checksum
    
    stem(speed);
    %stem(fb, spectrum);                                                             %Plot spectrum
    %writematrix(spectrum,'test.csv','WriteMode','append');
    i = i + 1;
    %ylim([0, 1E+5])
    drawnow
end