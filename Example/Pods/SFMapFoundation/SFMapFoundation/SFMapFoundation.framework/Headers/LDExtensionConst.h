
#ifndef __LDExtensionConst__H__
#define __LDExtensionConst__H__

#import <Foundation/Foundation.h>

// 过期
#define LDExtensionDeprecated(instead) NS_DEPRECATED(2_0, 2_0, 2_0, 2_0, instead)

// 构建错误
#define LDExtensionBuildError(clazz, msg) \
NSError *error = [NSError errorWithDomain:msg code:250 userInfo:nil]; \
[clazz setLD_error:error];

// 日志输出
#ifdef DEBUG
#define LDExtensionLog(...) NSLog(__VA_ARGS__)
#else
#define LDExtensionLog(...)
#endif

/**
 * 断言
 * @param condition   条件
 * @param returnValue 返回值
 */
#define LDExtensionAssertError(condition, returnValue, clazz, msg) \
[clazz setLD_error:nil]; \
if ((condition) == NO) { \
    LDExtensionBuildError(clazz, msg); \
    return returnValue;\
}

#define LDExtensionAssert2(condition, returnValue) \
if ((condition) == NO) return returnValue;

/**
 * 断言
 * @param condition   条件
 */
#define LDExtensionAssert(condition) LDExtensionAssert2(condition, )

/**
 * 断言
 * @param param         参数
 * @param returnValue   返回值
 */
#define LDExtensionAssertParamNotNil2(param, returnValue) \
LDExtensionAssert2((param) != nil, returnValue)

/**
 * 断言
 * @param param   参数
 */
#define LDExtensionAssertParamNotNil(param) LDExtensionAssertParamNotNil2(param, )

/**
 * 打印所有的属性
 */
#define LDLogAllIvars \
-(NSString *)description \
{ \
    return [self LD_keyValues].description; \
}
#define LDExtensionLogAllProperties LDLogAllIvars

/**
 *  类型（属性类型）
 */
extern NSString *const LDPropertyTypeInt;
extern NSString *const LDPropertyTypeShort;
extern NSString *const LDPropertyTypeFloat;
extern NSString *const LDPropertyTypeDouble;
extern NSString *const LDPropertyTypeLong;
extern NSString *const LDPropertyTypeLongLong;
extern NSString *const LDPropertyTypeChar;
extern NSString *const LDPropertyTypeBOOL1;
extern NSString *const LDPropertyTypeBOOL2;
extern NSString *const LDPropertyTypePointer;

extern NSString *const LDPropertyTypeIvar;
extern NSString *const LDPropertyTypeMethod;
extern NSString *const LDPropertyTypeBlock;
extern NSString *const LDPropertyTypeClass;
extern NSString *const LDPropertyTypeSEL;
extern NSString *const LDPropertyTypeId;

#endif