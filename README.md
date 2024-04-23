# ESPHome M5Stack CoreS3

Simple project to run [ESPHome](https://esphome.io/) on an [M5Stack CoreS3](https://docs.m5stack.com/en/core/CoreS3) device.

This is inspired from [M5CoreS3-Esphome](https://github.com/m5stack/M5CoreS3-Esphome) and [ESPHome - M5-Stack Core S3](https://github.com/gnumpi/esphome_m5stack_core_s3)

The main challenge is to get I2C working properly -- I haven't been able to expose more than one IC2 bus in ESPHome which limits the interactions with the I2C sensors: either you expose the internal bus, but you can't use any external sensor; or you expose Port A or B, and can't address any internal sensor...

For this project I have chosen to expose one of the external ports and use components for the internal bus (e.g. the touchscreen)

It is based on the `esp-idf` framework to be able to use MQTTS which is not supported by the `arduino` framework.

Sample [device configuration file](./example/m5stack_envIII_mqtt.yaml).
