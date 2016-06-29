//
//  MainViewController.h
//  Bluno_test
//
//  Created by roberthsu on 2016/6/4.
//  Copyright © 2016年 roberthsu. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "DFBlunoManager.h"


@interface MainViewController : UITableViewController<DFBlunoDelegate>
@property(strong,nonatomic) DFBlunoManager *blunoManager;
@property(nonatomic,strong) NSMutableArray *aryDevices;
@property(nonatomic,strong) DFBlunoDevice *blunoDev;
@property(nonatomic,strong) NSString *customBlunoName;
@end
