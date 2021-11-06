unsigned int *gpio_enable_reg = (unsigned int*)(0x3FF44020);
unsigned int *gpio_enable1_reg = (unsigned int*)(0x3FF4402C);

unsigned int gpio_initial_values;
unsigned int gpio_new_values;

unsigned int gpio_initial_values1;
unsigned int gpio_new_values1;

// W1TS GPIO register
unsigned int*gpio_w1ts_reg = (unsigned int*)(0x3FF44008);
unsigned int*gpio_w1ts_reg1 = (unsigned int*)(0x3FF44014);

// W1TC GPIO register
unsigned int*gpio_w1tc_reg = (unsigned int*)(0x3FF4400C);
unsigned int*gpio_w1tc_reg1 = (unsigned int*)(0x3FF44018);

void setup() {
    gpio_initial_values = *gpio_enable_reg; 
    gpio_new_values = gpio_initial_values | (1 << 18) | (1 << 5) | (1 << 22) | (1 << 21);
    *gpio_enable_reg = gpio_new_values;

    gpio_initial_values1 = *gpio_enable1_reg; 
    gpio_new_values1 = gpio_initial_values1 | (1 << 0) | (1 << 1);
    *gpio_enable1_reg = gpio_new_values1;
}

void loop() {
    *gpio_w1ts_reg = (1 << 18) | (1 << 5) | (1 << 22) | (1 << 21);
    *gpio_w1tc_reg = (1 << 18) | (1 << 5) | (1 << 22) | (1 << 21);

    *gpio_w1ts_reg1 = (1 << 0) | (1 << 1);
    *gpio_w1tc_reg1 = (1 << 0) | (1 << 1);
}
