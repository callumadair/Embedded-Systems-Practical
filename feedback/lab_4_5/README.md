# Feedback

Overall marks: 100.0/100  (100.0%)

## Lab4: Task1
Excellent work, your ALU is performing the correct operation for all the input op codes, well done. The Verilog is also neatly laid out and well formatted.  

mark = 25.0/25




## Lab4: Task2
Great job adding the working register, your ALU passes all the tests. Also, the implementation looks really good, it's great the way that you separated out the sequential components and the combinatorial, nice work. The only minor issue is that toseq is assigned in a combinatorial block, but it's value is not assigned for every possible output. I'm happy to sign this off but just wanted to make you aware of it.  

mark = 25.0/25




## Lab5: Task1
The implementation of the setup is good. I think however, setting the enable bit needs to happen after the setting of divval and the increment bits. Sorry, this was confusing how I wrote the comments in the code. Excellent work with the read function implementation. 

mark = 25.0/25




## Lab5: Task2
The 64-bit counter is implemented well, excellent work checking the config register bits to determine if the timer has been enabled and using the increment bit to either increment or decrement. I did have a bit of trouble getting your code to simulate, I needed to increase the number of bits for divval, but it worked fine after that.  Nice work implementing the load logic. When the LOAD address is written to the loadlo_reg and loadhi_reg will be written into the timer. I think the reason that you were getting a large timer value when the simulation ran and not the correct one, is because you were not writing 0's to the loadlo reg and loadhi reg in the sw_driver.h. So a random value was being loaded into them.  Great job implementing the update register and loading the timer values into hi_reg and lo_reg.  The prescalar counter is implemented perfectly, awesome! Nice implementation, this was a tricky lab and you made a really excellent implementation here, thanks for the good submission! While there was a slight issue with the loadlo and loadhi reg in the sw_driver which meant that you couldn't get quite the right output, I am more than happy to sign this off. Well done.  

mark = 25.0/25




