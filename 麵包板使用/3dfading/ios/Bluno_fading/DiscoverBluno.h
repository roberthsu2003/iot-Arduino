//
//  DiscoverBluno.h
//  Bluno_test
//
//  Created by roberthsu on 2016/6/12.
//  Copyright © 2016年 roberthsu. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DFBlunoDevice.h"

@interface DiscoverBluno : UITableViewController
@property(nonatomic,strong) NSArray *aryDevices;
@property(nonatomic,copy) void(^selectedDevice)(DFBlunoDevice *blunoDevice,NSString *blunoName);
-(void)reloadData;
@end
