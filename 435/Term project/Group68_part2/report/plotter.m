x=[0.5,10,20];
y=[198.1, 507.4, 761.6];
e=[1.338582, 1.715098, 1.926876];

errorbar(x,y,e);
xlabel('Packet Loss Percentage');
ylabel('File Transfer Time(s)');
title('Packet Loss Percentage vs File Transfer Time');
print('graph1.png')
pause;



x=[0.2,10,20];
y=[193.1, 473.5, 854.4];
e=[0.900326, 1.24264, 1.625036];

errorbar(x,y,e);
xlabel('Corruption Percentage');
ylabel('File Transfer Time(s)');
title('Corruption Percentage vs File Transfer Time');
print('graph2.png')
pause;



x=[1,10,35];
y=[142.6, 143.3, 143.9];
e=[0.796217, 0.872461, 0.94276];

errorbar(x,y,e);
xlabel('Reordering Percentage');
ylabel('File Transfer Time(s)');
title('Reordering Percentage vs File Transfer Time');
print('graph3.png')
pause;

