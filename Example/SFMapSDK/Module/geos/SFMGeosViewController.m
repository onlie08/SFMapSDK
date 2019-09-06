//
//  SFMGeosViewController.m
//  SFMapSDK_Example
//
//  Created by 龚聪(Cong Gong)-顺丰科技 on 2019/9/3.
//  Copyright © 2019年 ggggggc. All rights reserved.
//

#import "SFMGeosViewController.h"
#import <SFMapSDK/LMKMapKit.h>
#import "SFCircleTapDrawView.h"
#import "SFMGeosAnnotation.h"

@interface SFMGeosViewController ()<LMKMapViewDelegate>

@property(nonatomic,strong)LMKMapView *mapView;

@property(nonatomic,strong)NSMutableArray *annos;
//画圈按钮
@property(nonatomic,strong)UIButton *startCircleBtn; //开始画圈
@property(nonatomic,strong)UIButton *removeCircleBtn; //清除圈
@property(nonatomic,strong)SFCircleTapDrawView *circleView; //画圈视图

@end

@implementation SFMGeosViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [UIColor whiteColor];
    self.title = @"几何绘制";
    
    [self.view addSubview:self.mapView];
    
    [self.view addSubview:self.circleView];
    [self.view addSubview:self.startCircleBtn];
    [self.view addSubview:self.removeCircleBtn];
    
    //添加几个标注上去
    [self addSomeAnnos];
}

- (void)addSomeAnnos{
    CLLocationCoordinate2D coor = CLLocationCoordinate2DMake(30.420322, 114.43655);
    
    self.annos = [NSMutableArray array];
    //这里是测试数据
    for (NSInteger i = 0; i < 10; i++) {
        //    for (NSInteger i = 0; i < 1; i++) {
        double lat =  (arc4random() % 100) * 0.001f;
        double lon =  (arc4random() % 100) * 0.001f;
        
        CLLocationCoordinate2D coordinate = CLLocationCoordinate2DMake(coor.latitude + lat, coor.longitude + lon);
        SFMGeosAnnotation *anno = [[SFMGeosAnnotation alloc] init];
        anno.coordinate = coordinate;

        [self.annos addObject:anno];
    }
    [self.mapView addAnnotations:self.annos];
    [self.mapView showAnnotations:self.annos animated:YES];
}

#pragma mark - 画圈

- (void)startDrawCircle{
    self.circleView.hidden = NO;
    self.startCircleBtn.selected = YES;
}

- (void)removeCircle{
    self.circleView.hidden = YES;
    self.startCircleBtn.selected = NO;
    [self.circleView cleanCircle];
}

- (void)drawEndCircle:(NSArray *)screenPoints{
    //拿到所有的点，转换成坐标点
    int count = (int)screenPoints.count;
    CGPoint polygons[count];

    for (int i = 0; i < screenPoints.count; i ++) {
        CGPoint point = [screenPoints[i] CGPointValue];
        polygons[i] = point;
    }

    for (SFMGeosAnnotation *item in self.annos) {

        CGPoint itemPoint = [self.mapView convertCoordinate:item.coordinate toPointToView:nil];
//        NSLog(@"itemPoint:%f  %f",itemPoint.x,itemPoint.y);
        //做个偏移+y轴反转，将计算标准点偏移到标注底部，便于画圈准确判断（这里建议根据实际情况来偏移）
        itemPoint = CGPointMake(itemPoint.x + 2, self.mapView.frame.size.height - itemPoint.y + 8);
        //点画在图层上测试
        //        self.circleView.itemPoint = itemPoint;
        item.isInCircle = [self isPolygonContainsPoint:polygons count:count point:itemPoint];
    }
    
    [self.mapView removeAnnotations:self.mapView.annotations];
    [self.mapView addAnnotations:self.annos];
}

/** 对某点正好被包含在多边形的边上具有更好的适用性~ */
- (BOOL)isPolygonContainsPoint:(CGPoint *)polygons count:(int)count point:(CGPoint)p {
    
    bool isIntersectOnSection = false;
    
    int nCross = 0;
    for (int i = 0; i < count; ++ i) {
        CGPoint p1 = polygons[i];
        CGPoint p2 = polygons[(i + 1) % count];
        
        // 求解 y=p.y 与 p1 p2 的交点
        if (p1.y == p2.y) {   // p1p2 与 y=p0.y平行
            continue;
        }
        if (p.y < fminf(p1.y, p2.y)) { // 交点在p1p2延长线上
            continue;
        }
        if (p.y > fmaxf(p1.y, p2.y)) { // 交点在p1p2延长线上
            continue;
        }
        // 求交点的 X 坐标
        double x = (double)(p.y-p1.y)*(double)(p2.x-p1.x)/(double)(p2.y-p1.y)+p1.x;
        
        /** added on 2011.10.02.15.21，是否正好相交在边上~ */
        //        NSLog(@" —— x=%f, p.x=%f", x, p.x);
        if (fabs(x - p.x) < 10e-4) {
            //            NSLog(@"点正好相交在多边形的边上~");
            isIntersectOnSection = true;
            break;
        }
        if (x > p.x) { // 只统计单边交点
            nCross ++;
        }
    }
    if(isIntersectOnSection || nCross%2==1) {    // 单边交点为偶数，点在多边形之外
        return YES;
    } else {
        return NO;
    }
}

#pragma mark - LMKMapViewDelegate

// 根据anntation生成对应的View
- (LMKAnnotationView *)mapView:(LMKMapView *)mapView viewForAnnotation:(id <LMKAnnotation>)annotation {
    
    SFMGeosAnnotation *geosAnno = (SFMGeosAnnotation*)annotation;
    LMKPinAnnotationView *annotationView = [[LMKPinAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:SFMGeosAnnoIdentifier];
    annotationView.pinColor = LMKPinAnnotationColorRed;
    if(geosAnno.isInCircle){
        annotationView.pinColor = LMKPinAnnotationColorYellow;
    }
    [annotationView setBounds:CGRectMake(0, 0, 22, 22)];
    annotationView.draggable = YES;
    annotationView.annotation = annotation;
    annotationView.canShowCallout = YES;
    return annotationView;
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

- (UIButton *)startCircleBtn{
    if(!_startCircleBtn){
        _startCircleBtn = [[UIButton alloc] initWithFrame:CGRectMake(20, SFMAP_SCREEN_HEIGHT - 60, 80, 40)];
        _startCircleBtn.backgroundColor = [UIColor blackColor];
        _startCircleBtn.alpha = 0.8f;
        [_startCircleBtn setTitle:@"开始画圈" forState:UIControlStateNormal];
        [_startCircleBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [_startCircleBtn setTitleColor:[UIColor redColor] forState:UIControlStateSelected];
        [_startCircleBtn addTarget:self action:@selector(startDrawCircle) forControlEvents:UIControlEventTouchUpInside];
    }
    return _startCircleBtn;
}

- (UIButton *)removeCircleBtn{
    if(!_removeCircleBtn){
        _removeCircleBtn = [[UIButton alloc] initWithFrame:CGRectMake(SFMAP_SCREEN_WIDTH - 100, SFMAP_SCREEN_HEIGHT - 60, 80, 40)];
        _removeCircleBtn.backgroundColor = [UIColor blackColor];
        _removeCircleBtn.alpha = 0.8f;
        [_removeCircleBtn setTitle:@"清除画圈" forState:UIControlStateNormal];
        [_removeCircleBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [_removeCircleBtn addTarget:self action:@selector(removeCircle) forControlEvents:UIControlEventTouchUpInside];
    }
    return _removeCircleBtn;
}

- (SFCircleTapDrawView *)circleView{
    if(!_circleView){
        _circleView = [[SFCircleTapDrawView alloc] initWithFrame:self.mapView.frame];
        _circleView.backgroundColor = [UIColor clearColor];
        _circleView.hidden = YES;
        
        __weak typeof(self) weakSelf = self;
        _circleView.endCircleBlock = ^(NSArray *screenPoints) {
            [weakSelf drawEndCircle:screenPoints];
        };
    }
    return _circleView;
}

@end
