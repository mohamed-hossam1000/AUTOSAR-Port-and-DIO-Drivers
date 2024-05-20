 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Lcfg.c
 *
 * Description: Link Time Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mohamed Hossam
 ******************************************************************************/

/*
 * Module Version 1.0.0
 */
#define PORT_LCFG_SW_MAJOR_VERSION              (1U)
#define PORT_LCFG_SW_MINOR_VERSION              (0U)
#define PORT_LCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_LCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_LCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_LCFG_AR_RELEASE_PATCH_VERSION     (3U)

#include"Port.h"

/* AUTOSAR Version checking between Port_Lcfg.h and Port.h files */
#if ((PORT_AR_RELEASE_MAJOR_VERSION != PORT_LCFG_AR_RELEASE_MAJOR_VERSION)\
   ||(PORT_AR_RELEASE_MINOR_VERSION != PORT_LCFG_AR_RELEASE_MINOR_VERSION)\
   ||(PORT_AR_RELEASE_PATCH_VERSION != PORT_LCFG_AR_RELEASE_PATCH_VERSION))
    #error "The AR version of Port_Lcfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Lcfg.h and Port.h files */
#if ((PORT_SW_MAJOR_VERSION != PORT_LCFG_SW_MAJOR_VERSION)\
   ||(PORT_SW_MINOR_VERSION != PORT_LCFG_SW_MINOR_VERSION)\
   ||(PORT_SW_PATCH_VERSION != PORT_LCFG_SW_PATCH_VERSION))
    #error "The SW version of Port_Lcfg.h does not match the expected version"
#endif

const Port_ConfigType Port_Configuration = {
                                                PortConf_LED1_PORT_NUM, PortConf_LED1_PIN_NUM, PortConf_LED1_DIRECTION, PortConf_LED1_DIRECTION_CHANGEABLE,
                                                PortConf_LED1_LEVEL, PortConf_LED1_MODE, PortConf_LED1_MODE_CHANGEABLE, PortConf_LED1_INTERNAL_RESISTOR,
                                                PortConf_LED1_OPEN_DRAIN,

                                                PortConf_SW1_PORT_NUM, PortConf_SW1_PIN_NUM, PortConf_SW1_DIRECTION, PortConf_SW1_DIRECTION_CHANGEABLE,
                                                PortConf_SW1_LEVEL, PortConf_SW1_MODE, PortConf_SW1_MODE_CHANGEABLE, PortConf_SW1_INTERNAL_RESISTOR,
                                                PortConf_SW1_OPEN_DRAIN
                                            };
