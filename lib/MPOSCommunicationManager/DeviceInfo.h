//
//  DeviceInfo.h
//  BLEBaseDriver
//
//  Created by Landi 联迪 on 13-8-28.
//  Copyright (c) 2013年 Landi 联迪. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum _enumDeviceCommunicationChannel{
    AUDIOJACK,
    BLUETOOTH,
}DeviceCommunicationChannel;

@interface DeviceInfo : NSObject

-(id)initWithName:(NSString*)name identifier:(NSString*)identifier channel:(DeviceCommunicationChannel)dcc;

/*!
 * @method getName
 * @discussion Get the device name, refers to the Bluetooth indicates Bluetooth’ name and it is null for the audio jack.
 * @return device name {@NSString}
 */
-(NSString*)getName;

/*!
 * @method getIdentifier
 * @discussion Get the device Identifier, refers to the Bluetooth indicates device’s address or uuid and it is null for the audio jack.
 * @return device Identifier {@NSString}
 */
-(NSString*)getIdentifier;

/*!
 * @method getDevChannel
 * @discussion Get the device’s communication channel, the DeviceCommunicationChannel.BLUETOOTH for Bluetooth and
    DeviceCommunicationChannel.AUDIOJACK for audio jack.
 * @return device’s communication channel {@DeviceCommunicationChannel}
 */
-(DeviceCommunicationChannel)getDevChannel;

@end
