//
//  MainViewController.m
//  Bluno_test
//
//  Created by roberthsu on 2016/6/4.
//  Copyright © 2016年 roberthsu. All rights reserved.
//

#import "MainViewController.h"
#import "DiscoverBluno.h"

@interface MainViewController ()

@property(nonatomic,strong) DiscoverBluno *discoverBluno;
@property(nonatomic,strong) NSTimer *timer;
@property (weak, nonatomic) IBOutlet UILabel *temperatureLabel;
@end

@implementation MainViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.aryDevices = [[NSMutableArray alloc] init];
    self.title = @"尚未連線";
    
    //初始化介面
    self.view.alpha = 0.5;
    self.view.userInteractionEnabled = false;
    
}

-(void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender{
    if ([segue.identifier isEqualToString:@"goDiscover"]){
        self.discoverBluno = (DiscoverBluno *)segue.destinationViewController;
        self.discoverBluno.aryDevices = self.aryDevices;
        __weak MainViewController* mySelf = self;
        self.discoverBluno.selectedDevice = ^(DFBlunoDevice *selectedBluno,NSString *blunoName){
            mySelf.customBlunoName = blunoName;
            
            if (mySelf.blunoDev == nil){
                mySelf.blunoDev = selectedBluno;
                [mySelf.blunoManager connectToDevice:mySelf.blunoDev];
            }else if ([selectedBluno isEqual:mySelf.blunoDev]){
                if (!mySelf.blunoDev.bReadyToWrite){
                    [mySelf.blunoManager connectToDevice:mySelf.blunoDev];
                }
            }else{
                if (mySelf.blunoDev.bReadyToWrite){
                    [mySelf.blunoManager disconnectToDevice:mySelf.blunoDev];
                    mySelf.blunoDev = nil;
                }
                
                [mySelf.blunoManager connectToDevice:selectedBluno];
            }
            
        };
    }
}

- (IBAction)actionSearch:(UIBarButtonItem *)sender {
    if ([sender.title isEqualToString:@"搜尋Device"]){
        [self performSegueWithIdentifier:@"goDiscover" sender:nil];
        self.blunoManager = [DFBlunoManager sharedInstance];
        self.blunoManager.delegate = self;
        
        [self.aryDevices removeAllObjects];
        [self.blunoManager scan];
    }else{
        
        //send iphone中斷連線
        //送出iphone識別99
        unsigned char action = 99;
        [self sendToArduino:action];
        //送出功能識別
        action = 0x02;//連線功能
        [self sendToArduino:action];
        //送出功能值
        action = 0x02;//中斷連線
        [self sendToArduino:action];
        //送出結束值
        action = 100;
        [self sendToArduino:action];
        
        self.timer = [NSTimer timerWithTimeInterval:0.5 target:self selector:@selector(stopconnected:) userInfo:nil repeats:false];
        [self.timer fire];
        
    }
    
    
}

-(void)stopconnected:(NSTimer*)time{
   [self.blunoManager disconnectToDevice:self.blunoDev];
    self.timer = nil;
}


-(void)sendToArduino:(unsigned char)action{
    NSData *actionData = [NSData dataWithBytes:&action length:sizeof(action)];
    [self.blunoManager writeDataToDevice:actionData Device:self.blunoDev];
}


#pragma mark - DFBlunoManagerDelegate
-(void)bleDidUpdateState:(BOOL)bleSupported{
    if(bleSupported){
        [self.blunoManager scan];
    }
}

-(void)didDiscoverDevice:(DFBlunoDevice*)dev{
    
    BOOL bRepeat = NO;
    for (DFBlunoDevice* bleDevice in self.aryDevices)
    {
        if ([bleDevice isEqual:dev])
        {
            bRepeat = YES;
            break;
        }
    }
    if (!bRepeat)
    {
        [self.aryDevices addObject:dev];
    }
    
    [self.discoverBluno reloadData];
    
 }

-(void)readyToCommunicate:(DFBlunoDevice*)dev{
    self.blunoDev = dev;
    self.title = [NSString stringWithFormat:@"%@平台連線中",self.customBlunoName];
    //介面
    self.view.alpha = 1.0;
    self.view.userInteractionEnabled = YES;
    [self.navigationItem.rightBarButtonItem setTitle:@"中斷連線"];
    
    //send iphone連線成功
    //送出iphone識別99
    unsigned char action = 99;
    [self sendToArduino:action];
    //送出功能識別
    action = 0x02;//連線功能
    [self sendToArduino:action];
    //送出功能值
    action = 0x01;//連線成功
    [self sendToArduino:action];
    //送出結束值
    action = 100;
    [self sendToArduino:action];
}

-(void)didDisconnectDevice:(DFBlunoDevice*)dev{
    self.title = @"尚未連線";
    [self.navigationItem.rightBarButtonItem setTitle:@"搜尋Device"];
    //介面
    self.view.alpha = 0.5;
    self.view.userInteractionEnabled = false;
    self.temperatureLabel.text = @"0";
}


-(void)didWriteData:(DFBlunoDevice*)dev{
    
}


-(void)didReceiveData:(NSData*)data Device:(DFBlunoDevice*)dev{
    char *action = (char*)[data bytes];
    NSString *actionString = [NSString stringWithCString:action encoding:NSASCIIStringEncoding];
    NSLog(@"%@",actionString);
    self.temperatureLabel.text = actionString;
    
}




@end
