 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mohamed Hossam
 ******************************************************************************/

#ifndef PORT_PORT_CFG_H_
#define PORT_PORT_CFG_H_

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

#define PORT_CONFIGURED_PINS                  (2U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                 (STD_ON)

/* Pre-compile option for presence of Set Pin Direction API */
#define PORT_SET_PIN_DIRECTION_API            (STD_ON)

/* Pre-compile option for presence of Set Pin Mode API */
#define PORT_SET_PIN_MODE_API                 (STD_ON)

/* Pre-compile option for presence of Version Info API */
#define PORT_VERSION_INFO_API                 (STD_ON)

/* Pin Index in the array of structures in Port_Lcfg.c */
#define PortConf_LED1_PIN_ID_INDEX        (uint8)0x00
#define PortConf_SW1_PIN_ID_INDEX         (uint8)0x01

/* Port driver Configured Ports ID's  */
#define PortConf_LED1_PORT_NUM                (uint8)5 /* PORTF */
#define PortConf_SW1_PORT_NUM                 (uint8)5 /* PORTF */

/* Port driver Configured Port Pins ID's */
#define PortConf_LED1_PIN_NUM                 (Port_PinType)1 /* Pin 1 in PORTF */
#define PortConf_SW1_PIN_NUM                  (Port_PinType)4 /* Pin 4 in PORTF */

/* Port driver Configured Port Pins Directions */
#define PortConf_LED1_DIRECTION               PORT_PIN_OUT
#define PortConf_SW1_DIRECTION                PORT_PIN_IN

/* Port driver Configured Port Pins Directions Changeability */
#define PortConf_LED1_DIRECTION_CHANGEABLE    STD_OFF
#define PortConf_SW1_DIRECTION_CHANGEABLE     STD_OFF

/* Port driver Configured Port Pins Initial Level */
#define PortConf_LED1_LEVEL                   PORT_PIN_LEVEL_LOW
#define PortConf_SW1_LEVEL                    PORT_PIN_LEVEL_LOW

/* Port driver Configured Port Pins Mode */
#define PortConf_LED1_MODE                    PORT_PIN_MODE_DIO
#define PortConf_SW1_MODE                     PORT_PIN_MODE_DIO

/* Port driver Configured Port Pins Mode Changeability */
#define PortConf_LED1_MODE_CHANGEABLE         STD_OFF
#define PortConf_SW1_MODE_CHANGEABLE          STD_OFF

/* Port driver Configured Port Pins Internal Resistor */
#define PortConf_LED1_INTERNAL_RESISTOR       PORT_INTERNAL_RESISTOR_OFF
#define PortConf_SW1_INTERNAL_RESISTOR        PORT_INTERNAL_RESISTOR_PULL_UP

/* Port driver Configured Port Pins Open Drain */
#define PortConf_LED1_OPEN_DRAIN              PUSH_PULL
#define PortConf_SW1_OPEN_DRAIN               PUSH_PULL


#endif /* PORT_PORT_CFG_H_ */
