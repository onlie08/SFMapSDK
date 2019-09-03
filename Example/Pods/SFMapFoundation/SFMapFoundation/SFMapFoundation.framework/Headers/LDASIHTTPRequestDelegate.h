//
//  LDASIHTTPRequestDelegate.h
//  Part of LDASIHTTPRequest -> http://allseeing-i.com/LDASIHTTPRequest
//
//  Created by Ben Copsey on 13/04/2010.
//  Copyright 2010 All-Seeing Interactive. All rights reserved.
//

@class LDASIHTTPRequest;

@protocol LDASIHTTPRequestDelegate <NSObject>

@optional

// These are the default delegate methods for request status
// You can use different ones by setting didStartSelector / didFinishSelector / didFailSelector
- (void)requestStarted:(LDASIHTTPRequest *)request;
- (void)request:(LDASIHTTPRequest *)request didReceiveResponseHeaders:(NSDictionary *)responseHeaders;
- (void)request:(LDASIHTTPRequest *)request willRedirectToURL:(NSURL *)newURL;
- (void)requestFinished:(LDASIHTTPRequest *)request;
- (void)requestFailed:(LDASIHTTPRequest *)request;
- (void)requestRedirected:(LDASIHTTPRequest *)request;

// When a delegate implements this method, it is expected to process all incoming data itself
// This means that responseData / responseString / downloadDestinationPath etc are ignored
// You can have the request call a different method by setting didReceiveDataSelector
- (void)request:(LDASIHTTPRequest *)request didReceiveData:(NSData *)data;

// If a delegate implements one of these, it will be asked to supply credentials when none are available
// The delegate can then either restart the request ([request retryUsingSuppliedCredentials]) once credentials have been set
// or cancel it ([request cancelAuthentication])
- (void)authenticationNeededForRequest:(LDASIHTTPRequest *)request;
- (void)proxyAuthenticationNeededForRequest:(LDASIHTTPRequest *)request;

@end
