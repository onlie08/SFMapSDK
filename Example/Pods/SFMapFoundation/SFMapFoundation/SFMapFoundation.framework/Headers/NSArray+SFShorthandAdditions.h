//
//  NSArray+SFShorthandAdditions.h
//  SFMasonry
//
//  Created by Jonas Budelmann on 22/07/13.
//  Copyright (c) 2013 Jonas Budelmann. All rights reserved.
//

#import "NSArray+SFAdditions.h"

#ifdef SF_SHORTHAND

/**
 *	Shorthand array additions without the 'sf_' prefixes,
 *  only enabled if SF_SHORTHAND is defined
 */
@interface NSArray (SFShorthandAdditions)

- (NSArray *)_sf_makeConstraints:(void(^)(SFConstraintMaker *make))block;
- (NSArray *)_sf_updateConstraints:(void(^)(SFConstraintMaker *make))block;
- (NSArray *)_sf_remakeConstraints:(void(^)(SFConstraintMaker *make))block;

@end

@implementation NSArray (SFShorthandAdditions)

- (NSArray *)_sf_makeConstraints:(void(^)(SFConstraintMaker *))block {
    return [self sf_makeConstraints:block];
}

- (NSArray *)_sf_updateConstraints:(void(^)(SFConstraintMaker *))block {
    return [self sf_updateConstraints:block];
}

- (NSArray *)_sf_remakeConstraints:(void(^)(SFConstraintMaker *))block {
    return [self sf_remakeConstraints:block];
}

@end

#endif
