set(PROJECT_BUNDLE io.macchina.tf)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_LIST_DIR}/Tf.bndlspec)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io Tinkerforge Bindings"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR IoT::Tf::BundleActivator
        #LAZY_START
        RUN_LEVEL 610
        DEPENDENCIES io.macchina.devices:1.0.0-2.0.0
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                   src/MasterConnection.cpp
                   src/MasterConnectionImpl.cpp
                   src/TemperatureSensor.cpp
                   src/HumiditySensor.cpp
                   src/AmbientLightSensor.cpp
                   src/AirPressureSensor.cpp
                   src/RotaryEncoder.cpp
                   src/MotionDetector.cpp
                   src/GNSSSensor.cpp
                   src/DCMotor.cpp
                   src/BundleActivator.cpp
                   src/brick_dc.c
                   src/brick_imu.c
                   src/brick_master.c
                   src/brick_servo.c
                   src/brick_stepper.c
                   src/bricklet_ambient_light.c
                   src/bricklet_analog_in.c
                   src/bricklet_analog_out.c
                   src/bricklet_barometer.c
                   src/bricklet_current12.c
                   src/bricklet_current25.c
                   src/bricklet_distance_ir.c
                   src/bricklet_distance_us.c
                   src/bricklet_dual_button.c
                   src/bricklet_dual_relay.c
                   src/bricklet_gps.c
                   src/bricklet_hall_effect.c
                   src/bricklet_humidity.c
                   src/bricklet_industrial_digital_in_4.c
                   src/bricklet_industrial_digital_out_4.c
                   src/bricklet_industrial_dual_0_20ma.c
                   src/bricklet_industrial_quad_relay.c
                   src/bricklet_io16.c
                   src/bricklet_io4.c
                   src/bricklet_joystick.c
                   src/bricklet_lcd_16x2.c
                   src/bricklet_lcd_20x4.c
                   src/bricklet_led_strip.c
                   src/bricklet_line.c
                   src/bricklet_linear_poti.c
                   src/bricklet_moisture.c
                   src/bricklet_motion_detector.c
                   src/bricklet_multi_touch.c
                   src/bricklet_piezo_buzzer.c
                   src/bricklet_piezo_speaker.c
                   src/bricklet_ptc.c
                   src/bricklet_remote_switch.c
                   src/bricklet_rotary_encoder.c
                   src/bricklet_rotary_poti.c
                   src/bricklet_segment_display_4x7.c
                   src/bricklet_sound_intensity.c
                   src/bricklet_temperature.c
                   src/bricklet_temperature_ir.c
                   src/bricklet_tilt.c
                   src/bricklet_voltage.c
                   src/bricklet_voltage_current.c
                   src/ip_connection.c
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPIoTDevices
                   Poco::RemotingNG
                   Poco::OSP
                   Poco::Util
                   Poco::XML
                   Poco::Foundation
                 DEFINITIONS IoTTf_EXPORTS
                 )