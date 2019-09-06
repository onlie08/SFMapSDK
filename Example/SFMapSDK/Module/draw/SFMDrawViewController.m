//
//  SFMDrawViewController.m
//  SFMapSDK_Example
//
//  Created by 龚聪(Cong Gong)-顺丰科技 on 2019/9/3.
//  Copyright © 2019年 ggggggc. All rights reserved.
//

#import "SFMDrawViewController.h"
#import <SFMapSDK/LMKMapKit.h>

@interface SFMDrawViewController ()<LMKMapViewDelegate>

@property(nonatomic,strong)LMKMapView *mapView;

//按钮
@property(nonatomic,strong)UIButton *drawLineBtn; //划线按钮
@property(nonatomic,strong)UIButton *drawAreaBtn; //划区域按钮
@property(nonatomic,strong)UIButton *drawCircleBtn; //划圈按钮

@end

@implementation SFMDrawViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.view.backgroundColor = [UIColor whiteColor];
    self.title = @"地图绘制";
    
    [self.view addSubview:self.mapView];
    [self.view addSubview:self.drawLineBtn];
    [self.view addSubview:self.drawAreaBtn];
    [self.view addSubview:self.drawCircleBtn];
}

#pragma mark 按钮方法

- (void)drawLine{
    [self.mapView removeOverlays:self.mapView.overlays];
    
    CLLocationCoordinate2D center = CLLocationCoordinate2DMake(30.420322, 114.43655);
    
    NSUInteger coordianteCount = 2;
    CLLocationCoordinate2D coordinates[coordianteCount];
    for (int i = 0; i < coordianteCount; i++) {
        double lat =  (arc4random() % 100) * 0.001f;
        double lon =  (arc4random() % 100) * 0.001f;
        coordinates[i] = CLLocationCoordinate2DMake(center.latitude + lat, center.longitude + lon);
    }
    LMKPolyline *polyline = [LMKPolyline polylineWithCoordinates:coordinates count:coordianteCount];
    polyline.title = @"_gray";
    [self.mapView addOverlay:polyline];
    
    [self.mapView setCenterCoordinate:center animated:YES];
}

- (void)drawArea{
    [self.mapView removeOverlays:self.mapView.overlays];
    
    CLLocationCoordinate2D center = CLLocationCoordinate2DMake(30.420322, 114.43655);
    
    NSUInteger coordianteCount = 4;
    CLLocationCoordinate2D coordinates[coordianteCount];
    for (int i = 0; i < coordianteCount - 1; i++) {
        double lat =  (arc4random() % 100) * 0.001f;
        double lon =  (arc4random() % 100) * 0.001f;
        coordinates[i] = CLLocationCoordinate2DMake(center.latitude + lat, center.longitude + lon);
    }
    coordinates[coordianteCount - 1] = coordinates[0];
    LMKPolygon *polyline = [LMKPolygon polygonWithCoordinates:coordinates count:coordianteCount];
    [self.mapView addOverlay:polyline];
    
    [self.mapView setCenterCoordinate:center animated:YES];
}

- (void)drawCircle{
    [self.mapView removeOverlays:self.mapView.overlays];
    
    double lat =  (arc4random() % 100) * 0.001f;
    double lon =  (arc4random() % 100) * 0.001f;
    double radius = (arc4random() % 1000) + 1000;
    CLLocationCoordinate2D center = CLLocationCoordinate2DMake(30.420322 + lat, 114.43655 + lon);
    
    LMKCircle *circle = [[LMKCircle alloc] initWithWithCenterCoordinate:center radius:radius];
    [self.mapView addOverlay:circle];
    
    [self.mapView setCenterCoordinate:center animated:YES];
}

#pragma mark - LMKMapViewDelegate

- (LMKOverlayView *)mapView:(LMKMapView *)mapView viewForOverlay:(id<LMKOverlay>)overlay {
    if ([overlay isKindOfClass:[LMKPolyline class]]) {
        //
        LMKPolyline *polyline = (LMKPolyline *)overlay;
        if ([polyline.title hasPrefix:@"_"]) {
            LMKPolylineView *lineView = [[LMKPolylineView alloc] initWithPolyline:polyline];
            lineView.lineWidth = 40;
            
            //颜色填充
//            lineView.fillColor = [UIColor whiteColor];
            
            //图片填充
            [lineView loadStrokeTextureImage:[UIImage imageNamed:[[NSBundle mainBundle] pathForResource:[NSString stringWithFormat:@"line_texture%@",polyline.title] ofType:@"png" inDirectory:@"LDMap.bundle/images"]]];
            return lineView;
        }
    }else if([overlay isKindOfClass:[LMKPolygon class]]){
        LMKPolygon *polygon = (LMKPolygon *)overlay;
        LMKPolygonView *areaView = [[LMKPolygonView alloc] initWithPolygon:polygon];
        areaView.lineWidth = 10;
        areaView.fillColor = [UIColor orangeColor];
        areaView.strokeColor = [UIColor redColor];
        return areaView;
    }else if([overlay isKindOfClass:[LMKCircle class]]){
        LMKCircle *circle = (LMKCircle *)overlay;
        LMKCircleView *circleView = [[LMKCircleView alloc] initWithCircle:circle];
        circleView.lineWidth = 10;
        circleView.fillColor = [UIColor orangeColor];
        circleView.strokeColor = [UIColor redColor];
        return circleView;
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

- (UIButton *)drawLineBtn{
    if(!_drawLineBtn){
        _drawLineBtn = [[UIButton alloc] initWithFrame:CGRectMake(SFMAP_SCREEN_WIDTH - 100, SFMAP_NAVIBAR_HEIGHT + 20, 80, 40)];
        _drawLineBtn.backgroundColor = [UIColor blackColor];
        _drawLineBtn.alpha = 0.8f;
        [_drawLineBtn setTitle:@"划线" forState:UIControlStateNormal];
        [_drawLineBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [_drawLineBtn addTarget:self action:@selector(drawLine) forControlEvents:UIControlEventTouchUpInside];
    }
    return _drawLineBtn;
}

- (UIButton *)drawAreaBtn{
    if(!_drawAreaBtn){
        _drawAreaBtn = [[UIButton alloc] initWithFrame:CGRectMake(SFMAP_SCREEN_WIDTH - 100, SFMAP_NAVIBAR_HEIGHT + 20 + 50, 80, 40)];
        _drawAreaBtn.backgroundColor = [UIColor blackColor];
        _drawAreaBtn.alpha = 0.8f;
        [_drawAreaBtn setTitle:@"划区" forState:UIControlStateNormal];
        [_drawAreaBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [_drawAreaBtn addTarget:self action:@selector(drawArea) forControlEvents:UIControlEventTouchUpInside];
    }
    return _drawAreaBtn;
}

- (UIButton *)drawCircleBtn{
    if(!_drawCircleBtn){
        _drawCircleBtn = [[UIButton alloc] initWithFrame:CGRectMake(SFMAP_SCREEN_WIDTH - 100, SFMAP_NAVIBAR_HEIGHT + 20 + 100, 80, 40)];
        _drawCircleBtn.backgroundColor = [UIColor blackColor];
        _drawCircleBtn.alpha = 0.8f;
        [_drawCircleBtn setTitle:@"划圈" forState:UIControlStateNormal];
        [_drawCircleBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [_drawCircleBtn addTarget:self action:@selector(drawCircle) forControlEvents:UIControlEventTouchUpInside];
    }
    return _drawCircleBtn;
}

@end
