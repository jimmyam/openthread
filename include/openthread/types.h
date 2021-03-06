/*
 *  Copyright (c) 2016, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief
 *  This file defines the types and structures used in the OpenThread library API.
 */

#ifndef OPENTHREAD_TYPES_H_
#define OPENTHREAD_TYPES_H_

#include <stdint.h>
#include <stdbool.h>
#ifdef OTDLL
#include <guiddef.h>
#endif

#include "openthread/platform/toolchain.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#pragma warning(disable:4214)  // nonstandard extension used: bit field types other than int
#ifdef _KERNEL_MODE
#include <ntdef.h>
#else
#include <windows.h>
#endif
#else
#ifndef CONTAINING_RECORD
/*#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winvalid-offsetof"
#define CONTAINING_RECORD(address, type, field) \
    ((type *)((uint8_t*)(address) - offsetof(type, field)))
#pragma GCC diagnostic pop*/
#define BASE 0x1
#define myoffsetof(s,m) (((size_t)&(((s*)BASE)->m))-BASE)
#define CONTAINING_RECORD(address, type, field) \
    ((type *)((uint8_t*)(address) - myoffsetof(type, field)))
#endif /* CONTAINING_RECORD */
#endif /* _WIN32 */

/**
 * This type represents the OpenThread instance structure.
 */
typedef struct otInstance otInstance;

#ifdef OTDLL

/**
 * This type represents the handle to the OpenThread API.
 */
typedef struct otApiInstance otApiInstance;

/**
 * This type represents a list of device GUIDs.
 */
typedef struct otDeviceList
{
    uint16_t aDevicesLength;
    GUID     aDevices[1];
} otDeviceList;

#endif

/**
 * This enumeration represents error codes used throughout OpenThread.
 */
typedef enum ThreadError
{
    kThreadError_None = 0,
    kThreadError_Failed = 1,
    kThreadError_Drop = 2,
    kThreadError_NoBufs = 3,
    kThreadError_NoRoute = 4,
    kThreadError_Busy = 5,
    kThreadError_Parse = 6,
    kThreadError_InvalidArgs = 7,
    kThreadError_Security = 8,
    kThreadError_AddressQuery = 9,
    kThreadError_NoAddress = 10,
    kThreadError_NotReceiving = 11,
    kThreadError_Abort = 12,
    kThreadError_NotImplemented = 13,
    kThreadError_InvalidState = 14,
    kThreadError_NoTasklets = 15,

    /**
     * No acknowledgment was received after macMaxFrameRetries (IEEE 802.15.4-2006).
     */
    kThreadError_NoAck = 16,

    /**
     * A transmission could not take place due to activity on the channel, i.e., the CSMA-CA mechanism has failed
     * (IEEE 802.15.4-2006).
     */
    kThreadError_ChannelAccessFailure = 17,

    /**
     * Not currently attached to a Thread Partition.
     */
    kThreadError_Detached = 18,

    /**
     * FCS check failure while receiving.
     */
    kThreadError_FcsErr = 19,

    /**
     * No frame received.
     */
    kThreadError_NoFrameReceived = 20,

    /**
     * Received a frame from an unknown neighbor.
     */
    kThreadError_UnknownNeighbor = 21,

    /**
     * Received a frame from an invalid source address.
     */
    kThreadError_InvalidSourceAddress = 22,

    /**
     * Received a frame filtered by the whitelist.
     */
    kThreadError_WhitelistFiltered = 23,

    /**
     * Received a frame filtered by the destination address check.
     */
    kThreadError_DestinationAddressFiltered = 24,

    /**
     * The requested item could not be found.
     */
    kThreadError_NotFound = 25,

    /**
     * The operation is already in progress.
     */
    kThreadError_Already = 26,

    /**
     * Received a frame filtered by the blacklist.
     */
    kThreadError_BlacklistFiltered = 27,

    /**
     * The creation of IPv6 address failed.
     */
    kThreadError_Ipv6AddressCreationFailure = 28,

    /**
     * Operation prevented by mode flags
     */
    kThreadError_NotCapable = 29,

    /**
     * Coap response or acknowledgment or DNS response not received.
     */
    kThreadError_ResponseTimeout = 30,

    /**
     * Received a duplicated frame.
     */
    kThreadError_Duplicated = 31,
    kThreadError_Error = 255,
} ThreadError;

#define OT_IP6_IID_SIZE            8   ///< Size of an IPv6 Interface Identifier (bytes)

#define OT_MASTER_KEY_SIZE         16  ///< Size of the Thread Master Key (bytes)

#define OT_NETWORK_DIAGNOSTIC_TYPELIST_TYPE   18  ///< Concatenated List of Type Identifiers of Other Diagnostics TLVs Used to Request or Reset Multiple Diagnostic Values
#define OT_NETWORK_DIAGNOSTIC_TYPELIST_MAX_ENTRIES   18  ///< Maximum Number of Other Network Diagnostic TLV Types

/**
 * This structure represents a Thread Master Key.
 *
 */
typedef struct otMasterKey
{
    uint8_t m8[OT_MASTER_KEY_SIZE];
} otMasterKey;

#define OT_NETWORK_NAME_MAX_SIZE   16  ///< Maximum size of the Thread Network Name field (bytes)

/**
 * This structure represents a Network Name.
 *
 */
typedef struct otNetworkName
{
    char m8[OT_NETWORK_NAME_MAX_SIZE + 1];
} otNetworkName;

#define OT_EXT_PAN_ID_SIZE         8   ///< Size of a Thread PAN ID (bytes)

/**
 * This structure represents an Extended PAN ID.
 *
 */
typedef struct otExtendedPanId
{
    uint8_t m8[OT_EXT_PAN_ID_SIZE];
} otExtendedPanId;

#define OT_MESH_LOCAL_PREFIX_SIZE  8  ///< Size of the Mesh Local Prefix (bytes)

/**
 * This structure represents a Mesh Local Prefix.
 *
 */
typedef struct otMeshLocalPrefix
{
    uint8_t m8[OT_MESH_LOCAL_PREFIX_SIZE];
} otMeshLocalPrefix;

#define OT_PSKC_MAX_SIZE                             16  ///< Maximum size of the PSKc (bytes)

#define OT_COMMISSIONING_PASSPHRASE_MIN_SIZE         6   ///< Minimum size of the Commissioning Passphrase
#define OT_COMMISSIONING_PASSPHRASE_MAX_SIZE         255 ///< Maximum size of the Commissioning Passphrase

/**
  * This structure represents PSKc.
  *
  */
typedef struct otPSKc
{
    uint8_t m8[OT_PSKC_MAX_SIZE];
} otPSKc;

/**
  * This structure represent Security Policy.
  *
  */
typedef struct otSecurityPolicy
{
    uint16_t mRotationTime;
    uint8_t mFlags;
} otSecurityPolicy;

/**
 * This enumeration defines the Security Policy TLV flags.
 *
 */
enum
{
    OT_SECURITY_POLICY_OBTAIN_MASTER_KEY      = 1 << 7,  ///< Obtaining the Master Key
    OT_SECURITY_POLICY_NATIVE_COMMISSIONING   = 1 << 6,  ///< Native Commissioning
    OT_SECURITY_POLICY_ROUTERS                = 1 << 5,  ///< Routers enabled
    OT_SECURITY_POLICY_EXTERNAL_COMMISSIONER  = 1 << 4,  ///< External Commissioner allowed
    OT_SECURITY_POLICY_BEACONS                = 1 << 3,  ///< Beacons enabled
};

/**
  * This type represents Channel Mask Page 0.
  *
  */
typedef uint32_t otChannelMaskPage0;

/**
 * This type represents the IEEE 802.15.4 PAN ID.
 *
 */
typedef uint16_t otPanId;

/**
 * This type represents the IEEE 802.15.4 Short Address.
 *
 */
typedef uint16_t otShortAddress;

#define OT_EXT_ADDRESS_SIZE        8   ///< Size of an IEEE 802.15.4 Extended Address (bytes)

/**
 * This type represents the IEEE 802.15.4 Extended Address.
 *
 */
typedef struct otExtAddress
{
    uint8_t m8[OT_EXT_ADDRESS_SIZE];  ///< IEEE 802.15.4 Extended Address bytes
} otExtAddress;

#define OT_IP6_PREFIX_SIZE         8   ///< Size of an IPv6 prefix (bytes)
#define OT_IP6_ADDRESS_SIZE        16  ///< Size of an IPv6 address (bytes)

/**
 * This structure represents an IPv6 address.
 */
OT_TOOL_PACKED_BEGIN
struct otIp6Address
{
    union
    {
        uint8_t  m8[OT_IP6_ADDRESS_SIZE];                      ///< 8-bit fields
        uint16_t m16[OT_IP6_ADDRESS_SIZE / sizeof(uint16_t)];  ///< 16-bit fields
        uint32_t m32[OT_IP6_ADDRESS_SIZE / sizeof(uint32_t)];  ///< 32-bit fields
    } mFields;                                                 ///< IPv6 accessor fields
} OT_TOOL_PACKED_END;

typedef struct otIp6Address otIp6Address;


/**
 * This structure represents the local and peer IPv6 socket addresses.
 */
typedef struct otMessageInfo
{
    otIp6Address mSockAddr;     ///< The local IPv6 address.
    otIp6Address mPeerAddr;     ///< The peer IPv6 address.
    uint16_t     mSockPort;     ///< The local transport-layer port.
    uint16_t     mPeerPort;     ///< The peer transport-layer port.
    int8_t       mInterfaceId;  ///< An IPv6 interface identifier.
    uint8_t      mHopLimit;     ///< The IPv6 Hop Limit.
    const void  *mLinkInfo;     ///< A pointer to link-specific information.
} otMessageInfo;

/**
 * This type points to an OpenThread message buffer.
 */
typedef struct otMessage
{
    struct otMessage *mNext;  ///< A pointer to the next Message buffer.
} otMessage;

/**
 * @addtogroup commands  Commands
 *
 * @{
 *
 */

#define OT_PANID_BROADCAST   0xffff      ///< IEEE 802.15.4 Broadcast PAN ID

#define OT_CHANNEL_11_MASK   (1 << 11)   ///< Channel 11
#define OT_CHANNEL_12_MASK   (1 << 12)   ///< Channel 12
#define OT_CHANNEL_13_MASK   (1 << 13)   ///< Channel 13
#define OT_CHANNEL_14_MASK   (1 << 14)   ///< Channel 14
#define OT_CHANNEL_15_MASK   (1 << 15)   ///< Channel 15
#define OT_CHANNEL_16_MASK   (1 << 16)   ///< Channel 16
#define OT_CHANNEL_17_MASK   (1 << 17)   ///< Channel 17
#define OT_CHANNEL_18_MASK   (1 << 18)   ///< Channel 18
#define OT_CHANNEL_19_MASK   (1 << 19)   ///< Channel 19
#define OT_CHANNEL_20_MASK   (1 << 20)   ///< Channel 20
#define OT_CHANNEL_21_MASK   (1 << 21)   ///< Channel 21
#define OT_CHANNEL_22_MASK   (1 << 22)   ///< Channel 22
#define OT_CHANNEL_23_MASK   (1 << 23)   ///< Channel 23
#define OT_CHANNEL_24_MASK   (1 << 24)   ///< Channel 24
#define OT_CHANNEL_25_MASK   (1 << 25)   ///< Channel 25
#define OT_CHANNEL_26_MASK   (1 << 26)   ///< Channel 26

#define OT_CHANNEL_ALL       0xffffffff  ///< All channels

#define OT_STEERING_DATA_MAX_LENGTH       16  ///< Max steering data length (bytes)

/**
 * This structure represents the steering data.
 *
 */
typedef struct otSteeringData
{
    uint8_t mLength;
    uint8_t m8[OT_STEERING_DATA_MAX_LENGTH];
} otSteeringData;

/**
 * This struct represents a received IEEE 802.15.4 Beacon.
 *
 */
typedef struct otActiveScanResult
{
    otExtAddress    mExtAddress;      ///< IEEE 802.15.4 Extended Address
    otNetworkName   mNetworkName;     ///< Thread Network Name
    otExtendedPanId mExtendedPanId;   ///< Thread Extended PAN ID
    otSteeringData  mSteeringData;    ///< Steering Data
    uint16_t        mPanId;           ///< IEEE 802.15.4 PAN ID
    uint16_t        mJoinerUdpPort;   ///< Joiner UDP Port
    uint8_t         mChannel;         ///< IEEE 802.15.4 Channel
    int8_t          mRssi;            ///< RSSI (dBm)
    uint8_t         mLqi;             ///< LQI
    unsigned int    mVersion : 4;     ///< Version
    bool            mIsNative : 1;    ///< Native Commissioner flag
    bool            mIsJoinable : 1;  ///< Joining Permitted flag
} otActiveScanResult;

/**
 * This struct represents an energy scan result.
 *
 */
typedef struct otEnergyScanResult
{
    uint8_t mChannel;                ///< IEEE 802.15.4 Channel
    int8_t  mMaxRssi;                ///< The max RSSI (dBm)
} otEnergyScanResult;

/**
 * @}
 *
 */

/**
 * @addtogroup config  Configuration
 *
 * @brief
 *   This module includes functions for configuration.
 *
 * @{
 *
 */

/**
 * @defgroup config-general  General
 *
 * @brief
 *   This module includes functions that manage configuration parameters for the Thread Child, Router, and Leader roles.
 *
 * @{
 *
 */

/**
 * This structure represents an Active or Pending Operational Dataset.
 *
 */
typedef struct otOperationalDataset
{
    uint64_t             mActiveTimestamp;            ///< Active Timestamp
    uint64_t             mPendingTimestamp;           ///< Pending Timestamp
    otMasterKey          mMasterKey;                  ///< Network Master Key
    otNetworkName        mNetworkName;                ///< Network Name
    otExtendedPanId      mExtendedPanId;              ///< Extended PAN ID
    otMeshLocalPrefix    mMeshLocalPrefix;            ///< Mesh Local Prefix
    uint32_t             mDelay;                      ///< Delay Timer
    otPanId              mPanId;                      ///< PAN ID
    uint16_t             mChannel;                    ///< Channel
    otPSKc               mPSKc;                       ///< PSKc
    otSecurityPolicy     mSecurityPolicy;             ///< Security Policy
    otChannelMaskPage0   mChannelMaskPage0;           ///< Channel Mask Page 0

    bool                 mIsActiveTimestampSet : 1;   ///< TRUE if Active Timestamp is set, FALSE otherwise.
    bool                 mIsPendingTimestampSet : 1;  ///< TRUE if Pending Timestamp is set, FALSE otherwise.
    bool                 mIsMasterKeySet : 1;         ///< TRUE if Network Master Key is set, FALSE otherwise.
    bool                 mIsNetworkNameSet : 1;       ///< TRUE if Network Name is set, FALSE otherwise.
    bool                 mIsExtendedPanIdSet : 1;     ///< TRUE if Extended PAN ID is set, FALSE otherwise.
    bool                 mIsMeshLocalPrefixSet : 1;   ///< TRUE if Mesh Local Prefix is set, FALSE otherwise.
    bool                 mIsDelaySet : 1;             ///< TRUE if Delay Timer is set, FALSE otherwise.
    bool                 mIsPanIdSet : 1;             ///< TRUE if PAN ID is set, FALSE otherwise.
    bool                 mIsChannelSet : 1;           ///< TRUE if Channel is set, FALSE otherwise.
    bool                 mIsPSKcSet : 1;              ///< TRUE if PSKc is set, FALSE otherwise.
    bool                 mIsSecurityPolicySet : 1;    ///< TRUE if Security Policy is set, FALSE otherwise.
    bool                 mIsChannelMaskPage0Set : 1;  ///< TRUE if Channel Mask Page 0 is set, FALSE otherwise.
} otOperationalDataset;

/**
 * This structure represents a Commissioning Dataset.
 *
 */
typedef struct otCommissioningDataset
{
    uint16_t              mLocator;                   ///< Border Router RLOC16
    uint16_t              mSessionId;                 ///< Commissioner Session Id
    otSteeringData        mSteeringData;              ///< Steering Data
    uint16_t              mJoinerUdpPort;             ///< Joiner UDP Port

    bool                  mIsLocatorSet : 1;          ///< TRUE if Border Router RLOC16 is set, FALSE otherwise.
    bool                  mIsSessionIdSet: 1;         ///< TRUE if Commissioner Session Id is set, FALSE otherwise.
    bool                  mIsSteeringDataSet : 1;     ///< TRUE if Steering Data is set, FALSE otherwise.
    bool                  mIsJoinerUdpPortSet : 1;    ///< TRUE if Joiner UDP Port is set, FALSE otherwise.
} otCommissioningDataset;

/**
 * This enumeration represents meshcop TLV types.
 *
 */
typedef enum otMeshcopTlvType
{
    OT_MESHCOP_TLV_CHANNEL                   = 0,    ///< meshcop Channel TLV
    OT_MESHCOP_TLV_PANID                     = 1,    ///< meshcop Pan Id TLV
    OT_MESHCOP_TLV_EXTPANID                  = 2,    ///< meshcop Extended Pan Id TLV
    OT_MESHCOP_TLV_NETWORKNAME               = 3,    ///< meshcop Network Name TLV
    OT_MESHCOP_TLV_PSKC                      = 4,    ///< meshcop PSKc TLV
    OT_MESHCOP_TLV_MASTERKEY                 = 5,    ///< meshcop Network Master Key TLV
    OT_MESHCOP_TLV_NETWORK_KEY_SEQUENCE      = 6,    ///< meshcop Network Key Sequence TLV
    OT_MESHCOP_TLV_MESHLOCALPREFIX           = 7,    ///< meshcop Mesh Local Prefix TLV
    OT_MESHCOP_TLV_STEERING_DATA             = 8,    ///< meshcop Steering Data TLV
    OT_MESHCOP_TLV_BORDER_AGENT_RLOC         = 9,    ///< meshcop Border Agent Locator TLV
    OT_MESHCOP_TLV_COMMISSIONER_ID           = 10,   ///< meshcop Commissioner ID TLV
    OT_MESHCOP_TLV_COMM_SESSION_ID           = 11,   ///< meshcop Commissioner Session ID TLV
    OT_MESHCOP_TLV_SECURITYPOLICY            = 12,   ///< meshcop Security Policy TLV
    OT_MESHCOP_TLV_GET                       = 13,   ///< meshcop Get TLV
    OT_MESHCOP_TLV_ACTIVETIMESTAMP           = 14,   ///< meshcop Active Timestamp TLV
    OT_MESHCOP_TLV_STATE                     = 16,   ///< meshcop State TLV
    OT_MESHCOP_TLV_JOINER_DTLS               = 17,   ///< meshcop Joiner DTLS Encapsulation TLV
    OT_MESHCOP_TLV_JOINER_UDP_PORT           = 18,   ///< meshcop Joiner UDP Port TLV
    OT_MESHCOP_TLV_JOINER_IID                = 19,   ///< meshcop Joiner IID TLV
    OT_MESHCOP_TLV_JOINER_RLOC               = 20,   ///< meshcop Joiner Router Locator TLV
    OT_MESHCOP_TLV_JOINER_ROUTER_KEK         = 21,   ///< meshcop Joiner Router KEK TLV
    OT_MESHCOP_TLV_PROVISIONING_URL          = 32,   ///< meshcop Provisioning URL TLV
    OT_MESHCOP_TLV_VENDOR_NAME_TLV           = 33,   ///< meshcop Vendor Name TLV
    OT_MESHCOP_TLV_VENDOR_MODEL_TLV          = 34,   ///< meshcop Vendor Model TLV
    OT_MESHCOP_TLV_VENDOR_SW_VERSION_TLV     = 35,   ///< meshcop Vendor SW Version TLV
    OT_MESHCOP_TLV_VENDOR_DATA_TLV           = 36,   ///< meshcop Vendor Data TLV
    OT_MESHCOP_TLV_VENDOR_STACK_VERSION_TLV  = 37,   ///< meshcop Vendor Stack Version TLV
    OT_MESHCOP_TLV_PENDINGTIMESTAMP          = 51,   ///< meshcop Pending Timestamp TLV
    OT_MESHCOP_TLV_DELAYTIMER                = 52,   ///< meshcop Delay Timer TLV
    OT_MESHCOP_TLV_CHANNELMASK               = 53,   ///< meshcop Channel Mask TLV
    OT_MESHCOP_TLV_COUNT                     = 54,   ///< meshcop Count TLV
    OT_MESHCOP_TLV_PERIOD                    = 55,   ///< meshcop Period TLV
    OT_MESHCOP_TLV_SCAN_DURATION             = 56,   ///< meshcop Scan Duration TLV
    OT_MESHCOP_TLV_ENERGY_LIST               = 57,   ///< meshcop Energy List TLV
    OT_MESHCOP_TLV_DISCOVERYREQUEST          = 128,  ///< meshcop Discovery Request TLV
    OT_MESHCOP_TLV_DISCOVERYRESPONSE         = 129,  ///< meshcop Discovery Response TLV
} otMeshcopTlvType;

/**
 * This structure represents an MLE Link Mode configuration.
 */
OT_TOOL_ALIGN(4)
typedef struct otLinkModeConfig
{
    /**
     * 1, if the sender has its receiver on when not transmitting.  0, otherwise.
     */
    bool mRxOnWhenIdle : 1;

    /**
     * 1, if the sender will use IEEE 802.15.4 to secure all data requests.  0, otherwise.
     */
    bool mSecureDataRequests : 1;

    /**
     * 1, if the sender is an FFD.  0, otherwise.
     */
    bool mDeviceType : 1;

    /**
     * 1, if the sender requires the full Network Data.  0, otherwise.
     */
    bool mNetworkData : 1;
} otLinkModeConfig;

/**
 * This enumeration represents flags that indicate what configuration or state has changed within OpenThread.
 *
 */
enum
{
    OT_IP6_ADDRESS_ADDED         = 1 << 0,  ///< IPv6 address was added
    OT_IP6_ADDRESS_REMOVED       = 1 << 1,  ///< IPv6 address was removed

    OT_NET_ROLE                  = 1 << 3,  ///< Device role (disabled, detached, child, router, leader) changed
    OT_NET_PARTITION_ID          = 1 << 4,  ///< Partition ID changed
    OT_NET_KEY_SEQUENCE_COUNTER  = 1 << 5,  ///< Thread Key Sequence changed

    OT_THREAD_CHILD_ADDED        = 1 << 6,  ///< Child was added
    OT_THREAD_CHILD_REMOVED      = 1 << 7,  ///< Child was removed
    OT_THREAD_NETDATA_UPDATED    = 1 << 8,  ///< Thread Network Data updated

    OT_IP6_LL_ADDR_CHANGED       = 1 << 9,  ///< The link-local address has changed
    OT_IP6_ML_ADDR_CHANGED       = 1 << 10, ///< The mesh-local address has changed

    OT_IP6_RLOC_ADDED            = 1 << 11, ///< RLOC was added
    OT_IP6_RLOC_REMOVED          = 1 << 12, ///< RLOC was removed
};

/**
 * @}
 */

/**
 * @defgroup config-br  Border Router
 *
 * @brief
 *   This module includes functions that manage configuration parameters that apply to the Thread Border Router role.
 *
 * @{
 *
 */

/**
 * This structure represents an IPv6 prefix.
 */
typedef struct otIp6Prefix
{
    otIp6Address  mPrefix;  ///< The IPv6 prefix.
    uint8_t       mLength;  ///< The IPv6 prefix length.
} otIp6Prefix;

#define OT_NETWORK_DATA_ITERATOR_INIT  0  ///< Initializer for otNetworkDataIterator.

typedef uint8_t otNetworkDataIterator;  ///< Used to iterate through Network Data information.

/**
 * This structure represents a Border Router configuration.
 */
typedef struct otBorderRouterConfig
{
    /**
     * The IPv6 prefix.
     */
    otIp6Prefix mPrefix;

    /**
     * A 2-bit signed integer indicating router preference as defined in RFC 4291.
     */
    int mPreference : 2;

    /**
     * TRUE, if @p mPrefix is preferred.  FALSE, otherwise.
     */
    bool mPreferred : 1;

    /**
     * TRUE, if @p mPrefix should be used for address autoconfiguration.  FALSE, otherwise.
     */
    bool mSlaac : 1;

    /**
     * TRUE, if this border router is a DHCPv6 Agent that supplies IPv6 address configuration.  FALSE, otherwise.
     */
    bool mDhcp : 1;

    /**
     * TRUE, if this border router is a DHCPv6 Agent that supplies other configuration data.  FALSE, otherwise.
     */
    bool mConfigure : 1;

    /**
     * TRUE, if this border router is a default route for @p mPrefix.  FALSE, otherwise.
     */
    bool mDefaultRoute : 1;

    /**
     * TRUE, if this prefix is considered on-mesh.  FALSE, otherwise.
     */
    bool mOnMesh : 1;

    /**
     * TRUE, if this configuration is considered Stable Network Data.  FALSE, otherwise.
     */
    bool mStable : 1;

    /**
     * The Border Agent Rloc.
     */
    uint16_t mRloc16;
} otBorderRouterConfig;

/**
 * This structure represents an External Route configuration.
 */
typedef struct otExternalRouteConfig
{
    /**
     * The prefix for the off-mesh route.
     */
    otIp6Prefix mPrefix;

    /**
     * A 2-bit signed integer indicating router preference as defined in RFC 4291.
     */
    int mPreference : 2;

    /**
     * TRUE, if this configuration is considered Stable Network Data.  FALSE, otherwise.
     */
    bool mStable : 1;
} otExternalRouteConfig;

/**
 * @}
 *
 */

/**
 * @defgroup config-test  Test
 *
 * @brief
 *   This module includes functions that manage configuration parameters required for Thread Certification testing.
 *
 * @{
 *
 */

/**
 * Represents any restrictions on the attach process.
 */
typedef enum otMleAttachFilter
{
    kMleAttachAnyPartition    = 0,  ///< Attach to any Thread partition.
    kMleAttachSamePartition1  = 1,  ///< Attach to the same Thread partition (attempt 1).
    kMleAttachSamePartition2  = 2,  ///< Attach to the same Thread partition (attempt 2).
    kMleAttachBetterPartition = 3,  ///< Attach to a better (i.e. higher weight/partition id) Thread partition.
} otMleAttachFilter;

/**
 * This structure represents a whitelist entry.
 *
 */
typedef struct otMacWhitelistEntry
{
    otExtAddress mExtAddress;       ///< IEEE 802.15.4 Extended Address
    int8_t       mRssi;             ///< RSSI value
    bool         mValid : 1;        ///< Indicates whether or not the whitelist entry is valid
    bool         mFixedRssi : 1;    ///< Indicates whether or not the RSSI value is fixed.
} otMacWhitelistEntry;

/**
 * This structure represents a blacklist entry.
 *
 */
typedef struct otMacBlacklistEntry
{
    otExtAddress mExtAddress;       ///< IEEE 802.15.4 Extended Address
    bool         mValid;            ///< Indicates whether or not the blacklist entry is valid
} otMacBlacklistEntry;

/**
 * @}
 *
 */

/**
 * @}
 *
 */

/**
 * @addtogroup diags  Diagnostics
 *
 * @brief
 *   This module includes functions that expose internal state.
 *
 * @{
 *
 */

/**
 * Represents a Thread device role.
 */
typedef enum
{
    kDeviceRoleOffline,   ///< The Thread device is offline and unavailable.
    kDeviceRoleDisabled,  ///< The Thread stack is disabled.
    kDeviceRoleDetached,  ///< Not currently participating in a Thread network/partition.
    kDeviceRoleChild,     ///< The Thread Child role.
    kDeviceRoleRouter,    ///< The Thread Router role.
    kDeviceRoleLeader,    ///< The Thread Leader role.
} otDeviceRole;

/**
 * This structure holds diagnostic information for a neighboring Thread node
 *
 */
typedef struct
{
    otExtAddress   mExtAddress;            ///< IEEE 802.15.4 Extended Address
    uint32_t       mAge;                   ///< Time last heard
    uint16_t       mRloc16;                ///< RLOC16
    uint32_t       mLinkFrameCounter;      ///< Link Frame Counter
    uint32_t       mMleFrameCounter;       ///< MLE Frame Counter
    uint8_t        mLinkQualityIn;         ///< Link Quality In
    int8_t         mAverageRssi;           ///< Average RSSI
    bool           mRxOnWhenIdle : 1;      ///< rx-on-when-idle
    bool           mSecureDataRequest : 1; ///< Secure Data Requests
    bool           mFullFunction : 1;      ///< Full Function Device
    bool           mFullNetworkData : 1;   ///< Full Network Data
    bool           mIsChild : 1;           ///< Is the neighbor a child
} otNeighborInfo;

#define OT_NEIGHBOR_INFO_ITERATOR_INIT  0  ///< Initializer for otNeighborInfoIterator.

typedef int16_t otNeighborInfoIterator;    ///< Used to iterate through neighbor table.

/**
 * This structure holds diagnostic information for a Thread Child
 *
 */
typedef struct
{
    otExtAddress   mExtAddress;            ///< IEEE 802.15.4 Extended Address
    uint32_t       mTimeout;               ///< Timeout
    uint32_t       mAge;                   ///< Time last heard
    uint16_t       mRloc16;                ///< RLOC16
    uint16_t       mChildId;               ///< Child ID
    uint8_t        mNetworkDataVersion;    ///< Network Data Version
    uint8_t        mLinkQualityIn;         ///< Link Quality In
    int8_t         mAverageRssi;           ///< Average RSSI
    bool           mRxOnWhenIdle : 1;      ///< rx-on-when-idle
    bool           mSecureDataRequest : 1; ///< Secure Data Requests
    bool           mFullFunction : 1;      ///< Full Function Device
    bool           mFullNetworkData : 1;   ///< Full Network Data
} otChildInfo;

/**
 * This structure holds diagnostic information for a Thread Router
 *
 */
OT_TOOL_ALIGN(4)
typedef struct
{
    otExtAddress   mExtAddress;            ///< IEEE 802.15.4 Extended Address
    uint16_t       mRloc16;                ///< RLOC16
    uint8_t        mRouterId;              ///< Router ID
    uint8_t        mNextHop;               ///< Next hop to router
    uint8_t        mPathCost;              ///< Path cost to router
    uint8_t        mLinkQualityIn;         ///< Link Quality In
    uint8_t        mLinkQualityOut;        ///< Link Quality Out
    uint8_t        mAge;                   ///< Time last heard
    bool           mAllocated : 1;         ///< Router ID allocated or not
    bool           mLinkEstablished : 1;   ///< Link established with Router ID or not
} otRouterInfo;

/**
 * This structure represents an EID cache entry.
 *
 */
typedef struct otEidCacheEntry
{
    otIp6Address    mTarget;          ///< Target
    otShortAddress  mRloc16;          ///< RLOC16
    bool            mValid : 1;       ///< Indicates whether or not the cache entry is valid
} otEidCacheEntry;

/**
 * This structure represents the Thread Leader Data.
 *
 */
typedef struct otLeaderData
{
    uint32_t mPartitionId;            ///< Partition ID
    uint8_t mWeighting;               ///< Leader Weight
    uint8_t mDataVersion;             ///< Full Network Data Version
    uint8_t mStableDataVersion;       ///< Stable Network Data Version
    uint8_t mLeaderRouterId;          ///< Leader Router ID
} otLeaderData;

/**
 * This structure represents the MAC layer counters.
 */
typedef struct otMacCounters
{
    uint32_t mTxTotal;                ///< The total number of transmissions.
    uint32_t mTxUnicast;              ///< The total number of unicast transmissions.
    uint32_t mTxBroadcast;            ///< The total number of broadcast transmissions.
    uint32_t mTxAckRequested;         ///< The number of transmissions with ack request.
    uint32_t mTxAcked;                ///< The number of transmissions that were acked.
    uint32_t mTxNoAckRequested;       ///< The number of transmissions without ack request.
    uint32_t mTxData;                 ///< The number of transmitted data.
    uint32_t mTxDataPoll;             ///< The number of transmitted data poll.
    uint32_t mTxBeacon;               ///< The number of transmitted beacon.
    uint32_t mTxBeaconRequest;        ///< The number of transmitted beacon request.
    uint32_t mTxOther;                ///< The number of transmitted other types of frames.
    uint32_t mTxRetry;                ///< The number of retransmission times.
    uint32_t mTxErrCca;               ///< The number of CCA failure times.
    uint32_t mTxErrAbort;             ///< The number of frame transmission failures due to abort error.
    uint32_t mRxTotal;                ///< The total number of received packets.
    uint32_t mRxUnicast;              ///< The total number of unicast packets received.
    uint32_t mRxBroadcast;            ///< The total number of broadcast packets received.
    uint32_t mRxData;                 ///< The number of received data.
    uint32_t mRxDataPoll;             ///< The number of received data poll.
    uint32_t mRxBeacon;               ///< The number of received beacon.
    uint32_t mRxBeaconRequest;        ///< The number of received beacon request.
    uint32_t mRxOther;                ///< The number of received other types of frames.
    uint32_t mRxWhitelistFiltered;    ///< The number of received packets filtered by whitelist.
    uint32_t mRxDestAddrFiltered;     ///< The number of received packets filtered by destination check.
    uint32_t mRxDuplicated;           ///< The number of received duplicated packets.
    uint32_t mRxErrNoFrame;           ///< The number of received packets that do not contain contents.
    uint32_t mRxErrUnknownNeighbor;   ///< The number of received packets from unknown neighbor.
    uint32_t mRxErrInvalidSrcAddr;    ///< The number of received packets whose source address is invalid.
    uint32_t mRxErrSec;               ///< The number of received packets with security error.
    uint32_t mRxErrFcs;               ///< The number of received packets with FCS error.
    uint32_t mRxErrOther;             ///< The number of received packets with other error.
} otMacCounters;

/**
 * This structure represents the message buffer information.
 */
typedef struct otBufferInfo
{
    uint16_t mTotalBuffers;           ///< The number of buffers in the pool.
    uint16_t mFreeBuffers;            ///< The number of free message buffers.
    uint16_t m6loSendMessages;        ///< The number of messages in the 6lo send queue.
    uint16_t m6loSendBuffers;         ///< The number of buffers in the 6lo send queue.
    uint16_t m6loReassemblyMessages;  ///< The number of messages in the 6LoWPAN reassembly queue.
    uint16_t m6loReassemblyBuffers;   ///< The number of buffers in the 6LoWPAN reassembly queue.
    uint16_t mIp6Messages;            ///< The number of messages in the IPv6 send queue.
    uint16_t mIp6Buffers;             ///< The number of buffers in the IPv6 send queue.
    uint16_t mMplMessages;            ///< The number of messages in the MPL send queue.
    uint16_t mMplBuffers;             ///< The number of buffers in the MPL send queue.
    uint16_t mMleMessages;            ///< The number of messages in the MLE send queue.
    uint16_t mMleBuffers;             ///< The number of buffers in the MLE send queue.
    uint16_t mArpMessages;            ///< The number of messages in the ARP send queue.
    uint16_t mArpBuffers;             ///< The number of buffers in the ARP send queue.
    uint16_t mCoapClientMessages;     ///< The number of messages in the CoAP client send queue.
    uint16_t mCoapClientBuffers;      ///< The number of buffers in the CoAP client send queue.
} otBufferInfo;

/**
 * @}
 *
 */

/**
 * This structure represents an IPv6 network interface unicast address.
 *
 */
typedef struct otNetifAddress
{
    otIp6Address           mAddress;                 ///< The IPv6 unicast address.
    uint8_t                mPrefixLength;            ///< The Prefix length.
    bool                   mPreferred : 1;           ///< TRUE if the address is preferred, FALSE otherwise.
    bool                   mValid : 1;               ///< TRUE if the address is valid, FALSE otherwise.
    bool                   mScopeOverrideValid : 1;  ///< TRUE if the mScopeOverride value is valid, FALSE othewrise.
    unsigned int           mScopeOverride : 4;       ///< The IPv6 scope of this address.
    bool                   mRloc : 1;                ///< TRUE if the address is an RLOC, FALSE otherwise.
    struct otNetifAddress *mNext;                    ///< A pointer to the next network interface address.
} otNetifAddress;

/**
 * This structure represents an IPv6 network interface multicast address.
 *
 */
typedef struct otNetifMulticastAddress
{
    otIp6Address                    mAddress;   ///< The IPv6 multicast address.
    struct otNetifMulticastAddress *mNext;      ///< A pointer to the next network interface multicast address.
} otNetifMulticastAddress;

/**
 * This enumeration represents the list of allowable values for an InterfaceId.
 */
typedef enum otNetifInterfaceId
{
    OT_NETIF_INTERFACE_ID_THREAD = 1,  ///< The Thread Network interface ID.
} otNetifInterfaceId;

/**
 * This structure represents data used by Semantically Opaque IID Generator.
 *
 */
typedef struct
{
    uint8_t        *mInterfaceId;        ///< String of bytes representing interface ID. Like "eth0" or "wlan0".
    uint8_t         mInterfaceIdLength;  ///< Length of interface ID string.

    uint8_t        *mNetworkId;          ///< Network ID (or name). Can be null if mNetworkIdLength is 0.
    uint8_t         mNetworkIdLength;    ///< Length of Network ID string.

    uint8_t         mDadCounter;         ///< Duplicate address detection counter.

    uint8_t        *mSecretKey;          ///< Secret key used to create IID. Cannot be null.
    uint16_t        mSecretKeyLength;    ///< Secret key length in bytes. Should be at least 16 bytes == 128 bits.
} otSemanticallyOpaqueIidGeneratorData;

/**
 * @addtogroup icmp6  ICMPv6
 *
 * @brief
 *   This module includes functions that control ICMPv6 communication.
 *
 * @{
 *
 */

/**
 * ICMPv6 Message Types
 *
*/
typedef enum otIcmp6Type
{
    kIcmp6TypeDstUnreach  = 1,     ///< Destination Unreachable
    kIcmp6TypeEchoRequest = 128,   ///< Echo Request
    kIcmp6TypeEchoReply   = 129,   ///< Echo Reply
} otIcmp6Type;

/**
 * ICMPv6 Message Codes
 *
 */
typedef enum otIcmp6Code
{
    kIcmp6CodeDstUnreachNoRoute = 0,  ///< Destination Unreachable No Route
} otIcmp6Code;

#define OT_ICMP6_HEADER_DATA_SIZE  4   ///< Size of an message specific data of ICMPv6 Header.

/**
 * This structure represents an ICMPv6 header.
 *
 */
OT_TOOL_PACKED_BEGIN
struct otIcmp6Header
{
    uint8_t      mType;      ///< Type
    uint8_t      mCode;      ///< Code
    uint16_t     mChecksum;  ///< Checksum
    union
    {
        uint8_t  m8[OT_ICMP6_HEADER_DATA_SIZE / sizeof(uint8_t)];
        uint16_t m16[OT_ICMP6_HEADER_DATA_SIZE / sizeof(uint16_t)];
        uint32_t m32[OT_ICMP6_HEADER_DATA_SIZE / sizeof(uint32_t)];
    } mData;                 ///< Message-specific data
} OT_TOOL_PACKED_END;

typedef struct otIcmp6Header otIcmp6Header;

/**
 * This callback allows OpenThread to inform the application of a received ICMPv6 message.
 *
 * @param[in]  aContext      A pointer to arbitrary context information.
 * @param[in]  aMessage      A pointer to the received message.
 * @param[in]  aMessageInfo  A pointer to message information associated with @p aMessage.
 * @param[in]  aIcmpHeader   A pointer to the received ICMPv6 header.
 *
 */
typedef void (*otIcmp6ReceiveCallback)(void *aContext, otMessage *aMessage, const otMessageInfo *aMessageInfo,
                                       const otIcmp6Header *aIcmpHeader);

/**
 * This structure implements ICMPv6 message handler.
 *
 */
typedef struct otIcmp6Handler
{
    otIcmp6ReceiveCallback  mReceiveCallback;
    void                   *mContext;
    struct otIcmp6Handler  *mNext;
} otIcmp6Handler;

/**
 * @}
 *
 */

/**
 * @addtogroup udp  UDP
 *
 * @brief
 *   This module includes functions that control UDP communication.
 *
 * @{
 *
 */

/**
 * This structure represents an IPv6 socket address.
 */
typedef struct otSockAddr
{
    otIp6Address mAddress;  ///< An IPv6 address.
    uint16_t     mPort;     ///< A transport-layer port.
    int8_t       mScopeId;  ///< An IPv6 scope identifier.
} otSockAddr;

#ifdef OTDLL

/**
 * This function pointer is called to notify addition and removal of OpenThread devices.
 *
 * @param[in]  aAdded       A flag indicating if the device was added or removed.
 * @param[in]  aDeviceGuid  A GUID indicating which device state changed.
 * @param[in]  aContext     A pointer to application-specific context.
 *
 */
typedef void (OTCALL *otDeviceAvailabilityChangedCallback)(bool aAdded, const GUID *aDeviceGuid, void *aContext);

#endif // OTDLL

/**
 * @}
 *
 */

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // OPENTHREAD_TYPES_H_
