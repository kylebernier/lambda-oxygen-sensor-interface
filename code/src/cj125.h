/**
 * @file cj125.h
 * @author Kyle Bernier
 * @author Daeghan Elkin
 * @brief Definitons for the CJ125 registers
 * @date 2018-11-27
 * 
 */

/**
 * @defgroup CJ125 CJ125 Register definitions
 * @{
 */

/** @brief Register value for identification request */
#define CJ125_IDENT_REG         0x4800
/** @brief Register value for diagnostic request */
#define CJ125_DIAG_REG          0x7800
/** @brief Diagnostic response from CJ125: Ready */
#define CJ125_DIAG_REG_OK       0x28ff
/** @brief Diagnostic response from CJ125: No/Low power */
#define CJ125_DIAG_REG_NOPWR    0x2855
/** @brief Diagnostic response from CJ125: No sensor */
#define CJ125_DIAG_REG_NOSNSR   0x287f
/** @brief Register value for setting CJ125 into calibration mode */
#define CJ125_CALIBRATE_MODE    0x569d
/** @brief Register value for setting CJ125 into V=8 mode */
#define CJ125_V8_MODE           0x5688
/** @brief Register value for setting CJ125 into V=17 mode */
#define CJ125_V17_MODE          0x5689
/** @} */ 