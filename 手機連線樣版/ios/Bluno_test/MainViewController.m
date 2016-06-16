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
@property (weak, nonatomic) IBOutlet UIButton *openRedBtn;
@property (weak, nonatomic) IBOutlet UIButton *closeRedBtn;
@property (weak, nonatomic) IBOutlet UISwitch *redStateSwitch;
@property(nonatomic,strong) DiscoverBluno *discoverBluno;
@end

@implementation MainViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.aryDevices = [[NSMutableArray alloc] init];
    self.title = @"尚未連線";
    
    //初始化介面
    self.view.alpha = 0.5;
    self.view.userInteractionEnabled = false;
    self.closeRedBtn.enabled = false;
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
        [self.blunoManager disconnectToDevice:self.blunoDev];
        
    }
    
    
}
- (IBAction)userOpen:(UIButton *)sender {
    //送出iphone識別
    unsigned char action = 99;
    [self sendToArduino:action];
    //送出功能識別
    action = 0x02;
    [self sendToArduino:action];
    //送出功能值
    action = 0x01;
    [self sendToArduino:action];
    //送出結束值
    action = 100;
    [self sendToArduino:action];

}


-(void)sendToArduino:(unsigned char)action{
    NSData *actionData = [NSData dataWithBytes:&action length:sizeof(action)];
    [self.blunoManager writeDataToDevice:actionData Device:self.blunoDev];
}

- (IBAction)userClose:(UIButton *)sender {
    unsigned char action = 0;
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
}

-(void)didDisconnectDevice:(DFBlunoDevice*)dev{
    self.title = @"尚未連線";
    [self.navigationItem.rightBarButtonItem setTitle:@"搜尋Device"];
    //介面
    self.view.alpha = 0.5;
    self.view.userInteractionEnabled = false;
}


-(void)didWriteData:(DFBlunoDevice*)dev{
    
}


-(void)didReceiveData:(NSData*)data Device:(DFBlunoDevice*)dev{
    char *action = (char *)[data bytes];
    NSLog(@"%i",*action);
    /*
    if(*action == 1){
        self.openRedBtn.enabled = NO;
        self.closeRedBtn.enabled = YES;
        [self.redStateSwitch setOn:YES];
    }else if (*action == 0){
        self.openRedBtn.enabled = YES;
        self.closeRedBtn.enabled = NO;
        [self.redStateSwitch setOn:NO];
    }
     */
}




@end
