clearvars;
close all;

N = 512;
C = 2.99705E+8;
F0 = 24.125E+9;
fb = (-N/2):1:((N/2)-1);
COM = 'COM9';

xmega = serialport(COM,115200,'Timeout',10);
flush(xmega);

i = 1;

while 1
    
    write(xmega, 2, "uint8");                                                    %Send start sign
    
    %Function for reading doppler speed
%     while xmega.NumBytesAvailable < ((2*4)+4)
%         Do nothing 
%     end
% 
%     mag = read(xmega, 1, "single");
%     speed(i) = read(xmega, 1, "single");
%     checksum = read(xmega, 1, "single");
%     stem(speed);
%     writematrix(speed(i),'speedTest1.csv','WriteMode','append');



    %Function for reading spectrum
    while xmega.NumBytesAvailable < ((N*4)+(3*4))                                   %Do nothing till data is ready
    end
    
    spectrum = read(xmega, N, "single");                                        %Read data
    mag = read(xmega, 1, "single");
    speed(i) = read(xmega, 1, "single");
    checksum = read(xmega,1,"single");
    
    
    Vp(i) = (2*mag*2.06)./(N*pi*4096);%Read spectrum
    
    if(i == 1)
        nexttile;
        s = stem(fb, spectrum);                                                    %Plot spectrum
        title('FFT spectrum');
        xlabel('frequency bin');
        ylabel('magnitude');
    
        nexttile;
        v = semilogy(Vp);
        grid on;
        ylabel('Peak voltage in V');
        xlabel('FFT sample number');
        title('Vp no added gain');

        nexttile;
        sp = plot(speed);
        grid on;
        ylabel('Speed in kph');
        xlabel('FFT sample number');
        title('Boat speed');
    end

    v.YData = Vp;                                                           %Update plot data
    s.YData = spectrum;
    sp.YData = speed;

%    writematrix(spectrum,'test.csv','WriteMode','append');


    i = i + 1;
    drawnow;
end