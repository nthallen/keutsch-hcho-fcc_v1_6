%%
cd C:\Users\nort.ARP\Documents\Exp\HCHO\FCC_V1_6\Matlab
%%
serial_port_clear();
%%
[s,port] = serial_port_init();
%set(s,'BaudRate',57600);
set(s,'BaudRate',115200);
%%
% First check that the board is an FCC
BdID = read_subbus(s, 3);
if BdID ~= 10
  error('Expected BdID 10, reported %d', BdID);
end
Build = read_subbus(s,2);
fprintf(1, 'Attached to FCC Build # %d\n', Build);
%%
test_dac_adc_loopback(s, 25, 0, 1, 0);
%%
% write_subbus(s, 24, 34); % Switch to single-ended 
test_dac_adc_loopback(s, 25, 0, 1, 1);