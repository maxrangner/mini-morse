idf_component_register(
    SRCS "main.cpp" "app_controller/app_controller.cpp" 
    INCLUDE_DIRS "." "app_controller"
    REQUIRES button_driver
    )
