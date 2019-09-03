//
//  LMKOfflineCityAggregate.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "LMKOfflineItemCommonCity.h"
#import "LMKOfflineProvince.h"
#import "LMKOfflineItemNationWide.h"
#import "LMKOfflineItemMunicipality.h"
@interface LMKOfflineCityAggregate : NSObject<NSCoding>

+ (id)cityAggregateWithVersion:(NSString *)version citys:(NSArray *)citys;
+ (id)cityAggregateWithVersion:(NSString *)version provinces:(NSArray *)provinces municipalities:(NSArray*)municipalities cities:(NSArray*)cities specialCities:(NSArray*)specialCities nationWide:(LMKOfflineItemNationWide *)nationWide;

@property (nonatomic, copy) NSString *version;

@property (nonatomic, strong) NSArray *cities;
@property (nonatomic,strong) NSArray<LMKOfflineProvince*> *provinces;
@property (nonatomic,strong) LMKOfflineItemNationWide *nationWide;
@property (nonatomic,strong) NSArray *municipalities;
@property (nonatomic, strong) NSArray *specialCities;
@end

@interface LMKOfflineCityAggregate (FileSystem)

+ (id)cityAggregateWithContentsOfFile:(NSString *)path;

- (BOOL)writeToFile:(NSString *)path;


@end
