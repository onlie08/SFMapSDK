//
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface XYMGLMapSourceGridData : NSObject {
	NSString	*_gridName;
	NSInteger	_dataSource;
    NSString    *_eTag;
}

@property (nonatomic, retain) NSString *gridName;
@property (nonatomic, assign) NSInteger dataSource;

@property (nonatomic, retain) NSString *eTag;

- (id)initWithGridName:(NSString *)gridName dataSource:(NSInteger)dataSource;
+ (id)dataWithGridName:(NSString *)gridName dataSource:(NSInteger)dataSource;

@end

@interface XYMGLMapVTMCData : NSObject {
	NSData			*_vtmcData;
	NSString		*_gridName;
	NSTimeInterval	_createTime;
        NSString        *_eTag;
        NSInteger             _timeStamp;
}

@property (nonatomic, retain) NSData *vtmcData;
@property (nonatomic, copy) NSString *gridName;
@property (nonatomic, readonly) NSTimeInterval createTime;
@property (nonatomic, copy) NSString *eTag;
@property (nonatomic, readonly) NSInteger timeStamp;

- (id)initWithGridName:(NSString *)gridName data:(NSData *)data;
+ (id)dataWithGridName:(NSString *)gridName data:(NSData *)data;

- (void)updateTimeStamp:(NSInteger)time;

@end

#define LDVTMC_MAXSIZE			500
#define LDVTMC_MAXEXPIREDTIME	300
@interface XYMGLMapVTMCDataCache : NSObject {
	NSMutableDictionary		*_vtmcDatas;
	NSMutableArray			*_vtmcList;
	NSRecursiveLock			*_lock;
        NSInteger               _newestTimeStamp;
}

+ (XYMGLMapVTMCDataCache *)cache;
- (void)reset;
- (XYMGLMapVTMCData *)addDataRetain:(NSData *)data withName:(NSString *)name;
- (XYMGLMapVTMCData *)dataRetainWithName:(NSString *)name checkExistOnly:(BOOL)checkExistOnly;

@end

