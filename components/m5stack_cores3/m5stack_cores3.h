#pragma once

#include <M5Unified.h>
#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include <stdint.h>

namespace esphome {
namespace m5stack_cores3 {

class M5StackCoreS3 : public Component {
public:
    void setup() override;
    void loop() override;
    void dump_config() override;
    float get_setup_priority() const override { return setup_priority::BUS + 499.0f; }
    void set_bus_out(bool flag) { this->bus_out_ = flag; }
    void set_lcd_brightness(uint8_t value) { this->lcd_brightness_ = value; }
    void toggle_lcd();
    void lcd_on();
    void lcd_off();

protected:
    bool bus_out_{true};
    bool display_on_{false};
    uint8_t lcd_brightness_{0};
    uint8_t lcd_initial_brightness_{90};
    bool lcd_on_{false};
};

// I2C addresses
const uint8_t bm8563_addr = 0x51;
const uint8_t aw9523_addr = 0x58;

}  // namespace m5stack_cores3
}  // namespace esphome