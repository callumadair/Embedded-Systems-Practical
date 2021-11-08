# Feedback

Overall marks: 10/10  (100.00%)

## Lab 1
Excellent, it looks like your secret word, baud rate and pin were all correct. Nice work. 



## Lab 2
Nice work interacting with your dotDevice in Task1. Great job interacting with the dotDevices internal command memory. Also, it's great that you were able to configure the onboard timer. Good exploration of the tradeoffs between sending individual commands via the WiFi and using the dotDevice's internal command memory. 



## Lab 3
Nice work with the code for Task1, however, your value is slightly lower than I would have expected. I think this is because in pulseview you are not setting your sample rate high enough. I would expect the output to be between 2-3MHz, which means that your sample rate of 1MHz is not high enough. I would recommend setting the sample rate to the maximum that the logic analyser can support which is 24MHz. Same issue for Task2, the code looks good but the sample rate of the logic analyser is too low.  And Task3, code's good, sample rate is too low.  Code for Task 4 looks almost completely correct, however, all the registers are only 32 bits, so performing a shift like (1 << 32) will shift the value out of range. This is why there is a second set of registers where bit 0 maps to GPIO 32, bit 1 maps to GPIO 33, etc... 

Excellent work correcting the lab submission.

