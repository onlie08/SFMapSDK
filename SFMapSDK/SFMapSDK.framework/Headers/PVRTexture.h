//
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PVRTexture : NSObject {
    BOOL _hasAlpha;
}

+ (BOOL)unpackPVRData:(unsigned char*)data;

@end
