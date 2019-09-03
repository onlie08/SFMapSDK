
#import <Foundation/Foundation.h>

typedef enum {
    kSFCryptorNone = 0,  //无加密
    kSFCryptorDES = 2,  // DES 加密
    kSFCryptorRSA = 4 // RSA 加密
}SFCryptorType;

@interface SFCrypto : NSObject

// 子类须初始化
+ (instancetype)sharedCrypto;

/*!
 @function   encrypt:key
 @param      plainData       待加密的二进制流
 @param      key             如果为nil,使用默认密钥，否则使用传入的key; DES加密可以调用
                             resetDESKey 方法，重置密钥；
 @return                     加密后的数据，如果为nil,则加密失败
 */
- (NSData *)encrypt:(NSData *)plainData
                key:(NSString *)key;

/*!
 @function   decrypt:key
 @param      cipherData      待解密的二进制流 
 @param      key             如果为nil,使用默认密钥，否则使用传入的key; DES加密可以调用
                             resetDESKey 方法，重置密钥；
 @return                     解密后的数据，如果为nil,则解密失败
 */
- (NSData *)decrypt:(NSData *)cipherData
                key:(NSString *)key;
@end
