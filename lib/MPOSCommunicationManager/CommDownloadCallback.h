//
//  CommDownloadCallback.h
//  MPOSCommunicationManager
//
//  Created by Wu Robert on 12/31/13.
//  Copyright (c) 2013 Landi 联迪. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol CommDownloadCallback <NSObject>
@required
-(void)onDownloadComplete;
-(void)onDownloadProgress:(unsigned int)current totalProgress:(unsigned int)total;
-(void)onDownloadError:(int)code;

@end
