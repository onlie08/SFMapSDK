//
//  SFMTileViewController.m
//  SFMapSDK_Example
//
//  Created by 龚聪(Cong Gong)-顺丰科技 on 2019/9/6.
//  Copyright © 2019年 ggggggc. All rights reserved.
//

#import "SFMTileViewController.h"
#import <SFMapSDK/LMKMapKit.h>

@interface SFMTileViewController ()<LMKMapViewDelegate>

@property(nonatomic,strong)LMKMapView *mapView;

@end

@implementation SFMTileViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.view.backgroundColor = [UIColor whiteColor];
    self.title = @"栅格图层";
    
    [self.view addSubview:self.mapView];
    
    [self addTileOverlay];
}

//添加栅格图层
- (void)addTileOverlay{
    [self.mapView setCenterCoordinate:CLLocationCoordinate2DMake(30.420322, 114.43655)];
    
    LMKTileOverlay *tileOverlay = [[LMKTileOverlay alloc] initWithURLTemplate:@"http://193.112.234.240:8090/geoserver/wms?service=WMS&version=1.1.0&request=GetMap&layers=oculi:waibu-china-roadlmarking&styles=&bbox={bbox}&width=256&height=256&srs=EPSG:4326&format=image/png&TRANSPARENT=TRUE"];
    //urlTile的可渲染区域，默认世界范围
    tileOverlay.boundingMapRect = LMKMapRectWorld;
    tileOverlay.maximumZ = 21;
    tileOverlay.minimumZ = 3;
    [self.mapView addOverlay:tileOverlay];
}

#pragma mark - LMKMapViewDelegate

- (LMKOverlayView *)mapView:(LMKMapView *)mapView viewForOverlay:(id<LMKOverlay>)overlay{
    if([overlay isKindOfClass:[LMKTileOverlay class]]){
        LMKTileOverlayView *view = [[LMKTileOverlayView alloc] initWithTileOverlay:(LMKTileOverlay *)overlay];
        return view;
    }
    return nil;
}

#pragma mark - lazyload

- (LMKMapView *)mapView{
    if(!_mapView){
        _mapView = [[LMKMapView alloc] initWithFrame:CGRectMake(0, SFMAP_NAVIBAR_HEIGHT, SFMAP_SCREEN_WIDTH, SFMAP_SCREEN_HEIGHT-SFMAP_NAVIBAR_HEIGHT)];
        _mapView.delegate = self;
        _mapView.showsUserLocation = YES;
        _mapView.showsLogo = YES;
        _mapView.mapType = LMKMapTypeStandardDay;
    }
    return _mapView;
}

@end
