//
//  LMKGeometry.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <CoreLocation/CoreLocation.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#ifdef __cplusplus
extern "C" {
#endif
    
/*!
 @brief 地图投影类型，支持墨卡托投影和4326投影
 */
typedef NS_ENUM(NSUInteger, LMKMapProjectionType) {
    LMKMapProjectionTypeMercator,   //! 墨卡托投影，默认（支持矢量地图和栅格地图）
    LMKMapProjectionTypeG4326,       //! 4326投影（暂时只支持栅格地图）
};
    

#ifndef __LMK_GEOMETRY__H_
#define __LMK_GEOMETRY__H_
/*!
 @brief 地图投影点，用平面直角坐标表示(20级像素坐标)。
 */
typedef struct {
    double x;
    double y;
} LMKMapPoint;
/*!
 @brief 平面投影大小结构定义
 */
typedef struct {
    double width;
    double height;
} LMKMapSize;
/*!
 @brief 平面投影矩形结构定义
 */
typedef struct {
    LMKMapPoint origin;
    LMKMapSize size;
} LMKMapRect;
/*!
 @brief 经纬度范围
 */
typedef struct {
    CLLocationCoordinate2D northEast;
    CLLocationCoordinate2D southWest;
} LMKCoordinateBounds;
/*!
 @brief 表示一个经纬度跨度
 */
typedef struct {
    CLLocationDegrees latitudeDelta;
    CLLocationDegrees longitudeDelta;
} LMKCoordinateSpan;
/*!
 @brief 经纬度区域
 */
typedef struct {
    CLLocationCoordinate2D center;
    LMKCoordinateSpan span;
} LMKCoordinateRegion;

static inline LMKCoordinateBounds LMKCoordinateBoundsMake(CLLocationCoordinate2D northEast, CLLocationCoordinate2D southWest)
{
    return (LMKCoordinateBounds){ northEast, southWest };
}

static inline LMKCoordinateSpan LMKCoordinateSpanMake(CLLocationDegrees latitudeDelta, CLLocationDegrees longitudeDelta)
{
    return (LMKCoordinateSpan){ latitudeDelta, longitudeDelta };
}

static inline LMKCoordinateRegion LMKCoordinateRegionMake(CLLocationCoordinate2D centerCoordinate, LMKCoordinateSpan span)
{
    return (LMKCoordinateRegion){ centerCoordinate, span };
}

/*!
     const常量定义
     */
extern const LMKMapSize LMKMapSizeWorld;

extern const LMKMapRect LMKMapRectWorld;

extern const LMKMapRect LMKMapRectZero;

/*!
 @brief 经纬度坐标转平面投影坐标
 @param coordinate 要转化的经纬度坐标
 @param projectionType 投影类型
 @return 平面投影坐标
 */
extern LMKMapPoint LMKMapPointForCoordinate(CLLocationCoordinate2D coordinate, LMKMapProjectionType projectionType);

/*!
 @brief 平面投影坐标转经纬度坐标
 @param mapPoint 要转化的平面投影坐标
 @param projectionType 投影类型 投影类型,0:墨卡托，1：4326
 @return 经纬度坐标
 */
extern CLLocationCoordinate2D LMKCoordinateForMapPoint(LMKMapPoint mapPoint, LMKMapProjectionType projectionType);

/*!
 @brief 字符串坐标转经纬度坐标
 @param coornaditeStr 要转化的字符串坐标
 @param count 返回坐标点的个数
 @return 经纬度坐标，内部malloc 需要外部释放 free
 */
extern CLLocationCoordinate2D* LMKCoordinatesForCoordinateString(NSString* coornaditeStr, NSUInteger* count);

/*!
 @brief 字符串坐标转经纬度点坐标
 @param coornaditeStr 要转化的字符串坐标
 @param count 返回坐标点的个数
 @return 经纬度点坐标，内部malloc 需要外部释放 free，比实际的点多了一个（两个int大小）
 */
extern int* LMKCoordinatePointsForCoordinateString(NSString* coornaditeStr, int* count);

/*!
 @brief 平面投影点集合所属的平面范围
 @param pointArray 平面坐标点
 @return 平面投影点集平面范围
 */
extern LMKMapRect mapRectForMapPoints(NSArray* pointArray);

/*!
 @brief 合并两个LMKMapRect
 */
extern LMKMapRect LMKMapRectUnion(LMKMapRect rect1, LMKMapRect rect2);

static inline LMKMapPoint LMKMapPointMake(double x, double y)
{
    return (LMKMapPoint){ x, y };
}

static inline LMKMapSize LMKMapSizeMake(double width, double height)
{
    return (LMKMapSize){ width, height };
}

static inline LMKMapRect LMKMapRectMake(double x, double y, double width, double height)
{
    return (LMKMapRect){ LMKMapPointMake(x, y), LMKMapSizeMake(width, height) };
}

static inline LMKMapPoint LMKGetMapRectCenter(LMKMapRect mapRect)
{
    return (LMKMapPoint){ mapRect.origin.x + mapRect.size.width / 2, mapRect.origin.y + mapRect.size.height / 2 };
}

static inline double LMKMapRectGetMinX(LMKMapRect rect)
{
    return rect.origin.x;
}

static inline double LMKMapRectGetMinY(LMKMapRect rect)
{
    return rect.origin.y;
}

static inline double LMKMapRectGetMidX(LMKMapRect rect)
{
    return rect.origin.x + rect.size.width / 2.0;
}

static inline double LMKMapRectGetMidY(LMKMapRect rect)
{
    return rect.origin.y + rect.size.height / 2.0;
}

static inline double LMKMapRectGetMaxX(LMKMapRect rect)
{
    return rect.origin.x + rect.size.width;
}

static inline double LMKMapRectGetMaxY(LMKMapRect rect)
{
    return rect.origin.y + rect.size.height;
}

static inline double LMKMapRectGetWidth(LMKMapRect rect)
{
    return rect.size.width;
}

static inline double LMKMapRectGetHeight(LMKMapRect rect)
{
    return rect.size.height;
}

extern BOOL LMKMapRectIntersectsRect(LMKMapRect rect1, LMKMapRect rect2);
extern BOOL LMKMapRectContainsRect(LMKMapRect rect1, LMKMapRect rect2);
extern BOOL LMKMapRectEqualRect(LMKMapRect rect1, LMKMapRect rect2);
    
/*!
 @brief 1米对应的投影

 @param latitude 纬度
 @param projectionType 投影类型
 @return 1米对应的投影像素点坐标
 */
extern double LMKMapPointsPerMeterAtLatitude(CLLocationDegrees latitude, LMKMapProjectionType projectionType);

/*!
 @brief 经纬度两点之间的距离

 @param coord1 坐标1
 @param coord2 坐标2
 @return 经纬度两点之间的距离
 */
extern CLLocationDistance LMKMetersBetweenLocations(CLLocationCoordinate2D coord1, CLLocationCoordinate2D coord2);
    
#endif

#ifdef __cplusplus
}
#endif
