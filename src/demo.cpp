#include "stm32-template.h"

#include "i2c/i2c.h"

#include "st7920/st7920-dm.h"
#include "dot-matrix/dot-matrix.h"
#include "dot-matrix/dot-char.h"
#include "dot-matrix/dot-font.h"
#include "dot-matrix/dot-string.h"

Gpio led_green(GPIOC, GPIO_Pin_9, RCC_APB2Periph_GPIOC);
Gpio led_blue(GPIOC, GPIO_Pin_8, RCC_APB2Periph_GPIOC);

Gpio st7920_rs(GPIOC, GPIO_Pin_12, RCC_APB2Periph_GPIOC);
Gpio st7920_en(GPIOC, GPIO_Pin_11, RCC_APB2Periph_GPIOC);
Gpio st7920_d4(GPIOC, GPIO_Pin_10, RCC_APB2Periph_GPIOC);
Gpio st7920_d5(GPIOA, GPIO_Pin_15, RCC_APB2Periph_GPIOA);
Gpio st7920_d6(GPIOA, GPIO_Pin_14, RCC_APB2Periph_GPIOA);
Gpio st7920_d7(GPIOA, GPIO_Pin_13, RCC_APB2Periph_GPIOA);

Gpio i2c_scl(GPIOB, GPIO_Pin_6, RCC_APB2Periph_GPIOB);
Gpio i2c_sda(GPIOB, GPIO_Pin_7, RCC_APB2Periph_GPIOB);
I2c i2c(I2C1, RCC_APB1Periph_I2C1);

St7920Dm lcd(st7920_rs, st7920_en, st7920_d4, st7920_d5, st7920_d6, st7920_d7);
DotMatrix dm = lcd.getDotMatrix();

DotChar dc(dm, vfont_7x3);
DotString ds(dc, 16, false);

const char* titles[] = { "        -     +", "ADXL345:", "X:", "Y:", "Z:", "",
		"ITG3200:", "X:", "Y:", "Z:", "", "HMC5883:", "X:", "Y:", "Z:" };

void display();

void setup() {

	led_green.init(GPIO_Mode_Out_PP);
	led_blue.init(GPIO_Mode_Out_PP);

	i2c_scl.init(GPIO_Mode_AF_OD);
	i2c_sda.init(GPIO_Mode_AF_OD);

	i2c.init(I2C_Mode_I2C, 400000);
	i2c.setReg(0x53, 0x2d, 0x08); // 345
	i2c.setReg(0x53, 0x2c, 0x09); // 345

	i2c.setReg(0x1e, 0x00, 0x70); // 3886
	i2c.setReg(0x1e, 0x01, 0x20); // 3886
	i2c.setReg(0x1e, 0x02, 0x00); // 3886

	i2c.setReg(0x68, 0x3e, 0x00); // 3200
	i2c.setReg(0x68, 0x15, 19);   // 3200
	i2c.setReg(0x68, 0x16, 0x1e); // 3200
	i2c.setReg(0x68, 0x17, 0x00); // 3200

	nvic.configure(TIM2_IRQn, 0, 3, ENABLE);
	Tim t2(TIM2, RCC_APB1Periph_TIM2, RCC_APB1PeriphClockCmd);
	t2.init(1000, 1000);
	t2.configureIT(TIM_IT_Update);
	t2.setState();

	lcd.init();
	dc.setVertical(false);
}

void loop() {
	static uint8_t i = 0;
	while (usart.available()) {
		char c = usart.read();
		fprintf(stdout, "0x%02X\r\n", c);
		led_blue.toggle();
	}

	fprintf(stdout, "0x%02x\r\n", i++);

	display();
}

void showData(int16_t *val, uint8_t row, uint8_t shift_right) {
	static const uint8_t mid = 18;
	for (uint8_t i = 0; i < 3; i++) {
		ds.printf("%04X", (uint16_t) val[i]);
		uint8_t r = row + 8 * i;
		ds.postAt(8, r);
		dm.setLine(r + 1, 18, r + 6, 18);
		dm.setRect(r + 4, mid, r + 5, mid - (val[i] >> shift_right));
	}
}

void display() {

	dm.clear();
	uint8_t data[6];
	int16_t val[3];

	for (uint8_t i = 0; i < 15; i++) {
		uint8_t j = 8 * i;
		ds.printf(titles[i]);
		ds.postAt(0, j);
		//dm.setLine(j + 1, 18,  j + 6, 18);
	}

	i2c.getReg(0x53, 0x32, data, 6);
	for (uint8_t i = 0; i < 3; i++)
		val[i] = make16(data[i + i + 1], data[i + i]);
	showData(val, 16, 4);

	i2c.getReg(0x68, 0x1d, data, 6);
	for (uint8_t i = 0; i < 3; i++)
		val[i] = make16(data[i + i], data[i + i + 1]);
	showData(val, 56, 8);

	i2c.getReg(0x1e, 0x03, data, 6);
	for (uint8_t i = 0; i < 3; i++)
		val[i] = make16(data[i + i], data[i + i + 1]);

	int16_t temp = val[1];
	val[1] = val[2];
	val[2] = temp;

	showData(val, 96, 5);

	lcd.putDM();

}
