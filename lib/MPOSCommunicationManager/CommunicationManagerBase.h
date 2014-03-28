//
//  CommunicationManagerBase.h
//  BLEBaseDriver
//
//  Created by Landi 联迪 - Robert on 13-8-27.
//  Copyright (c) 2013年 Landi 联迪. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DeviceSearchListener.h"
#import "CommunicationCallBack.h"
#import "CommDownloadCallback.h"
#import "DeviceInfo.h"

typedef enum _enumDeviceCommunicationMode{
    MASTERSLAVE,
    DUPLEX,
}DeviceCommunicationMode;

@interface CommunicationManagerBase : NSObject

+(CommunicationManagerBase*)sharedInstance:(DeviceCommunicationChannel)channel;

/*!
 * @method searchDevices:detectAudioDevice:detectBluetooth:timeout:
 * @discussion start discovering device around, the searching result will return by @link DeviceSearchListener @/link, see detail in @link DeviceSearchListener @/link interface
 * @param dsl: search result will return by it,
 * @param detectAudioDevice: If application want to detect which a device connected phone by audio jack,set this value to true, else false.
 * @param detectBluetoothDevice: If application want to detect which a device connected phone by bluetooth, set this value to true, else false.
 * @param timeout: the max time to search, this parameter is not used now, just reserve for future.
 * @return {@int}
      0 phone start to discover device
     -1 phone don’t support Bluetooth,
     -2 phone has not power on Bluetooth,
     -3 phone has error when startDiscovery Bluetooth Device
 */
+(int)searchDevices:(id<DeviceSearchListener>)dsl
  detectAudioDevice:(BOOL)detectAudioDevcie
    detectBluetooth:(BOOL)detectBluetoothDevice
            timeout:(long)timeout;


+(void)stopSearching;

/*!
 * @method getLibVersion
 * @discussion Return library version.
 * @return library version {@NSString}
 */
+(NSString*)getLibVersion;

+(void)switchLog:(BOOL)bOpen;

/*!
 * @method openDevice:
 * @discussion Set up connection with the specified Bluetoothidentifier
 * @param Identifier   : for Bluetooth maybe it’s an address or uuid.
 * @return  {@int}
     0 represent setup connection success,
    -1 represent the address is Illegal,
    -2 represent setup connection failed.
    -4 phone don’t support Bluetooth,
    -5 phone has not power on Bluetooth,
    -6 phone has unknown error.
 */
-(int)openDevice:(NSString*)identifier;


/*!
 * @method openDevice:cb:mode:
 * @discussion Set up connection with the specified Bluetoothidentifier
 * @param Identifier    for Bluetooth maybe it’s an address or uuid.
 * @param cb    exchange callback.
 * @param mode  indicate the communication mode.
 * @return {@int}
      0 represent setup connection success,
     -1 represent the address is Illegal,
     -2 represent setup connection failed.
     -4 phone don’t support Bluetooth,
     -5 phone has not power on Bluetooth,
     -6 phone has unknown error.
 */
-(int)openDevice:(NSString *)identifier cb:(id<CommunicationCallBack>) cb mode:(DeviceCommunicationMode)mode;


/*!
 * @method exchangeData:timeout:cb:
 * @discussion Do the data exchanging between app and device in the specified timeout. It will call @link CommunicationCallBack @/link after data exchanging
            finished. See the @link CommunicationCallBack @/link protocol.
 * @param data  exchange data,
 * @param timeout   exchange timeout,
 * @param cb    exchange callback.
 
 * @return {@int}
     0 represent phone can send data
    -1 represent the current data exchanging is not completed, it can’t do exchange now.
    -2 represent phone is not opened.
 */
-(int)exchangeData:(NSData*)data timeout:(long)timeout cb:(id<CommunicationCallBack>) cb;
-(int)exchangeData:(NSData *)data timeout:(long)timeout;


/*!
 * @method cancelExchange
 * @discussion Try send cancel command to cancel the current data exchanging
 
 * @return {@int}
      0 represent can cancel the current exchange, it will call onError() when cancel command finish. See the detail in Error Code.
     -1 represent represent there is not data exchanging , no need to cancel.
     -2 represent phone is not opened.
 */
-(int)cancelExchange;


/*! 
 * @method closeDevice
 * @discussion Disconnected Bluetooth and release resource.
 */
-(void)closeDevice;


/*!
 * @method closeDevice
 * @discussion Disconnected Bluetooth and release resource.
 */
-(void)closeResource;


-(BOOL)isConnected;
-(void)download:(NSString*)identifier path:(NSString*)filePath callback:(id<CommDownloadCallback>)cb;

@end
