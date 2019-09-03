//
//  LDPropertyKey.h
//  LDExtensionExample
//
//  Created by LD Lee on 15/8/11.
//  Copyright (c) 2015年 小码哥. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
    LDPropertyKeyTypeDictionary = 0, // 字典的key
    LDPropertyKeyTypeArray // 数组的key
} LDPropertyKeyType;

/**
 *  属性的key
 */
@interface LDPropertyKey : NSObject
/** key的名字 */
@property (copy,   nonatomic) NSString *name;
/** key的种类，可能是@"10"，可能是@"age" */
@property (assign, nonatomic) LDPropertyKeyType type;

/**
 *  根据当前的key，也就是name，从object（字典或者数组）中取值
 */
- (id)valueInObject:(id)object;

@end
