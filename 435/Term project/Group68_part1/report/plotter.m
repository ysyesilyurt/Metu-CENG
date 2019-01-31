x=[0,1,20,60];
y=[222.853660583, 231.452915668, 260.553383827, 346.436054707];
e=[0.101962889366996, 0.9407839472138799, 1.3780723067818, 1.24405544556972];

errorbar(x,y,e);
xlabel('Emulated Delay(ms)/+-5ms');
ylabel('End-to-End Delay(ms)');
title('Emulated Delay vs End-to-End Delay');
print('graph.png')
pause;
