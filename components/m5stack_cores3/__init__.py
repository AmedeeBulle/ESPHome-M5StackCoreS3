"""M5Stack Core S3 component."""

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.core import CORE
from esphome.const import CONF_ID


def AUTO_LOAD():
    if CORE.is_esp32:
        return ["psram"]
    return []


CODEOWNERS = ["@amedeebulle"]

m5stack_cores3_ns = cg.esphome_ns.namespace("m5stack_cores3")
M5StackCoreS3 = m5stack_cores3_ns.class_("M5StackCoreS3", cg.Component)

CONF_BUS_OUT = "bus_out"
CONF_LCD_BRIGHTNESS = "lcd_brightness"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(M5StackCoreS3),
        cv.Optional(CONF_BUS_OUT, default=True): cv.boolean,
        cv.Optional(CONF_LCD_BRIGHTNESS, default=90): cv.int_,
    }
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    cg.add(var.set_bus_out(config[CONF_BUS_OUT]))
    cg.add(var.set_lcd_brightness(config[CONF_LCD_BRIGHTNESS]))
