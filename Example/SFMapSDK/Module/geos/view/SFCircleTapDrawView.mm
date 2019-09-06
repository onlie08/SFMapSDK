//
//  SFCircleTapDrawView.m
//  SFMapDemo
//
//  Created by 龚聪(Cong Gong)-顺丰科技 on 2019/2/20.
//  Copyright © 2019年 龚聪(Cong Gong)-顺丰科技. All rights reserved.
//

#import "SFCircleTapDrawView.h"

#include <map>
#include <vector>
#include <geos_c.h>
#include <geos/geom/Coordinate.h>
#include <geos/geom/Geometry.h>
#include <geos/geom/GeometryFactory.h>
#include <geos/geom/LineString.h>
#include <geos/geom/LinearRing.h>
#include <geos/geom/MultiPolygon.h>
#include <geos/geom/Point.h>
#include <geos/geom/Polygon.h>
#include <geos/geom/CoordinateArraySequenceFactory.h>
#include <geos/operation/polygonize/Polygonizer.h>
#include <geos/simplify/TaggedLinesSimplifier.h>


using namespace geos::geom;
using namespace geos::operation;
using namespace geos::simplify;

using namespace std;

@interface SFCircleTapDrawView()

@property(nonatomic,strong)UIBezierPath *circlePath;
@property(nonatomic,strong)CAShapeLayer *circleLayer;

@property(nonatomic,strong)UIView *pointView;

@property(nonatomic,strong)NSMutableArray *circlePoints;

@end

@implementation SFCircleTapDrawView

- (instancetype)initWithFrame:(CGRect)frame{
    self = [super initWithFrame:frame];
    if(self){
        [self initView];
    }
    return self;
}

- (void)initView{
    [self.layer addSublayer:self.circleLayer];
    [self addSubview:self.pointView];
}

bool valueIsEqual(double x,double x1){
    if(fabs(x - x1) < 1e-6){
        return YES;
    }
    return NO;
}

//判断多点是否在一条直线上
- (BOOL)isCoorsInLine:(NSArray *)array{
    // 判定两矩形是否相交
    NSInteger sizeCount = array.count;
    if(sizeCount < 3){
        //少于3个点，要么是个点，要么是条线
        return YES;
    }
    
    BOOL isLine = YES;
    
    CGPoint p0 = [array[0] CGPointValue];
    CGPoint p1 = [array[1] CGPointValue];
    
    for (int i = 2; i < sizeCount; i ++) {
        CGPoint p = [array[i] CGPointValue];
        
        //先看是否在水平或纵向一条直线上
        if((valueIsEqual(p.x, p0.x) && valueIsEqual(p.x, p1.x)) ||
           (valueIsEqual(p.y, p0.y) && valueIsEqual(p.y, p1.y))){
            continue;
        }
        //再看斜率是否一样
        if((p.y - p0.y)/(p.x - p0.x) == (p.y - p1.y)/(p.x - p1.x)){
            //斜率一样
            continue;
        }
        //已有三个点，不在一条直线上了
        isLine = NO;
        break;
    }
    return isLine;
}
 
- (void)filterPolygon{

    //先检测点集是否只有一个点、或在一条直线上
    if([self isCoorsInLine:self.circlePoints]){
        return;
    }
    
    const GeometryFactory *geometryFactory = GeometryFactory::getDefaultInstance();
    CoordinateArraySequenceFactory seqFactory;
    //    GeometryCollection *multiPolygon = geometryFactory->createGeometryCollection();
    CoordinateSequence *cse = seqFactory.create();
    
    //添加尾点
    [self.circlePoints addObject:[self.circlePoints firstObject]];
    int pointCount = (int)self.circlePoints.count;
    
    for (int i = 0; i < pointCount; i ++) {
        CGPoint point = [self.circlePoints[i] CGPointValue];
        //点集
        Coordinate coor(point.x,point.y);
        cse->add(coor, false);
    }
    //创建线条
    LineString *lineString = geometryFactory->createLineString(cse);
    //取buffer
    Geometry *tempPolygon = lineString->buffer(0.001, 6);
    
    if(tempPolygon != nullptr &&
       (tempPolygon->getGeometryTypeId() == GeometryTypeId::GEOS_POLYGON)){
        //多边形
        Polygon *tempP = dynamic_cast<Polygon *>(tempPolygon);
        //取外环
        const LinearRing *tempLine = dynamic_cast<const LinearRing *>(tempP->getExteriorRing());
        Polygon *polygon = geometryFactory->createPolygon((LinearRing *)tempLine, nullptr);
        //获取新的外环点集
        self.circlePoints = [self getPointsWithGeometry:polygon];
        
        geometryFactory->destroyGeometry(polygon);
    }else{
        geometryFactory->destroyGeometry(tempPolygon);
    }
}

- (NSMutableArray *)getPointsWithGeometry:(const Geometry *)geo{
    
    CoordinateSequence *tempSeq = geo->getCoordinates();
    long seqSize = tempSeq->getSize();
    
    NSMutableArray *nowPoints = [NSMutableArray array];
    for (int i = 0; i < seqSize; i ++) {
        double x = tempSeq->getX(i);
        double y = tempSeq->getY(i);
        CGPoint nowPoint = CGPointMake(x, y);
        [nowPoints addObject:@(nowPoint)];
    }
    return nowPoints;
}

- (void)cleanCircle{
    [self.circlePath removeAllPoints];
    self.circleLayer.path = self.circlePath.CGPath;
    self.circleLayer.strokeStart = 0;
    self.circleLayer.strokeEnd = 1;
}

- (void)setItemPoint:(CGPoint)itemPoint{
    _itemPoint = itemPoint;
    
    self.pointView.frame = CGRectMake(_itemPoint.x, _itemPoint.y, 1, 1);
}

//手势
- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    //开始，记下第一个点
    CGPoint startPoint = [[touches anyObject] locationInView:self];
    
    self.circleLayer.fillColor = [UIColor clearColor].CGColor;
    [self.circlePath removeAllPoints];
    [self.circlePoints removeAllObjects];
    [self.circlePath moveToPoint:startPoint];
    [self.circlePoints addObject:@(startPoint)];
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    CGPoint endPoint = [[touches anyObject] locationInView:self];
    [self.circlePoints addObject:@(endPoint)];
    [self.circlePath addLineToPoint:endPoint];
    
    //进行多边形过滤
    [self filterPolygon];
    
    [self.circlePath removeAllPoints];
    for (int i = 0; i < self.circlePoints.count; i ++) {
        CGPoint thisPoint = [self.circlePoints[i] CGPointValue];
        if(i == 0){
            [self.circlePath moveToPoint:thisPoint];
        }else{
            [self.circlePath addLineToPoint:thisPoint];
        }
    }
    [self.circlePath closePath];
    
    self.circleLayer.path = self.circlePath.CGPath;
    self.circleLayer.strokeStart = 0;
    self.circleLayer.strokeEnd = 1;
    self.circleLayer.fillRule = kCAFillRuleEvenOdd;
    self.circleLayer.fillColor = [[UIColor orangeColor] colorWithAlphaComponent:0.2].CGColor;
    
    if(self.endCircleBlock){
        self.endCircleBlock(self.circlePoints);
    }
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    CGPoint movePoint = [[touches anyObject] locationInView:self];
    if(CGPointEqualToPoint(movePoint, [[self.circlePoints lastObject] CGPointValue])){
        //跟上一个点相同的话，则舍弃
        return;
    }
    [self.circlePath addLineToPoint:movePoint];
    [self.circlePoints addObject:@(movePoint)];
    
    self.circleLayer.path = self.circlePath.CGPath;
    self.circleLayer.strokeStart = 0;
    self.circleLayer.strokeEnd = 1;
}


#pragma mark - lazyload

- (UIBezierPath *)circlePath{
    if(!_circlePath){
        _circlePath = [UIBezierPath bezierPath];
    }
    return _circlePath;
}

- (CAShapeLayer *)circleLayer{
    if(!_circleLayer){
        _circleLayer = [CAShapeLayer layer];
        _circleLayer.strokeColor = [UIColor orangeColor].CGColor;
        _circleLayer.fillColor = [UIColor clearColor].CGColor;
        _circleLayer.lineWidth = 2;
        _circleLayer.lineCap = kCALineCapRound;
    }
    return _circleLayer;
}

- (UIView *)pointView{
    if(!_pointView){
        _pointView = [[UIView alloc] init];
        _pointView.backgroundColor = [UIColor redColor];
    }
    return _pointView;
}

- (NSMutableArray *)circlePoints{
    if(!_circlePoints){
        _circlePoints = [NSMutableArray array];
    }
    return _circlePoints;
}

@end
