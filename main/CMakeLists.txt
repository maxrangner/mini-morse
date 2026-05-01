idf_component_register(
    SRCS "main.cpp" "app_controller/app_controller.cpp" "morse_decoder/morse_decoder.cpp"
    INCLUDE_DIRS "." "app_controller" "morse_decoder"
    REQUIRES button_driver
    )
