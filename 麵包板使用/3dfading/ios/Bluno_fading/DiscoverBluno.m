//
//  DiscoverBluno.m
//  Bluno_test
//
//  Created by roberthsu on 2016/6/12.
//  Copyright © 2016年 roberthsu. All rights reserved.
//

#import "DiscoverBluno.h"
#define robert_bluno_test @"1F222DBB-198F-77DD-325D-7251D9C3AE28"
#define robert_bluno_home @"4500EECD-DD02-2D1A-5DDF-1847B50E0456"

@interface DiscoverBluno ()

@end

@implementation DiscoverBluno

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
    
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
}

-(void)reloadData{
    [self.tableView reloadData];
}

#pragma mark - Table view data source


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
   
    return self.aryDevices.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView
         cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cell1" forIndexPath:indexPath];
    DFBlunoDevice *blunoDevice = self.aryDevices[indexPath.row];
    if ([blunoDevice.identifier isEqualToString:robert_bluno_test]){
        cell.textLabel.text = @"RobertBlunoTest";
        cell.detailTextLabel.text = blunoDevice.identifier;
        return cell;
    }
    
    if ([blunoDevice.identifier isEqualToString:robert_bluno_home]){
        cell.textLabel.text = @"RobertBlunoHome";
        cell.detailTextLabel.text = blunoDevice.identifier;
        return cell;
    }
    
    cell.textLabel.text = @"其它人的Bluno";
    
    cell.detailTextLabel.text = blunoDevice.identifier;
    cell.userInteractionEnabled = false;
    return cell;
}

#pragma mark- TableView Delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    DFBlunoDevice *device = [self.aryDevices objectAtIndex:indexPath.row];
    UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
    NSString *blunoName = cell.textLabel.text;
    self.selectedDevice(device,blunoName);
    [self.navigationController popViewControllerAnimated:true];
}


@end
