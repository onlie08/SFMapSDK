//
//  SFMGeoCodeViewController.m
//  SFMapSDK_Example
//
//  Created by 龚聪(Cong Gong)-顺丰科技 on 2019/9/3.
//  Copyright © 2019年 ggggggc. All rights reserved.
//

#import "SFMGeoCodeViewController.h"
#import <SFMapSDK/LMKMapKit.h>
#import <SFMapSDK/LMKGeoCodeAPI.h>
#import "SFMGeoCodeAnnotation.h"

@interface SFMGeoCodeViewController ()<LMKMapViewDelegate>

@property(nonatomic,strong)LMKMapView *mapView;

//输入框
@property(nonatomic,strong)UITextField *geoCodeTxt;     //地理编码
@property(nonatomic,strong)UIButton *geoCodeBtn;     //地理编码按钮

@property(nonatomic,strong)UITextField *regeoCodeTxt;   //逆地理编码
@property(nonatomic,strong)UIButton *regeoCodeBtn;     //逆地理编码按钮

//地理编码API
@property(nonatomic,strong)LMKGeoCodeAPI *geoCodeAPI;

@end

@implementation SFMGeoCodeViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [UIColor whiteColor];
    self.title = @"地理编码";
    //地理编码
    self.geoCodeAPI = [[LMKGeoCodeAPI alloc] init];
    
    [self.view addSubview:self.mapView];
    [self.view addSubview:self.geoCodeTxt];
    [self.view addSubview:self.geoCodeBtn];
    [self.view addSubview:self.regeoCodeTxt];
    [self.view addSubview:self.regeoCodeBtn];
}

#pragma mark 按钮方法

- (void)startGeoCode{
    //地理编码
    if(!self.geoCodeTxt.text.length){
        NSLog(@"请输入地址");
        return;
    }
    //    LMKGeoCodeParam *param = [LMKGeoCodeParam paramWithAddress:@"湖北省武汉市光谷金融港B14栋"];
    LMKGeoCodeParam *param = [LMKGeoCodeParam paramWithAddress:self.geoCodeTxt.text];
    
    __weak typeof(self) weakSelf = self;
    [self.geoCodeAPI LMKGeocodeWithParam:param callBack:^(id data, NSError *error) {
        NSLog(@"data:%@",data);
        if(error){
            NSLog(@"error:%@",error);
            return ;
        }
        NSDictionary *resultDict = data[@"result"];
        //展示在地图上
        SFMGeoCodeAnnotation *anno = [[SFMGeoCodeAnnotation alloc] init];
        anno.coordinate = CLLocationCoordinate2DMake([resultDict[@"ycoord"] floatValue], [resultDict[@"xcoord"] floatValue]);
        anno.title = resultDict[@"src_address"];
        
        [weakSelf.mapView removeAnnotations:weakSelf.mapView.annotations];
        [weakSelf.mapView addAnnotation:anno];
        [weakSelf.mapView showAnnotations:@[anno] animated:YES];
    }];
}

- (void)startReGeoCode{
    //逆地理编码
    NSString *regeoStr = self.regeoCodeTxt.text;
    NSArray *arr = [regeoStr componentsSeparatedByString:@" "];
    if(arr.count != 2){
        NSLog(@"请输入正确的经纬度");
        return;
    }
    
    LMKReGeoCodeParam *reparam = [LMKReGeoCodeParam paramWithPoint:[LMKGeoPoint locationWithLatitude:[arr[1] floatValue] longitude:[arr[0] floatValue]]];
    
    __weak typeof(self) weakSelf = self;
    [self.geoCodeAPI LMKReGeocodeWithParam:reparam callBack:^(id data, NSError *error) {
        NSLog(@"data:%@",data);
        if(error){
            NSLog(@"error:%@",error);
            return ;
        }
        NSDictionary *resultDict = data[@"result"];
       
        //展示在地图上
        SFMGeoCodeAnnotation *anno = [[SFMGeoCodeAnnotation alloc] init];
        anno.coordinate = CLLocationCoordinate2DMake([resultDict[@"my_y"] floatValue], [resultDict[@"my_x"] floatValue]);
        anno.title = resultDict[@"name"];

        [weakSelf.mapView removeAnnotations:weakSelf.mapView.annotations];
        [weakSelf.mapView addAnnotation:anno];
        [weakSelf.mapView showAnnotations:@[anno] animated:YES];
    }];
}

#pragma mark - LMKMapViewDelegate

// 根据anntation生成对应的View
- (LMKAnnotationView *)mapView:(LMKMapView *)mapView viewForAnnotation:(id <LMKAnnotation>)annotation {
    
//    SFMGeoCodeAnnotation *cluster = (SFMGeoCodeAnnotation*)annotation;
    LMKPinAnnotationView *annotationView = [[LMKPinAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:SFMGeoCodeAnnoIdentifier];
    annotationView.pinColor = LMKPinAnnotationColorRed;
    
//    UILabel *annotationLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 22, 22)];
//    annotationLabel.textColor = [UIColor whiteColor];
//    annotationLabel.font = [UIFont systemFontOfSize:11];
//    annotationLabel.textAlignment = NSTextAlignmentCenter;
//    annotationLabel.hidden = NO;
//    annotationLabel.text = @"1";
//    annotationLabel.backgroundColor = [UIColor greenColor];
//    annotationView.alpha = 0.8;
//    [annotationView addSubview:annotationLabel];

    [annotationView setBounds:CGRectMake(0, 0, 22, 22)];
    annotationView.draggable = YES;
    annotationView.annotation = annotation;
    annotationView.canShowCallout = YES;
    return annotationView;
}

- (void)mapView:(LMKMapView*)mapView didSelectAnnotationView:(LMKAnnotationView*)view{
    if ([view isKindOfClass:[LMKPinAnnotationView class]]) {
        
    }
}

- (void)mapView:(LMKMapView *)mapView didLongPressedAtCoordinate:(CLLocationCoordinate2D)coordinate{
    //长按地图
    self.regeoCodeTxt.text = [NSString stringWithFormat:@"%f %f",coordinate.longitude,coordinate.latitude];
    [self startReGeoCode];
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

- (UITextField *)geoCodeTxt{
    if(!_geoCodeTxt){
        _geoCodeTxt = [[UITextField alloc] initWithFrame:CGRectMake(20, SFMAP_NAVIBAR_HEIGHT + 20, SFMAP_SCREEN_WIDTH - 20 - 90 , 44)];
        _geoCodeTxt.backgroundColor = [UIColor whiteColor];
        _geoCodeTxt.placeholder = @"请输入地址";
    }
    return _geoCodeTxt;
}
- (UIButton *)geoCodeBtn{
    if(!_geoCodeBtn){
        _geoCodeBtn = [[UIButton alloc] initWithFrame:CGRectMake(CGRectGetMaxX(self.geoCodeTxt.frame) + 10, CGRectGetMinY(self.geoCodeTxt.frame), 70, 44)];
        _geoCodeBtn.backgroundColor = [UIColor grayColor];
        [_geoCodeBtn setTitle:@"编码" forState:UIControlStateNormal];
        [_geoCodeBtn addTarget:self action:@selector(startGeoCode) forControlEvents:UIControlEventTouchUpInside];
    }
    return _geoCodeBtn;
}

- (UITextField *)regeoCodeTxt{
    if(!_regeoCodeTxt){
        _regeoCodeTxt = [[UITextField alloc] initWithFrame:CGRectMake(CGRectGetMinX(self.geoCodeTxt.frame), CGRectGetMaxY(self.geoCodeTxt.frame) + 20, CGRectGetWidth(self.geoCodeTxt.frame) , CGRectGetHeight(self.geoCodeTxt.frame))];
        _regeoCodeTxt.backgroundColor = [UIColor whiteColor];
        _regeoCodeTxt.placeholder = @"请输入经纬度，或长按地图";
    }
    return _regeoCodeTxt;
}
- (UIButton *)regeoCodeBtn{
    if(!_regeoCodeBtn){
        _regeoCodeBtn = [[UIButton alloc] initWithFrame:CGRectMake(CGRectGetMaxX(self.regeoCodeTxt.frame) + 10, CGRectGetMinY(self.regeoCodeTxt.frame), 70, 44)];
        _regeoCodeBtn.backgroundColor = [UIColor grayColor];
        [_regeoCodeBtn setTitle:@"逆编码" forState:UIControlStateNormal];
        [_regeoCodeBtn addTarget:self action:@selector(startReGeoCode) forControlEvents:UIControlEventTouchUpInside];
    }
    return _regeoCodeBtn;
}

@end
