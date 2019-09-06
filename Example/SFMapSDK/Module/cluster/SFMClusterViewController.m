//
//  SFMClusterViewController.m
//  SFMapSDK_Example
//
//  Created by 龚聪(Cong Gong)-顺丰科技 on 2019/9/3.
//  Copyright © 2019年 ggggggc. All rights reserved.
//

#import "SFMClusterViewController.h"
#import "SFMQuadItem.h"
#import "SFMClusterAnnotation.h"
#import <SFMapSDK/LMKMapKit.h>
#import <SFMapSDK/LMKClusterManager.h>

#define LMKClusterZoomMin 3       //最小缩放级别
#define LMKClusterZoomMax 21      //最大缩放级别

@interface SFMClusterViewController ()<LMKMapViewDelegate>{
    BOOL _switchFlag;
}

@property(nonatomic,strong)LMKMapView *mapView;

//按钮
@property(nonatomic,strong)UIButton *addClusterBtn; //聚合
@property(nonatomic,strong)UIButton *showAllBtn; //全局展示

@property(nonatomic,strong)LMKUserLocation *userLocation;

///工具
@property (nonatomic, strong) LMKClusterManager *clusterManager;
@property (nonatomic, strong) NSMutableArray *clusterCacheArray;
@property (nonatomic, assign) NSUInteger clusterZoom;
@property (nonatomic, strong) NSMutableArray *dataArray;
@property (nonatomic, assign) BOOL clusterIsFirstShow;

@end

@implementation SFMClusterViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [UIColor whiteColor];
    self.title = @"地图聚合";
    
    [self.view addSubview:self.mapView];
    [self.view addSubview:self.addClusterBtn];
    [self.view addSubview:self.showAllBtn];
}

#pragma mark - 定位到中心点，且展示所有聚合点

- (void)showAllDataAndUserCenter{
    [self moveUserCenterAndShowAll:YES];
}

- (void)moveUserCenterAndShowAll:(BOOL)animated{
    
    //所有点以定位点为中心，进行映射
    NSMutableArray *pointArray = [NSMutableArray array];
    
    CLLocationCoordinate2D userLocation = self.userLocation.location.coordinate;
    
    //这里取的所有的点进行包含聚合
    for (SFMQuadItem *item in self.dataArray) {
        LMKMapPoint mapPoint = LMKMapPointForCoordinate(item.coordinate, LMKMapProjectionTypeMercator);
        [pointArray addObject:[NSValue valueWithBytes:&mapPoint objCType:@encode(LMKMapPoint)]];
    }
    LMKMapPoint userMapPoint = LMKMapPointForCoordinate(userLocation, LMKMapProjectionTypeMercator);
    [pointArray addObject:[NSValue valueWithBytes:&userMapPoint objCType:@encode(LMKMapPoint)]];
    
    LMKMapRect mapRect = mapRectForMapPoints(pointArray);
    //开始设置
    [self.mapView setVisibleMapRect:mapRect animated:animated];
}

#pragma mark - 聚类

- (void)loadData{
    
    //    if(self.mapView.annotations.count){
    //        [self.clusterManager clearClusterItems];
    //        NSArray *array = [self.clusterManager getClusters:self.clusterZoom];
    //        NSLog(@"array:%@",array);
    //        [self.mapView removeAnnotations:self.mapView.annotations];
    //        return;
    //    }
    self.clusterCacheArray = [NSMutableArray array];
    for (int i = LMKClusterZoomMin; i <= LMKClusterZoomMax; i ++) {
        [self.clusterCacheArray addObject:[NSMutableArray array]];
    }
    self.dataArray = [NSMutableArray array];
    self.clusterIsFirstShow = NO;
    
    CLLocationCoordinate2D coor = CLLocationCoordinate2DMake(30.420322, 114.43655);
    if(_switchFlag){
        coor = CLLocationCoordinate2DMake(23.117055306, 113.2756);
    }
    _switchFlag = !_switchFlag;
    
    //这里是测试数据
    for (NSInteger i = 0; i < 20; i++) {
        //    for (NSInteger i = 0; i < 1; i++) {
        double lat =  (arc4random() % 100) * 0.001f;
        double lon =  (arc4random() % 100) * 0.001f;
        
        CLLocationCoordinate2D coordinate;
        coordinate = CLLocationCoordinate2DMake(coor.latitude + lat, coor.longitude + lon);
        SFMQuadItem *quadItem = [[SFMQuadItem alloc] init];
        quadItem.coordinate = coordinate;
        quadItem.qid = [NSString stringWithFormat:@"%li",(long)i];
        [self.dataArray addObject:quadItem];
    }
    [self.clusterManager clearClusterItems];
    [self.clusterManager setAnnoDataArray:self.dataArray];
    [self updateClusters];
}

//更新地图等级
- (void)updateZoom:(float)zoomLevel{
    NSInteger newZoom = (NSInteger)zoomLevel;
    if(newZoom != self.clusterZoom){
        self.clusterZoom = newZoom;
        [self updateClusters];
    }
}

- (void)updateClusters {
    
    if(!_mapView){
        return;
    }
    if(!_dataArray.count){
        return;
    }
    
    @synchronized(self.clusterCacheArray) {
        __block NSMutableArray *clusters = [self.clusterCacheArray objectAtIndex:(self.clusterZoom - LMKClusterZoomMin)];
        if (clusters.count > 0) {
            /**
             移除一组标注
             
             @param annotations 要移除的标注数组
             */
            [self.mapView removeAnnotations:_mapView.annotations];
            //            将一组标注添加到当前地图View中
            [self.mapView addAnnotations:clusters];
        } else {
            
            __weak typeof(self) weakSelf = self;
            
            dispatch_async(dispatch_get_global_queue(0, 0), ^{
                ///获取聚合后的标注
                __block NSArray *array = [self.clusterManager getClusters:weakSelf.clusterZoom];
                dispatch_async(dispatch_get_main_queue(), ^{
                    for (LMKCluster *item in array) {
                        SFMClusterAnnotation *annotation = [[SFMClusterAnnotation alloc] init];
                        //设置标注的经纬度坐标
                        annotation.coordinate = item.coordinate;
                        annotation.size = item.size;
                        //设置标注的标题
                        annotation.title = [NSString stringWithFormat:@"我是%ld个", (long)item.size];
                        
                        NSLog(@"annotation.items:%@",item.clusterAnnotationItems);
                        
                        [clusters addObject:annotation];
                    }
                    /**
                     移除一组标注
                     
                     @param annotations 要移除的标注数组
                     */
                    [weakSelf.mapView removeAnnotations:weakSelf.mapView.annotations];
                    [weakSelf.mapView addAnnotations:clusters];
                    //将一组标注添加到当前地图View中
                    
                    if(!weakSelf.clusterIsFirstShow){
                        weakSelf.clusterIsFirstShow = YES;
                        [weakSelf.mapView showAnnotations:clusters animated:YES];
                    }
                });
            });
        }
    }
}

#pragma mark - LMKMapViewDelegate

- (void)mapView:(LMKMapView *)mapView didUpdateUserLocation:(LMKUserLocation *)userLocation updatingLocation:(BOOL)updatingLocation{
    
//    CLLocationCoordinate2D location = userLocation.location.coordinate;
    self.userLocation = userLocation;
}

- (void)mapViewZoomingOrMoveing:(LMKMapView *)mapView{
    [self updateZoom:mapView.zoomLevel];
}
- (void)mapViewZoomOrMoveFinish:(LMKMapView *)mapView{
    [self updateZoom:mapView.zoomLevel];
    [self updateClusters];
}

// 根据anntation生成对应的View
- (LMKAnnotationView *)mapView:(LMKMapView *)mapView viewForAnnotation:(id <LMKAnnotation>)annotation {
    
    SFMClusterAnnotation *cluster = (SFMClusterAnnotation*)annotation;
    LMKPinAnnotationView *annotationView = [[LMKPinAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:SFMClusterAnnoIdentifier];
    if(cluster.isCircleInner){
        annotationView.pinColor = LMKPinAnnotationColorRed;
    }else{
        annotationView.pinColor = LMKPinAnnotationColorDefault;
    }
    
    UILabel *annotationLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 22, 22)];
    annotationLabel.textColor = [UIColor whiteColor];
    annotationLabel.font = [UIFont systemFontOfSize:11];
    annotationLabel.textAlignment = NSTextAlignmentCenter;
    annotationLabel.hidden = NO;
    annotationLabel.text = [NSString stringWithFormat:@"%ld", (long)cluster.size];
    annotationLabel.backgroundColor = [UIColor greenColor];
    annotationView.alpha = 0.8;
    [annotationView addSubview:annotationLabel];
    
    if (cluster.size == 1) {
        annotationLabel.hidden = YES;
        //        annotationView.pinColor = LMKPinAnnotationColorRed;
    }
    if (cluster.size > 20) {
        annotationLabel.backgroundColor = [UIColor redColor];
    } else if (cluster.size > 10) {
        annotationLabel.backgroundColor = [UIColor purpleColor];
    } else if (cluster.size > 5) {
        annotationLabel.backgroundColor = [UIColor blueColor];
    } else {
        annotationLabel.backgroundColor = [UIColor greenColor];
    }
    [annotationView setBounds:CGRectMake(0, 0, 22, 22)];
    annotationView.draggable = YES;
    annotationView.annotation = annotation;
    annotationView.canShowCallout = YES;
    return annotationView;
}


/**
 当点击annotationView时
 
 @param mapView 地图View
 @param view 泡泡所属的annotationView
 */
- (void)mapView:(LMKMapView*)mapView didSelectAnnotationView:(LMKAnnotationView*)view{
    if ([view isKindOfClass:[LMKPinAnnotationView class]]) {
        SFMClusterAnnotation *clusterAnnotation = (SFMClusterAnnotation *)view.annotation;
        if (clusterAnnotation.size > 1) {
            /**
             设定地图中心点坐标
             @param coordinate 要设定的地图中心点坐标，用经纬度表示
             @param animated 是否采用动画效果
             */
            
            [mapView setCenterCoordinate:view.annotation.coordinate];
            /**
             放大一级比例尺
             
             @return 是否成功
             */
            [mapView setZoomLevel:(_mapView.zoomLevel++)];
        }
    }
}


#pragma mark - lazyload

- (LMKClusterManager *)clusterManager{
    if(!_clusterManager){
        _clusterManager = [[LMKClusterManager alloc] init];
        //        _clusterManager.dpDistance = 400;
        _clusterManager.zoomMin = LMKClusterZoomMin;
        _clusterManager.zoomMax = LMKClusterZoomMax;
    }
    return _clusterManager;
}

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

- (UIButton *)addClusterBtn{
    if(!_addClusterBtn){
        _addClusterBtn = [[UIButton alloc] initWithFrame:CGRectMake(SFMAP_SCREEN_WIDTH - 100, SFMAP_NAVIBAR_HEIGHT + 20, 80, 40)];
        _addClusterBtn.backgroundColor = [UIColor blackColor];
        _addClusterBtn.alpha = 0.8f;
        [_addClusterBtn setTitle:@"聚类" forState:UIControlStateNormal];
        [_addClusterBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [_addClusterBtn addTarget:self action:@selector(loadData) forControlEvents:UIControlEventTouchUpInside];
    }
    return _addClusterBtn;
}
- (UIButton *)showAllBtn{
    if(!_showAllBtn){
        _showAllBtn = [[UIButton alloc] initWithFrame:CGRectMake(SFMAP_SCREEN_WIDTH - 100, SFMAP_NAVIBAR_HEIGHT + 20 + 60, 80, 40)];
        _showAllBtn.backgroundColor = [UIColor blackColor];
        _showAllBtn.alpha = 0.8f;
        [_showAllBtn setTitle:@"展示" forState:UIControlStateNormal];
        [_showAllBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [_showAllBtn addTarget:self action:@selector(showAllDataAndUserCenter) forControlEvents:UIControlEventTouchUpInside];
    }
    return _showAllBtn;
}

@end
