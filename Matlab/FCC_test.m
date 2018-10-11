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
if BdID ~= 10 && BdID ~= 11 && BdID ~= 13
  error('Expected BdID 10 or 11, reported %d', BdID);
end
Build = read_subbus(s,2);
fprintf(1, 'Attached to FCC %d Build # %d\n', BdID, Build);
%%
% Connect DAC 0 out to ADC 0 in
%  J2.A8 FLSET0 to J2.A2 FLOW0
%  J2.A12 or A5 (anagnd) to J2.A11 (FLOW0_RTN)
% A is the top connector. Pin 1 is in the upper right
test_dac_adc_loopback(s, 25, 0, 0, 0);
%%
test_dac_adc_loopback(s, 25, 1, 1, 0);
%%
test_dac_adc_loopback(s, 25, 2, 2, 0);
%%
test_dac_adc_loopback(s, 25, 3, 3, 0);
%%
% write_subbus(s, 24, 34); % Switch to single-ended 
test_dac_adc_loopback(s, 25, 0, 1, 1);
%%
% write_subbus(s, 24, 34); % Switch to single-ended negative lead
test_dac_adc_loopback(s, 25, 0, 1, 1, 0);


%% Test Commands
%
% Channel 0-3
% Mode 0: both off
%      1: Closed on
%      2: Open on
%      3: Open and closed on, but only for channel 3
channel = 3;
mode = 0;
write_subbus(s, 24, channel*4+mode);
