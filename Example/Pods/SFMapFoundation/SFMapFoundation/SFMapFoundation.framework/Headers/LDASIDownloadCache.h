//
//  LDASIDownloadCache.h
//  Created by sfmap on 16/4/20.
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LDASICacheDelegate.h"

@interface LDASIDownloadCache : NSObject <LDASICacheDelegate> {
	
	// The default cache policy for this cache
	// Requests that store data in the cache will use this cache policy if their cache policy is set to LDASIUseDefaultCachePolicy
	// Defaults to LDASIAskServerIfModifiedWhenStaleCachePolicy
	LDASICachePolicy defaultCachePolicy;
	
	// The directory in which cached data will be stored
	// Defaults to a directory called 'LDASIHTTPRequestCache' in the temporary directory
	NSString *storagePath;
	
	// Mediates access to the cache
	NSRecursiveLock *accessLock;
	
	// When YES, the cache will look for cache-control / pragma: no-cache headers, and won't reuse store responses if it finds them
	BOOL shouldRespectCacheControlHeaders;
}

// Returns a static instance of an LDASIDownloadCache
// In most circumstances, it will make sense to use this as a global cache, rather than creating your own cache
// To make LDASIHTTPRequests use it automatically, use [LDASIHTTPRequest setDefaultCache:[LDASIDownloadCache sharedCache]];
+ (id)sharedCache;

// A helper function that determines if the server has requested data should not be cached by looking at the request's response headers
+ (BOOL)serverAllowsResponseCachingForRequest:(LDASIHTTPRequest *)request;

// A list of file extensions that we know won't be readable by a webview when accessed locally
// If we're asking for a path to cache a particular url and it has one of these extensions, we change it to '.html'
+ (NSArray *)fileExtensionsToHandleAsHTML;

@property (assign, nonatomic) LDASICachePolicy defaultCachePolicy;
@property (retain, nonatomic) NSString *storagePath;
@property (retain) NSRecursiveLock *accessLock;
@property (assign) BOOL shouldRespectCacheControlHeaders;
@end
