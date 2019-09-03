//
//  LMKDownLoader2.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LMKDownLoaderItemProgress;
@class LMKOfflineItem;
@protocol LMKDownLoaderProtocol <NSObject>

@optional
/**
 *  下载进度
 *
 *  @param url         下载的URL
 *  @param currentSize 当前的数据大小
 */
- (void)downLoaderProgressWithURL:(NSURL*)url progress:(LMKDownLoaderItemProgress*)progress;

/**
 *  下载完成
 *
 *  @param url 下载的URL
 */
- (void)downLoaderCompletionWithURL:(NSURL*)url;

/**
 *  下载出错
 *
 *  @param url           下载的URL
 *  @param downloadError 错误信息
 */
- (void)downLoaderErrorWithURL:(NSURL*)url error:(NSError*)downloadError;

@end

/**
 *  下载管理类
 */
typedef void (^ProgressBlock)(NSUInteger currentSize, long long totalSize, NSURL *url);
typedef void (^CompletedBlock)(NSUInteger receivedSize, NSError* error, NSURL *url);
typedef void (^CancelledBlock)(NSUInteger receivedSize, NSURL *url);
typedef void (^WillDeleteBlock)();
typedef void (^WillPauseBlock)();

@interface LMKDownLoader2 : NSObject
@property (nonatomic, copy) ProgressBlock ProgressBlock;
@property (nonatomic, copy) CompletedBlock CompletedBlock;
@property (nonatomic, copy) CancelledBlock CancelledBlock;
@property (nonatomic, copy) WillDeleteBlock WillDeleteBlock;
@property (nonatomic, copy) WillPauseBlock WillPauseBlock;
@property (nonatomic, copy) NSString *filePathName; //文件存放路径
@property (nonatomic, strong) NSURLSessionConfiguration* sessionConfigure;
@property (nonatomic, strong) NSURLSession* session;

@property (nonatomic, strong) NSMutableDictionary* downloadTaskDic; // 当前正在下载的任务字典
@property (nonatomic, strong) NSMutableDictionary* isDownloadingTaskDic;
@property (nonatomic, strong) NSMutableArray* downloadTaskArray; // 当前正在下载的任务队列

@property (nonatomic, strong) NSMutableDictionary* fileHandlerDic; // 存放文件handler
@property (nonatomic, strong) NSMutableDictionary* downloadProgress; // 文件下载进度记录
@property (nonatomic, strong) NSMutableDictionary *progressBlockDict;//存放ProgressBlock的队列
@property (nonatomic, strong) NSMutableDictionary *completedBlockDict;//存放CompletedBlock的队列
@property (nonatomic, strong) NSMutableDictionary *cancelledBlockDict;//存放CancelledBlock的队列

@property (nonatomic, strong) NSMutableDictionary *willDeleteBlockDict;//存放willDeleteBlock的队列
@property (nonatomic, strong) NSMutableDictionary *willPauseBlockDict;//存放willPauseBlock的队列

+ (instancetype)sharedManager;

@property (nonatomic, weak) id<LMKDownLoaderProtocol> delegate;
-(void)downloadWithURL:(NSURL*)url totalSize:(long long)totalSize progress:(ProgressBlock)ProgressBlock completed:(CompletedBlock)CompletedBlock cancelled:(CancelledBlock)CancelledBlock;
// 暂停任务
- (void)pauseDownloadWithURL:(NSURL*)url;
// 开始添加某一个下载任务到队列
- (void)startDownloadWithURL:(NSURL*)url;

// 从队列中取消某一个下载任务
- (void)cancelDownloadWithURL:(NSURL*)url;

// 取消队列中的所有下载任务
- (void)cancelAll;
//是否正在下载
- (BOOL)isDownloadingForURL:(NSURL*)url;
//销毁自身
+ (void)destoryDownloader2;
//返回当前task的数目
- (NSInteger)getIsDownloadingItemsCount;
@end

/**
 *  记录当前下载文件的进度
 */
@interface LMKDownLoaderItemProgress : NSObject

@property (nonatomic, assign) NSUInteger totalSize;
@property (nonatomic, assign) NSUInteger currentSize;

@end
