//
//  SFOfflineAuthentication.h
//  SFFoundation
//
//  Created by sfmap on 16/9/6.
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef void (^SFOfflineAuthenticationBlock)(NSString * deviceIDFilePath);

@interface SFOfflineAuthentication : NSObject

@property (nonatomic, strong) SFOfflineAuthenticationBlock authenticationBlock;

- (BOOL)setOfflineAuthenticationFile:(NSString *)filePath  authenticationBlock:(SFOfflineAuthenticationBlock)authenticationBlock;

+ (instancetype)sharedOfflineAuthentication;

- (BOOL)getAuthenticationResult;

void IOSGetDeviceID( char *cpDeviceID );

@end
