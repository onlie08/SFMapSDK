//
//  LMKGeoCodeAPI.h
//  SFMapSDK
//
//  Created by 龚聪(Cong Gong)-顺丰科技 on 2018/12/6.
//  Copyright © 2018年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

/**
 *  callback typedef
 *
 *  @param data    data parsed from json, may be NSArray or NSDictionary
 *  @param error   error if anything is wrong
 *
 */
typedef void (^LMKGeoCodeAPICallBack)(id data, NSError *error);

typedef enum {
    LMKGeoCodeAPIError_Param = 8000,       //参数错误
    LMKGeoCodeAPIError_NoLocation = 8001,  //没传地址
} LMKGeoCodeAPIErrorType;

/*!
 @brief 经纬度坐标。
 */
@interface LMKGeoPoint : NSObject<NSCopying>

@property (nonatomic, assign) double latitude; //!< 纬度（垂直方向）。
@property (nonatomic, assign) double longitude; //!< 经度（水平方向）。

+ (instancetype)locationWithLatitude:(double)latitude longitude:(double)longitude;
//是否有效
- (BOOL)isValidPoint;

@end

/*逆地理编码参数
 * (两个参数传一个即可)
 * @param point : 逆地理编码的地址
 * @param pointArray : 逆地理编码的地址数组
 */
@interface LMKReGeoCodeParam : NSObject

@property(nonatomic,copy)LMKGeoPoint *point;
@property(nonatomic,copy)NSArray<LMKGeoPoint *> *pointArray;
@property(nonatomic,assign)NSTimeInterval timeout;  //默认20秒
@property(nonatomic,assign)BOOL isCleanOtherTask;  //请求之前是否清空其他逆地理编码请求（默认NO，不清空）

+ (instancetype)paramWithPoint:(LMKGeoPoint *)point;
+ (instancetype)paramWithPointArray:(NSArray<LMKGeoPoint *> *)pointArray;

@end

//地理编码参数
@interface LMKGeoCodeParam : NSObject

@property(nonatomic,copy) NSString *address;        //地址
@property(nonatomic,copy) NSString *city;           //城市（可不传）
@property(nonatomic,assign)NSTimeInterval timeout;  //默认20秒
@property(nonatomic,assign)BOOL isCleanOtherTask;   //请求之前是否清空其他地理编码请求（默认NO，不清空）

+ (instancetype)paramWithAddress:(NSString *)address;
+ (instancetype)paramWithAddress:(NSString *)address city:(NSString *)city;

@end

@interface LMKGeoCodeAPI : NSObject

/**
 *  地理编码方法
 *
 *  @param param   参数，详见LMKGeoCodeParam
 *  @param callBack  回调
 *
 */
- (void)LMKGeocodeWithParam:(LMKGeoCodeParam *)param
                   callBack:(LMKGeoCodeAPICallBack)callBack;

/**
 *  逆地理编码方法
 *
 *  @param param   参数，详见LMKReGeoCodeParam
 *  @param callBack  回调
 *
 */
- (void)LMKReGeocodeWithParam:(LMKReGeoCodeParam *)param
                     callBack:(LMKGeoCodeAPICallBack)callBack;

/**
 *  清空所有请求
 */
- (void)LMKCleanAllTask;

@end
