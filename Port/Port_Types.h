 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Types.h
 *
 * Description: Data Types Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mohamed Hossam
 ******************************************************************************/


#ifndef PORT_PORT_TYPES_H_
#define PORT_PORT_TYPES_H_

/*
 * Module Version 1.0.0
 */
#define PORT_TYPES_SW_MAJOR_VERSION              (1U)
#define PORT_TYPES_SW_MINOR_VERSION              (0U)
#define PORT_TYPES_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_TYPES_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_TYPES_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_TYPES_AR_RELEASE_PATCH_VERSION     (3U)

#include"../Common/Std_Types.h"
/* AUTOSAR Version checking between Std_Types.h and Port.h files */
#if ((PORT_TYPES_AR_RELEASE_MAJOR_VERSION != STD_TYPES_AR_RELEASE_MAJOR_VERSION)\
   ||(PORT_TYPES_AR_RELEASE_MINOR_VERSION != STD_TYPES_AR_RELEASE_MINOR_VERSION)\
   ||(PORT_TYPES_AR_RELEASE_PATCH_VERSION != STD_TYPES_AR_RELEASE_PATCH_VERSION))
    #error "The AR version of Port_Types.h does not match the expected version"
#endif

/*******************************************************************************
 *                                 Definitions                                 *
 *******************************************************************************/
/* Values of Port Pins Level */
#define PORT_PIN_LEVEL_HIGH                     STD_HIGH
#define PORT_PIN_LEVEL_LOW                      STD_LOW

/* Port Pins Modes */
#define PORT_PIN_MODE_DIO                       0x00
#define PORT_PIN_MODE_AF1                       0x01
#define PORT_PIN_MODE_AF2                       0x02
#define PORT_PIN_MODE_AF3                       0x03
#define PORT_PIN_MODE_AF4                       0x04
#define PORT_PIN_MODE_AF5                       0x05
#define PORT_PIN_MODE_AF6                       0x06
#define PORT_PIN_MODE_AF7                       0x07
#define PORT_PIN_MODE_AF8                       0x08
#define PORT_PIN_MODE_AF9                       0x09
#define PORT_PIN_MODE_ADC                       0x0A
#define PORT_PIN_MODE_AF14                      0x0E
#define PORT_PIN_MODE_AF15                      0x0F

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
/* Type definition for Port_PinType used by the Port APIs */
typedef uint8 Port_PinType;

/* Type definition for Port_PinDirectionType used by the Port APIs */
typedef enum{
    PORT_PIN_IN = 0, PORT_PIN_OUT = 1
}Port_PinDirectionType;

/* Type definition for Port_PinModeType used by the Port APIs */
typedef uint8 Port_PinModeType;

/* Enum to hold internal resistor type for PIN */
typedef enum
{
    PORT_INTERNAL_RESISTOR_OFF = 0, PORT_INTERNAL_RESISTOR_PULL_UP = 1, PORT_INTERNAL_RESISTOR_PULL_DOWN = 2
}Port_InternalResistor;

/* Enum to hold internal resistor type for PIN */
typedef enum
{
    PUSH_PULL = 0, OPEN_DRAIN = 1
}Port_OpenDrain;

/* Data Structure For pin Configuration */
typedef struct{
    /* Member contains the ID of the Port that this Port Pin belongs to */
    uint8 Port_Num;
    /* Member contains the ID of the Port Pin */
    Port_PinType Pin_Num;
    /* Member contains the Direction of the Port Pin */
    Port_PinDirectionType PortPinDirection;
    /* Member to indicate if the direction is changeable on a port pin during runtime */
    boolean PortPinDirectionChangeable;
    /* Member contains the Level of the Port Pin */
    uint8 PortPinLevelValue;
    /* Member contains the Mode of the Port Pin */
    Port_PinModeType PortPinMode;
    /* Member to indicate if the mode is changeable on a port pin during runtime */
    boolean PortPinModeChangeable;
    /* Member to indicate if the Pull Up or Pull down resistor is used */
    Port_InternalResistor PortPinResistorMode;
    /* Member to indicate if the Open drain mode is used */
    Port_OpenDrain  PortPinOpenDrainMode;
}Port_ConfigPin;

/* Data Structure required for initializing the Port Driver */
typedef struct{
    Port_ConfigPin Pins[PORT_CONFIGURED_PINS];
}Port_ConfigType;



#endif /* PORT_PORT_TYPES_H_ */
