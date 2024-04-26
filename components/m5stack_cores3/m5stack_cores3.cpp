#include "esphome/core/log.h"
#include "m5stack_cores3.h"

namespace esphome {
namespace m5stack_cores3 {

static const char *TAG = "m5stack_cores3";

void M5StackCoreS3::setup() {
    ESP_LOGI(TAG, "M5Stack CoreS3 setup");
    M5.begin();

    // RTC BM8563 Init (clear INT)
    M5.In_I2C.writeRegister8(bm8563_addr, 0x00, 0x00, 100000L);
    M5.In_I2C.writeRegister8(bm8563_addr, 0x01, 0x00, 100000L);
    M5.In_I2C.writeRegister8(bm8563_addr, 0x0D, 0x00, 100000L);

    // Power on BUS for sensors
    M5.In_I2C.bitOff(aw9523_addr, 0x02, 0b100000, 100000L); // USB OTG EN
    if (this->bus_out_) {
        ESP_LOGI(TAG, "Enable Power on BUS");
        M5.In_I2C.bitOn(aw9523_addr, 0x02, 0b000010, 100000L);
    } else {
        ESP_LOGI(TAG, "Disable Power on BUS");
        M5.In_I2C.bitOff(aw9523_addr, 0x02, 0b000010, 100000L);
    }
    M5.In_I2C.bitOn(aw9523_addr, 0x03, 0b10000000, 100000L);  // BOOST_EN

    // Set initial brightness
    M5.Display.setBrightness(this->lcd_brightness_);
    if (this->lcd_brightness_ > 0) {
        this->lcd_initial_brightness_ = this->lcd_brightness_;
        this->lcd_on_ = true;
    }
}

void M5StackCoreS3::loop() {
}

void M5StackCoreS3::dump_config(){
    ESP_LOGCONFIG(TAG, "M5Stack CoreS3");
    ESP_LOGCONFIG(TAG, "  Power BUS: %s", YESNO(this->bus_out_));
    ESP_LOGCONFIG(TAG, "  LCD Brightness: %d", this->lcd_brightness_);
}

void M5StackCoreS3::toggle_lcd() {
    if (this->lcd_on_) {
        M5.Display.setBrightness(0);
    } else {
        M5.Display.setBrightness(this->lcd_initial_brightness_);
    }
    this->lcd_on_ = ! this->lcd_on_;
}

void M5StackCoreS3::lcd_on() {
    M5.Display.setBrightness(this->lcd_initial_brightness_);
    this->lcd_on_ = true;
}

void M5StackCoreS3::lcd_off() {
    M5.Display.setBrightness(0);
    this->lcd_on_ = false;
}

}  // namespace m5stack_cores3
}  // namespace esphome