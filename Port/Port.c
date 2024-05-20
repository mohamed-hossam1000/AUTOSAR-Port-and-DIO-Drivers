 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mohamed Hossam
 ******************************************************************************/

#include"Port.h"
#include"Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "../Det/Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Port_ConfigPin * Port_Pins = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module.
************************************************************************************/
void Port_Init(const Port_ConfigType* ConfigPtr)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    if(NULL_PTR == ConfigPtr)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
    }
    else
#endif
    {
        uint8 i;
        uint32 GPIOx[NUM_OF_GPIO_PORTS] = {PORTA_BASE_ADDRESS, PORTB_BASE_ADDRESS, PORTC_BASE_ADDRESS, PORTD_BASE_ADDRESS, PORTE_BASE_ADDRESS, PORTF_BASE_ADDRESS};
        uint32 Port_Base_Adrress;
        /* default settings for all Port Pins
         * Digital GPIO pin (no special function)
         * Input with Pull Up
         *  */
        for (i = 0; i < NUM_OF_GPIO_PORTS; i++)
        {
            *((volatile uint32 *)(GPIOx[i] + DIR_OFFSET   )) = 0x00000000;
            *((volatile uint32 *)(GPIOx[i] + AFSEL_OFFSET )) = 0x00000000;
            *((volatile uint32 *)(GPIOx[i] + PUR_OFFSET   )) = 0x00000000;
            *((volatile uint32 *)(GPIOx[i] + PDR_OFFSET   )) = 0x000000FF;
            *((volatile uint32 *)(GPIOx[i] + DEN_OFFSET   )) = 0x000000FF;
            *((volatile uint32 *)(GPIOx[i] + AMSEL_OFFSET )) = 0x00000000;
            *((volatile uint32 *)(GPIOx[i] + DATA_OFFSET  )) = 0x00000000;
        }

        Port_Pins = ConfigPtr->Pins;
        for (i = 0; i < PORT_CONFIGURED_PINS; i++)
        {
            Port_Base_Adrress = GPIOx[Port_Pins[i].Port_Num];

            /* Set The Direction of the Port Pin */
            if (PORT_PIN_OUT == Port_Pins[i].PortPinDirection)
            {
                *((volatile uint32 *)(Port_Base_Adrress + DIR_OFFSET)) |= (1 << Port_Pins[i].Pin_Num);
            }
            else
            {
                *((volatile uint32 *)(Port_Base_Adrress + DIR_OFFSET)) &= ~(1 << Port_Pins[i].Pin_Num);
            }

            /* Set The Initial Level of the Port Pin */
            if (PORT_PIN_LEVEL_HIGH == Port_Pins[i].PortPinLevelValue)
            {
                *((volatile uint32 *)(Port_Base_Adrress + DATA_OFFSET)) |= (1 << Port_Pins[i].Pin_Num);
            }
            else
            {
                *((volatile uint32 *)(Port_Base_Adrress + DATA_OFFSET)) &= ~(1 << Port_Pins[i].Pin_Num);
            }

            /* Configure The Open Drain of the Port Pin */
            if (OPEN_DRAIN == Port_Pins[i].PortPinOpenDrainMode)
            {
                *((volatile uint32 *)(Port_Base_Adrress + ODR_OFFSET)) |= (1 << Port_Pins[i].Pin_Num);
            }
            else
            {
                *((volatile uint32 *)(Port_Base_Adrress + ODR_OFFSET)) &= ~(1 << Port_Pins[i].Pin_Num);
            }

            /* Configure the Internal Resistor */
            if (PORT_INTERNAL_RESISTOR_PULL_UP == Port_Pins[i].PortPinResistorMode)
            {
                *((volatile uint32 *)(Port_Base_Adrress + PUR_OFFSET)) |= (1 << Port_Pins[i].Pin_Num);
            }
            else if (PORT_INTERNAL_RESISTOR_PULL_DOWN == Port_Pins[i].PortPinResistorMode)
            {
                *((volatile uint32 *)(Port_Base_Adrress + PDR_OFFSET)) |= (1 << Port_Pins[i].Pin_Num);
            }
            else
            {
                *((volatile uint32 *)(Port_Base_Adrress + PUR_OFFSET)) &= ~(1 << Port_Pins[i].Pin_Num);
                *((volatile uint32 *)(Port_Base_Adrress + PDR_OFFSET)) &= ~(1 << Port_Pins[i].Pin_Num);
            }

            /* Set The Mode */
            if (PORT_PIN_MODE_ADC == Port_Pins[i].PortPinMode)
            {
                *((volatile uint32 *)(Port_Base_Adrress + AFSEL_OFFSET)) &= ~(1 << Port_Pins[i].Pin_Num);
                /* Set Analog Mode bit */
                *((volatile uint32 *)(Port_Base_Adrress + AMSEL_OFFSET)) |= (1 << Port_Pins[i].Pin_Num);
                /* Clear PCTL register for the Port Pin */
                *((volatile uint32 *)(Port_Base_Adrress + PCTL_OFFSET)) &= ~(0x0F << (Port_Pins[i].Pin_Num << 2));
            }
            else if (PORT_PIN_MODE_DIO == Port_Pins[i].PortPinMode)
            {
                *((volatile uint32 *)(Port_Base_Adrress + AFSEL_OFFSET)) &= ~(1 << Port_Pins[i].Pin_Num);
                /* Set Digital Mode bit */
                *((volatile uint32 *)(Port_Base_Adrress + DEN_OFFSET)) |= (1 << Port_Pins[i].Pin_Num);
                /* Clear PCTL register for the Port Pin */
                *((volatile uint32 *)(Port_Base_Adrress + PCTL_OFFSET)) &= ~(0x0F << (Port_Pins[i].Pin_Num << 2));
            }
            else
            {
                *((volatile uint32 *)(Port_Base_Adrress + AFSEL_OFFSET)) |= (1 << Port_Pins[i].Pin_Num);
                /* Set Digital Mode bit */
                *((volatile uint32 *)(Port_Base_Adrress + DEN_OFFSET)) |= (1 << Port_Pins[i].Pin_Num);
                /* Clear PCTL register for the Port Pin */
                *((volatile uint32 *)(Port_Base_Adrress + PCTL_OFFSET)) &= ~(0x0F << (Port_Pins[i].Pin_Num << 2));
                /* Set PCTL register for the Port Pin to the required mode */
                *((volatile uint32 *)(Port_Base_Adrress + PCTL_OFFSET)) |= (Port_Pins[i].PortPinMode << (Port_Pins[i].Pin_Num << 2));
            }
        }
        Port_Status = PORT_INITIALIZED;
    }
}

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin - Port Pin ID number
*                  Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction.
************************************************************************************/
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
    boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if (PORT_NOT_INITIALIZED == Port_Status)
    {
        /* Send DET Error */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /*Do Nothing*/
    }
    /* Check if the used Pin is initialized */
    if (PORT_CONFIGURED_PINS <= Pin)
    {
        /* Send DET Error */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
        error = TRUE;
    }
    else
    {
        /*Do Nothing*/
    }
    /* Check if the used pin is allowed to change direction in run time */
    if (STD_ON != Port_Pins[Pin].PortPinDirectionChangeable)
    {
        /* Send DET Error */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE);
        error = TRUE;
    }
    else
    {
        /*Do Nothing*/
    }
#endif
    if (FALSE == error)
    {
        /* Change the Direction of the required pin */
        switch (Port_Pins[Pin].Port_Num)
        {
        case PORTA:
            GPIO_PORTA_DIR_REG = (GPIO_PORTA_DIR_REG & ~(1 << Port_Pins[Pin].Pin_Num)) | ((Direction & 0x01) << Port_Pins[Pin].Pin_Num);
            break;
        case PORTB:
            GPIO_PORTB_DIR_REG = (GPIO_PORTB_DIR_REG & ~(1 << Port_Pins[Pin].Pin_Num)) | ((Direction & 0x01) << Port_Pins[Pin].Pin_Num);
            break;
        case PORTC:
            GPIO_PORTC_DIR_REG = (GPIO_PORTC_DIR_REG & ~(1 << Port_Pins[Pin].Pin_Num)) | ((Direction & 0x01) << Port_Pins[Pin].Pin_Num);
            break;
        case PORTD:
            GPIO_PORTD_DIR_REG = (GPIO_PORTD_DIR_REG & ~(1 << Port_Pins[Pin].Pin_Num)) | ((Direction & 0x01) << Port_Pins[Pin].Pin_Num);
            break;
        case PORTE:
            GPIO_PORTE_DIR_REG = (GPIO_PORTE_DIR_REG & ~(1 << Port_Pins[Pin].Pin_Num)) | ((Direction & 0x01) << Port_Pins[Pin].Pin_Num);
            break;
        case PORTF:
            GPIO_PORTF_DIR_REG = (GPIO_PORTF_DIR_REG & ~(1 << Port_Pins[Pin].Pin_Num)) | ((Direction & 0x01) << Port_Pins[Pin].Pin_Num);
            break;
        default:
            break;
        }
    }
}
#endif

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
************************************************************************************/
void Port_RefreshPortDirection(void)
{
    uint8 i;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if (PORT_NOT_INITIALIZED == Port_Status)
    {
        /* Send DET Error */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
    }
    else
#endif
    {
        for (i = 0; i < PORT_CONFIGURED_PINS; i++)
        {
            /* Refresh the Direction of all Port Pins that are not changeable during runtime */
            if (FALSE == Port_Pins[i].PortPinDirectionChangeable)
            {
                switch (Port_Pins[i].Port_Num)
                {
                case PORTA:
                    GPIO_PORTA_DIR_REG = (GPIO_PORTA_DIR_REG & ~(1 << Port_Pins[i].Pin_Num)) | (Port_Pins[i].PortPinDirection << Port_Pins[i].Pin_Num);
                    break;
                case PORTB:
                    GPIO_PORTB_DIR_REG = (GPIO_PORTB_DIR_REG & ~(1 << Port_Pins[i].Pin_Num)) | (Port_Pins[i].PortPinDirection << Port_Pins[i].Pin_Num);
                    break;
                case PORTC:
                    GPIO_PORTC_DIR_REG = (GPIO_PORTC_DIR_REG & ~(1 << Port_Pins[i].Pin_Num)) | (Port_Pins[i].PortPinDirection << Port_Pins[i].Pin_Num);
                    break;
                case PORTD:
                    GPIO_PORTD_DIR_REG = (GPIO_PORTD_DIR_REG & ~(1 << Port_Pins[i].Pin_Num)) | (Port_Pins[i].PortPinDirection << Port_Pins[i].Pin_Num);
                    break;
                case PORTE:
                    GPIO_PORTE_DIR_REG = (GPIO_PORTE_DIR_REG & ~(1 << Port_Pins[i].Pin_Num)) | (Port_Pins[i].PortPinDirection << Port_Pins[i].Pin_Num);
                    break;
                case PORTF:
                    GPIO_PORTF_DIR_REG = (GPIO_PORTF_DIR_REG & ~(1 << Port_Pins[i].Pin_Num)) | (Port_Pins[i].PortPinDirection << Port_Pins[i].Pin_Num);
                    break;
                default:
                    break;
                }
            }
        }
    }
}

#if (PORT_VERSION_INFO_API == STD_ON)
/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Returns the version information of this module.
************************************************************************************/
void Port_GetVersionInfo(Std_VersionInfoType * versioninfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == versioninfo)
    {
        /* Send DET Error */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
    }
    else
#endif
    {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16)PORT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
}
#endif

#if (PORT_SET_PIN_MODE_API == STD_ON)
/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin - Port Pin ID number
*                  Mode - New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
************************************************************************************/
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
    boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if (PORT_NOT_INITIALIZED == Port_Status)
    {
        /* Send DET Error */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /*Do Nothing*/
    }
    /* Check if the used Pin is initialized */
    if (PORT_CONFIGURED_PINS <= Pin)
    {
        /* Send DET Error */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
        error = TRUE;
    }
    else
    {
        /*Do Nothing*/
    }
    /* Check if the used pin is allowed to change direction in run time */
    if (STD_ON != Port_Pins[Pin].PortPinModeChangeable)
    {
        /* Send DET Error */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
        error = TRUE;
    }
    else
    {
        /*Do Nothing*/
    }
    /*  Check if the mode i Valid */
    if ((Mode > PORT_PIN_MODE_AF15) || ((Mode > PORT_PIN_MODE_ADC) && (Mode < PORT_PIN_MODE_AF14)))
    {
        /* Send DET Error */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
        error = TRUE;
    }
    else
    {
        /*Do Nothing*/
    }
#endif
    if (FALSE == error)
    {
        uint32 Port_Base_Adrress;
        switch (Port_Pins[Pin].Port_Num)
        {
            case PORTA:
                Port_Base_Adrress = PORTA_BASE_ADDRESS;
                break;
            case PORTB:
                Port_Base_Adrress = PORTB_BASE_ADDRESS;
                break;
            case PORTC:
                Port_Base_Adrress = PORTC_BASE_ADDRESS;
                break;
            case PORTD:
                Port_Base_Adrress = PORTD_BASE_ADDRESS;
                break;
            case PORTE:
                Port_Base_Adrress = PORTE_BASE_ADDRESS;
                break;
            case PORTF:
                Port_Base_Adrress = PORTF_BASE_ADDRESS;
                break;
            default:
                break;
        }
        /* Set The Mode */
        if (PORT_PIN_MODE_ADC == Mode)
        {
            *((volatile uint32 *)(Port_Base_Adrress + AFSEL_OFFSET)) &= ~(1 << Port_Pins[Pin].Pin_Num);
            /* Set Analog Mode bit */
            *((volatile uint32 *)(Port_Base_Adrress + AMSEL_OFFSET)) |= (1 << Port_Pins[Pin].Pin_Num);
            /* Clear PCTL register for the Port Pin */
            *((volatile uint32 *)(Port_Base_Adrress + PCTL_OFFSET)) &= ~(0x0F << (Port_Pins[Pin].Pin_Num << 2));
        }
        else if (PORT_PIN_MODE_DIO == Mode)
        {
            *((volatile uint32 *)(Port_Base_Adrress + AFSEL_OFFSET)) &= ~(1 << Port_Pins[Pin].Pin_Num);
            /* Set Digital Mode bit */
            *((volatile uint32 *)(Port_Base_Adrress + DEN_OFFSET)) |= (1 << Port_Pins[Pin].Pin_Num);
            /* Clear PCTL register for the Port Pin */
            *((volatile uint32 *)(Port_Base_Adrress + PCTL_OFFSET)) &= ~(0x0F << (Port_Pins[Pin].Pin_Num << 2));
        }
        else
        {
            *((volatile uint32 *)(Port_Base_Adrress + AFSEL_OFFSET)) |= (1 << Port_Pins[Pin].Pin_Num);
            /* Set Digital Mode bit */
            *((volatile uint32 *)(Port_Base_Adrress + DEN_OFFSET)) |= (1 << Port_Pins[Pin].Pin_Num);
            /* Clear PCTL register for the Port Pin */
            *((volatile uint32 *)(Port_Base_Adrress + PCTL_OFFSET)) &= ~(0x0F << (Port_Pins[Pin].Pin_Num << 2));
            /* Set PCTL register for the Port Pin to the required mode */
            *((volatile uint32 *)(Port_Base_Adrress + PCTL_OFFSET)) |= (Mode << (Port_Pins[Pin].Pin_Num << 2));
        }
    }
}
#endif
