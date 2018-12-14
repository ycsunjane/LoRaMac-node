/*!
 * \file      LmPackage.h
 *
 * \brief     Defines the packages API
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \code
 *                ______                              _
 *               / _____)             _              | |
 *              ( (____  _____ ____ _| |_ _____  ____| |__
 *               \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 *               _____) ) ____| | | || |_| ____( (___| | | |
 *              (______/|_____)_|_|_| \__)_____)\____)_| |_|
 *              (C)2013-2018 Semtech
 *
 * \endcode
 *
 * \author    Miguel Luis ( Semtech )
 */
#ifndef __LMH_PACKAGE_H__
#define __LMH_PACKAGE_H__

#include <stdint.h>
#include <stdbool.h>
#include "LmHandlerTypes.h"

/*!
 * Maximum number of packages
 */
#define PKG_MAX_NUMBER                              4

typedef struct LmhPackage_s
{
    uint8_t Port;
    /*
     *=========================================================================
     * Below callbacks must be initialized in package variable declaration
     *=========================================================================
     */

    /*!
     * Initializes the package with provided parameters
     *
     * \param [IN] params            Pointer to the package parameters
     * \param [IN] dataBuffer        Pointer to main application buffer
     * \param [IN] dataBufferMaxSize Main application buffer maximum size
     */
    void ( *Init )( void *params, uint8_t *dataBuffer, uint8_t dataBufferMaxSize );
    /*!
     * Returns the current package initialization status.
     *
     * \retval status Package initialization status
     *                [true: Initialized, false: Not initialized]
     */
    bool ( *IsInitialized )( void );
    /*!
     * Returns the package operation status.
     *
     * \retval status Package operation status
     *                [true: Running, false: Not running]
     */
    bool ( *IsRunning )( void );
    /*!
     * Processes the internal package events.
     */
    void ( *Process )( void );
    /*!
     * Processes the MCSP Confirm
     *
     * \param [IN] mcpsConfirm MCPS confirmation primitive data
     */
    void ( *OnMcpsConfirmProcess )( McpsConfirm_t *mcpsConfirm );
    /*!
     * Processes the MCPS Indication
     *
     * \param [IN] mcpsIndication     MCPS indication primitive data
     */
    void ( *OnMcpsIndicationProcess )( McpsIndication_t *mcpsIndication );
    /*!
     * Processes the MLME Confirm
     *
     * \param [IN] mlmeConfirm MLME confirmation primitive data
     */
    void ( *OnMlmeConfirmProcess )( MlmeConfirm_t *mlmeConfirm );
    /*!
     * Processes the MLME Indication
     *
     * \param [IN] mlmeIndication     MLME indication primitive data
     */
    void ( *OnMlmeIndicationProcess )( MlmeIndication_t *mlmeIndication );

    /*
     *=========================================================================
     * Below callbacks must be initialized in LmHandler initialization with
     * provideded LmHandlerSend and OnMacRequest functions
     *=========================================================================
     */

    /*!
     * Notifies the upper layer that a MCPS request has been made to the MAC layer
     *
     * \param   [IN] status      - Request returned status
     * \param   [IN] mcpsRequest - Performed MCPS-Request. Refer to \ref McpsReq_t.
     */
    void ( *OnMacMcpsRequest )( LoRaMacStatus_t status, McpsReq_t *mcpsReq );
    /*!
     * Notifies the upper layer that a MLME request has been made to the MAC layer
     *
     * \param   [IN] status      - Request returned status
     * \param   [IN] mlmeRequest - Performed MLME-Request. Refer to \ref MlmeReq_t.
     */
    void ( *OnMacMlmeRequest )( LoRaMacStatus_t status, MlmeReq_t *mlmeReq );
    /*!
     * Instructs the MAC layer to send a ClassA uplink
     *
     * \param [IN] appData Data to be sent
     * \param [IN] isTxConfirmed Indicates if the uplink requires an acknowledgement
     *
     * \retval status Returns \ref LORAMAC_HANDLER_SUCCESS if request has been
     *                processed else \ref LORAMAC_HANDLER_ERROR
     */
    LmHandlerErrorStatus_t ( *OnSendRequest )( LmHandlerAppData_t *appData, LmHandlerMsgTypes_t isTxConfirmed );
}LmhPackage_t;

#endif // __LMH_PACKAGE_H__