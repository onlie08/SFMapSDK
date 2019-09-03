//
//  SFMapFoundation.h
//  SFMapFoundation
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for SFMapFoundation.
FOUNDATION_EXPORT double SFMapFoundationVersionNumber;

//! Project version string for SFMapFoundation.
FOUNDATION_EXPORT const unsigned char SFMapFoundationVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <SFMapFoundation/PublicHeader.h>

#import "SFMapCO.h"
#import "SFEncryption.h"
#import "LDExtension.h"
#import "SFMasonry.h"
#import "SFMCache.h"
#import "SFOfflineAuthentication.h"
#import "LDKit.h"
#import "SFFoundationHelper.h"

// 通用尺寸定义
#define SFMAP_SCREEN_BOUNDS [UIScreen mainScreen].bounds
#define SFMAP_SCREEN_WIDTH  [UIScreen mainScreen].bounds.size.width
#define SFMAP_SCREEN_HEIGHT ([UIScreen mainScreen].bounds.size.height - (([[UIApplication sharedApplication] statusBarFrame].size.height == 40)?20:0))

#define SFM_MAX  (SFMAP_SCREEN_WIDTH > SFMAP_SCREEN_HEIGHT ? SFMAP_SCREEN_WIDTH : SFMAP_SCREEN_HEIGHT)
#define SFM_MIN  (SFMAP_SCREEN_WIDTH < SFMAP_SCREEN_HEIGHT ? SFMAP_SCREEN_WIDTH : SFMAP_SCREEN_HEIGHT)

#define SFMAP_SF_IPHONE (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone)
#define SFMAP_IPHONE_4_OR_LESS (SFMAP_SF_IPHONE && SFM_MAX < 568.0)
#define SFMAP_IPHONE_5_OR_MORE (SFMAP_SF_IPHONE && SFM_MAX >= 568.0)
#define SFMAP_IPHONE_6_OR_MORE (SFMAP_SF_IPHONE && SFM_MAX >= 667.0)
#define SFMAP_IPHONE_6P (SFMAP_SF_IPHONE && SFM_MAX == 736.0)
#define SFMAP_IPHONE_X (SFM_MIN >= 375.0f && SFM_MAX >= 812.0f && SFMAP_SF_IPHONE)
//底部home bar高度
#define SFMAP_HOMEBAR_HEIGHT (SFMAP_IPHONE_X?34:0)

#define SFMAP_STATUSBAR_HEIGHT (([[UIApplication sharedApplication] statusBarFrame].size.height == 40)?20:[[UIApplication sharedApplication] statusBarFrame].size.height)
//#define SFMAP_STATUSBAR_HEIGHT [[UIApplication sharedApplication] statusBarFrame].size.height
#define SFMAP_NAVIGATIONBAR_VER_HEIGHT 44
#define SFMAP_NAVIGATIONBAR_HOR_HEIGHT 30
#define SFMAP_NAVIBAR_HEIGHT (SFMAP_STATUSBAR_HEIGHT + SFMAP_NAVIGATIONBAR_VER_HEIGHT)

//是否显示了顶部的蓝色框
#define SFMAP_SHOWING_TOP_BLUEBOX ([[UIApplication sharedApplication] statusBarFrame].size.height == 40)

