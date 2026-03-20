#pragma once
/**
 * OpenKNX Hardware Configuration Header File
 *
 * Defines hardware properties for various reusable OpenKNX hardware modules and
 * includes hardware definition headers for various OpenKNX modules.
 *
 * Note: This file should only contain include directives for hardware configuration headers.
 *       No hardware configurations should be made directly in this file.
 *
 * Naming Conventions for OpenKNX Hardware Definitions:
 *     1. to be defined.
 *
 * Naming Conventions for "OpenKNX Ready" 3rd Party Hardware Definitions:
 *     1. to be defined.
 */

/**
 * Include hardware definition headers:
 *
 */

// OpenKNX Hardware Configurations
#include "HardwareConfig/OpenKNX/REG1.h"
#include "HardwareConfig/OpenKNX/REG2.h"
#include "HardwareConfig/OpenKNX/UP1.h"
#include "HardwareConfig/OpenKNX/Xiao.h"
#include "HardwareConfig/OpenKNX/misc.h"

// OpenKNX Ready Hardware Configurations
//  #include "HardwareConfig/OpenKNX-Ready/AB-SmartHouse/xyz.h"
#include "HardwareConfig/OpenKNX-Ready/Smart-MF/Devices.h"

// Other 3rd Party Hardware Configurations
//  #include "HardwareConfig/Others/XYZ-Hardware.h"
#include "HardwareConfig/Others/Adafruit.h"
