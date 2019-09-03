
#import <Foundation/Foundation.h>

@class NSString;

@interface NSData (Encryption)

- (NSData *)sfAES256EncryptWithKey:(NSString *)key;   //加密
- (NSData *)sfAES256DecryptWithKey:(NSString *)key;   //解密

@end
