//
//  SFMMapViewController.m
//  SFMapSDK_Example
//
//  Created by 龚聪(Cong Gong)-顺丰科技 on 2019/9/3.
//  Copyright © 2019年 ggggggc. All rights reserved.
//

#import "SFMMapViewController.h"
#import <SFMapSDK/LMKMapKit.h>

@interface SFMMapViewController ()<LMKMapViewDelegate>{
    BOOL _firstMoveMap;
}

@property(nonatomic,strong)LMKMapView *mapView;

@end

@implementation SFMMapViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    _firstMoveMap = YES;
    
    self.view.backgroundColor = [UIColor whiteColor];
    self.title = @"地图Demo";
    
    [self.view addSubview:self.mapView];
}

#pragma mark - LMKMapViewDelegate

- (void)mapView:(LMKMapView *)mapView didUpdateUserLocation:(LMKUserLocation *)userLocation updatingLocation:(BOOL)updatingLocation{
    
    if(_firstMoveMap){
        _firstMoveMap = NO;
        
        CLLocationCoordinate2D location = userLocation.location.coordinate;
        /*
         火星坐标转换方法
         double lat,lng;
         [[SFMapCO sharedSFMapCO] sfCOLat:location.latitude lng:location.longitude outLat:&lat outLng:&lng];
         */
        [mapView setCenterCoordinate:location animated:NO];
        mapView.zoomLevel = 15;
        
        //        self.userLocation = userLocation;
    }
}

#pragma mark - lazyload

- (LMKMapView *)mapView{
    if(!_mapView){
        _mapView = [[LMKMapView alloc] initWithFrame:CGRectMake(0, SFMAP_NAVIBAR_HEIGHT, SFMAP_SCREEN_WIDTH, SFMAP_SCREEN_HEIGHT-SFMAP_NAVIBAR_HEIGHT)];
        _mapView.delegate = self;
        _mapView.showsUserLocation = YES;
        _mapView.showsLogo = YES;
        _mapView.mapType = LMKMapTypeStandardDay;
        //        _mapView.showsScale = NO;
        
        //        self.map3dView = (XYMap3DView *)[_mapView valueForKey:@"mapView"];
        //        XYMap3DGPSOverlay *gpsOverlay = [self.map3dView.layermanager gpsOverlay];
        //        gpsOverlay.circleColor = [UIColor clearColor];
        //        gpsOverlay.circleBorderColor = [UIColor clearColor];
        
        //        _mapView.showsCompass = NO;
    }
    return _mapView;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
