//
//  SFMViewController.m
//  SFMapSDK
//
//  Created by ggggggc on 09/03/2019.
//  Copyright (c) 2019 ggggggc. All rights reserved.
//

#import "SFMViewController.h"
#import <SFMapSDK/LMKMapKit.h>

@interface SFMViewController ()<UITableViewDelegate,UITableViewDataSource>

@property(nonatomic,strong)UITableView *listView;
@property(nonatomic,strong)NSArray *dataArray;

@end

@implementation SFMViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    self.title = @"地图Demo";
    self.dataArray = @[
                       @"基础地图",
                       @"地图绘制",
                       @"地理编码",
                       @"栅格图层",
                       @"聚合",
                       @"几何",
                       @"调用顺丰地图（定位）"];
    
    [self.view addSubview:self.listView];
}

#pragma mark - UITableViewDelegate & UITableViewDataSource

//确定一个tableView有几个单元格
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return self.dataArray.count;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

//此函数是循环执行的，每次执行后加载一个单元格，直到单元格加载完毕
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    static NSString *cellIdentifier = @"SFMMapViewFuncCell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    if(!cell){
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:cellIdentifier];
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    }
    cell.contentView.backgroundColor = [UIColor whiteColor];
    cell.backgroundColor = [UIColor whiteColor];
    cell.textLabel.text = self.dataArray[indexPath.row];
    cell.textLabel.textColor = [UIColor blackColor];
    cell.textLabel.font = [UIFont systemFontOfSize:18];
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:NO];  //点击后有渐变效果
    
    NSString *vcStr = @"";
    switch (indexPath.row) {
        case 0://基础地图
            vcStr = @"SFMMapViewController";
            break;
        case 1://地图绘制
            vcStr = @"SFMDrawViewController";
            break;
        case 2://地理编码
            vcStr = @"SFMGeoCodeViewController";
            break;
        case 3://栅格图层
            vcStr = @"SFMTileViewController";
            break;
        case 4://聚合
            vcStr = @"SFMClusterViewController";
            break;
        case 5://几何
            vcStr = @"SFMGeosViewController";
            break;
        case 6://调用顺丰地图（定位）
        {
            [self openSFMapAppToLocate];
        }
            break;
        default:
            break;
    }
    Class class = NSClassFromString(vcStr);
    if(!class){
        return;
    }
    UIViewController *obj = (UIViewController *)[[class alloc] init];
    if(![obj isKindOfClass:[UIViewController class]]){
        return;
    }
    [self.navigationController pushViewController:obj animated:YES];
}


//调用顺丰地图定位
- (void)openSFMapAppToLocate{
    /*
     scheme方式
     host：sfmap://com.sfmap.map/map  or  iossfmap://com.sfmap.map/map
     参数：type  ->  -1 定位
     0 驾车
     1 骑行
     2 步行
     x1  ->  经度 longitude
     y1  ->  纬度 latitude
     
     配置：
     1、在info.plist中，添加白名单LSApplicationQueriesSchemes (Array)，数组中添加sfmap、iossfmap
     （或者打开info.plist的source code，添加：
     <key>LSApplicationQueriesSchemes</key>
     <array>
     <string>sfmap</string>
     <string>iossfmap</string>
     </array>
     ）
     */
    NSString *host = @"sfmap://com.sfmap.map/map";      //白名单方式
    //            NSString *host = @"https://fs.pailizhuan.cn/map"; //通用链接
    NSString *param = @"type=-1&y1=30.899188&x1=114.249516&appver=1";
    
    NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"%@?%@",host,param]];
    if ([[UIApplication sharedApplication] canOpenURL:url]) {
        //打开url
        [[UIApplication sharedApplication] openURL:url options:@{} completionHandler:^(BOOL success) {
            if(!success){
                NSLog(@"打开失败");
            }
        }];
    }else{
        NSLog(@"请先安装顺丰地图");
    }
}

#pragma mark - lazyload

- (UITableView *)listView{
    if(!_listView){
        _listView = [[UITableView alloc] initWithFrame:CGRectMake(0, SFMAP_NAVIBAR_HEIGHT, SFMAP_SCREEN_WIDTH, SFMAP_SCREEN_HEIGHT-SFMAP_NAVIBAR_HEIGHT)];
        _listView.backgroundColor = [UIColor whiteColor];
        _listView.delegate = self;
        _listView.dataSource = self;
        _listView.rowHeight = 50;
    }
    return _listView;
}

@end
