 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mohamed Hossam
 ******************************************************************************/

#ifndef PORT_PORT_H_
#define PORT_PORT_H_

/* Id for the company in the AUTOSAR
 * for example Mohamed Hossam's ID = 1000 :) */
#define PORT_VENDOR_ID    (1000U)

/* PORT Module Id */
#define PORT_MODULE_ID    (124U)

/* PORT Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for PORT Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

#include"../Common/Std_Types.h"
/* AUTOSAR Version checking between Std_Types.h and Port.h files */
#if ((PORT_AR_RELEASE_MAJOR_VERSION != STD_TYPES_AR_RELEASE_MAJOR_VERSION)\
   ||(PORT_AR_RELEASE_MINOR_VERSION != STD_TYPES_AR_RELEASE_MINOR_VERSION)\
   ||(PORT_AR_RELEASE_PATCH_VERSION != STD_TYPES_AR_RELEASE_PATCH_VERSION))
    #error "The AR version of Port_Types.h does not match the expected version"
#endif


#include"Port_Cfg.h"
/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_AR_RELEASE_MAJOR_VERSION != PORT_CFG_AR_RELEASE_MAJOR_VERSION)\
   ||(PORT_AR_RELEASE_MINOR_VERSION != PORT_CFG_AR_RELEASE_MINOR_VERSION)\
   ||(PORT_AR_RELEASE_PATCH_VERSION != PORT_CFG_AR_RELEASE_PATCH_VERSION))
    #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_SW_MAJOR_VERSION != PORT_CFG_SW_MAJOR_VERSION)\
   ||(PORT_SW_MINOR_VERSION != PORT_CFG_SW_MINOR_VERSION)\
   ||(PORT_SW_PATCH_VERSION != PORT_CFG_SW_PATCH_VERSION))
    #error "The SW version of Port_Cfg.h does not match the expected version"
#endif


#include"Port_Types.h"
/* AUTOSAR Version checking between Port_Types.h and Port.h files */
#if ((PORT_AR_RELEASE_MAJOR_VERSION != PORT_TYPES_AR_RELEASE_MAJOR_VERSION)\
  ||(PORT_AR_RELEASE_MINOR_VERSION != PORT_TYPES_AR_RELEASE_MINOR_VERSION)\
  ||(PORT_AR_RELEASE_PATCH_VERSION != PORT_TYPES_AR_RELEASE_PATCH_VERSION))
    #error "The AR version of Port_Types.h does not match the expected version"
#endif

/* Software Version checking between Port_Types.h and Port.h files */
#if ((PORT_SW_MAJOR_VERSION != PORT_TYPES_SW_MAJOR_VERSION)\
   ||(PORT_SW_MINOR_VERSION != PORT_TYPES_SW_MINOR_VERSION)\
   ||(PORT_SW_PATCH_VERSION != PORT_TYPES_SW_PATCH_VERSION))
    #error "The SW version of Port_Types.h does not match the expected version"
#endif

/******************************************************************************
 *                          API Service Id Macros                             *
 ******************************************************************************/
/* Service ID for Port Init */
#define PORT_INIT_SID                               0x00

/* Service ID for Port Set Pin Directopn */
#define PORT_SET_PIN_DIRECTION_SID                  0x01

/* Service ID for Port Refresh Port Direction */
#define PORT_REFRESH_PORT_DIRECTION_SID             0x02

/* Service ID for Port Get Version Info */
#define PORT_GET_VERSION_INFO_SID                   0x03

/* Service ID for Port Set Pin Mode */
#define PORT_SET_PIN_MODE_SID                       0x04

/*******************************************************************************
 *                              DET Error Codes                                *
 *******************************************************************************/
/* Invalid Port Pin ID requested  */
#define PORT_E_PARAM_PIN                        0x0A
/* Port Pin not configured as changeable  */
#define PORT_E_DIRECTION_UNCHANGEABLE           0x0B
/* API Port_Init service called with wrong parameter */
#define PORT_E_PARAM_CONFIG                     0x0C
/* API Port_SetPinMode service called with wrong parameter */
#define PORT_E_PARAM_INVALID_MODE               0x0D
/* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE                0x0E
/* API service called without module initialization  */
#define PORT_E_UNINIT                           0x0F
/* APIs called with a Null Pointer  */
#define PORT_E_PARAM_POINTER                    0x10

/*******************************************************************************
 *                              Port Names Macros                                *
 *******************************************************************************/
#define PORTA                                   (0U)
#define PORTB                                   (1U)
#define PORTC                                   (2U)
#define PORTD                                   (3U)
#define PORTE                                   (4U)
#define PORTF                                   (5U)

#define NUM_OF_GPIO_PORTS                       (6U)

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/
/* Function that Initializes the Port Driver module */
void Port_Init(
    const Port_ConfigType* ConfigPtr
);

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/* Function that Sets the port pin direction */
void Port_SetPinDirection(
    Port_PinType Pin,
    Port_PinDirectionType Direction
) ;
#endif

/* Function that Refreshes port direction */
void Port_RefreshPortDirection(
    void
);

#if (PORT_VERSION_INFO_API == STD_ON)
/* Function that Returns the version information of this module */
void Port_GetVersionInfo(
    Std_VersionInfoType* versioninfo
);
#endif

#if (PORT_SET_PIN_MODE_API == STD_ON)
/* Function that Sets the port pin mode */
void Port_SetPinMode(
    Port_PinType Pin,
    Port_PinModeType Mode
);
#endif

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern Link time structures to be used by Port and other modules */
extern const Port_ConfigType Port_Configuration;

#endif /* PORT_PORT_H_ */
