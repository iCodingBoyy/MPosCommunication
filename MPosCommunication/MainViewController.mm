//
//  MainViewController.m
//  MPosCommunication
//
//  Created by 马远征 on 14-3-25.
//  Copyright (c) 2014年 马远征. All rights reserved.
//

#import "MainViewController.h"

@interface MainViewController () <DeviceSearchListener,CommunicationCallBack>
{
    
}
@property (nonatomic, strong) DeviceInfo *deviceInfo;
@end

@implementation MainViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self)
    {
        
    }
    return self;
}

- (void)loadView
{
    [super loadView];
    UIView *contentView = [[UIView alloc]initWithFrame:[[UIScreen mainScreen]applicationFrame]];
    contentView.backgroundColor = [UIColor clearColor];
    self.view = contentView;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self startSearchDevice];
}

- (void)startSearchDevice
{
    int status =  [CommunicationManagerBase searchDevices:self
                                        detectAudioDevice:NO
                                          detectBluetooth:YES
                                                  timeout:60];
    if (status == 0)
    {
        NSLog(@"--------phone start to discover device----");
    }
    if (status == -1)
    {
        NSLog(@"--------phone don’t support Bluetooth----");
    }
    if (status == -2)
    {
        NSLog(@"--------phone has not power on Bluetooth----");
    }
    if (status == -3)
    {
        NSLog(@"--------phone has error when startDiscovery Bluetooth Device----");
    }
}

-(void) discoverOneDevice:(DeviceInfo*)devInfo
{
    self.deviceInfo = devInfo;
    NSLog(@"--------devInfo----%@,%@",[devInfo getName],[devInfo getIdentifier]);
    DeviceCommunicationChannel channel = [devInfo getDevChannel];
    
    NSLog(@"----devChannel---%d",channel);
    
    int status =  [[CommunicationManagerBase sharedInstance:channel] openDevice:[devInfo getIdentifier] cb:self mode:DUPLEX];
    if (status == 0)
    {
        NSLog(@"---0 represent setup connection success,--");
        if ([[CommunicationManagerBase sharedInstance:channel]isConnected])
        {
            Byte byte[10] = {0x00,0xe1,0xe2,0x1a,0x2b,0xcc,0xe0};
            NSData *data = [NSData dataWithBytes:&byte length:sizeof(byte)];
            [[CommunicationManagerBase sharedInstance:channel]exchangeData:data timeout:30 cb:self];
        }
        else
        {
            NSLog(@"---蓝牙设备未连接--");
        }
        
    }
    if (status == -1)
    {
        NSLog(@"----1 represent the address is Illegal,--");
    }
    if (status == -2)
    {
        NSLog(@"----2 represent setup connection failed.--");
    }
    if (status == -4)
    {
        NSLog(@"----4 phone don’t support Bluetooth,--");
    }
    if (status == -5)
    {
        NSLog(@"----5 phone has not power on Bluetooth,--");
    }
    if (status == -6)
    {
        NSLog(@"----6 phone has unknown error.--");
    }
    
}

-(void) discoverComplete
{
     NSLog(@"--------discoverComplete----");
}

-(void)onSendOK
{
    NSLog(@"--------onSendOK----");
}

-(void)onReceive:(NSData*)data
{
    NSLog(@"--------onReceive----%@",data);
}
-(void)onTimeout
{
    NSLog(@"--------onTimeout----");
}

-(void)onError:(NSInteger)code message:(NSString*)msg
{
    NSLog(@"--------onError----%d:%@",code,msg);
    if (code == 8)
    {
        [[CommunicationManagerBase sharedInstance:BLUETOOTH]closeResource];
//        [[CommunicationManagerBase sharedInstance:BLUETOOTH]cancelExchange];
//        [[CommunicationManagerBase sharedInstance:BLUETOOTH]closeDevice];
//        [self discoverOneDevice:self.deviceInfo];
    }
}

-(void)onProgress:(NSData*)data
{
    NSLog(@"--------onProgress----%@",data);
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
