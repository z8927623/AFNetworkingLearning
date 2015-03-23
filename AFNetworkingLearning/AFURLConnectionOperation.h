//
//  AFURLConnectionOperation.h
//  AFNetworkingLearning
//
//  Created by wildyao on 15/2/21.
//  Copyright (c) 2015年 wildyao. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
    AFSSLPinningModeNone,
    AFSSLPinningModePublicKey,
    AFSSLPinningModeCertificate,
} AFURLConnectionOperationSSLPinningMode;

@interface AFURLConnectionOperation : NSOperation <NSURLConnectionDelegate,
#if (defined(__IPHONE_OS_VERSION_MIN_REQUIRED) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 50000) || \
(defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 1080)
NSURLConnectionDataDelegate,
#endif
NSCoding, NSCopying>


@property (nonatomic, strong) NSSet *runLoopModes;

@property (nonatomic, strong, readonly) NSURLRequest *request;

@property (nonatomic, strong, readonly) NSURLResponse *response;

@property (nonatomic, strong, readonly) NSError *error;

/**
 * 是否允许无效的SSL证书
 */
@property (nonatomic, assign) BOOL allowsInvalidSSLCertificate;

@property (nonatomic, strong, readonly) NSData *responseData;

@property (nonatomic, strong, readonly) NSString *responseString;

/**
 * 如果response没有使用编码，则responseStringEncoding返回NSUTF8StringEncoding
 * NSStringEncoding为NSUInteger
 */
@property (nonatomic, assign, readonly) NSStringEncoding responseStringEncoding;

/**
 * 是否需要校验证书，默认为YES
 * `NSURLConnectionDelegate` method `-connectionShouldUseCredentialStorage:`
 */
@property (nonatomic, assign) BOOL shouldUseCredentialStorage;

/**
 * 证书
 * `-connection:didReceiveAuthenticationChallenge:`
 */
@property (nonatomic, strong) NSURLCredential *credential;

@property (nonatomic, assign) AFURLConnectionOperationSSLPinningMode SSLPinningMode;

/**
 * 读取数据
 */
@property (nonatomic, strong) NSInputStream *inputStream;

/**
 * 写入数据
 */
@property (nonatomic, strong) NSOutputStream *outputStream;

@property (nonatomic, strong) NSDictionary *userInfo;

- (id)initWithRequest:(NSURLRequest *)urlRequest;

- (void)pause;

- (BOOL)isPaused;

- (void)resume;

#if defined(__IPHONE_OS_VERSION_MIN_REQUIRED)
- (void)setShouldExecuteAsBackgroundTaskWithExpirationHandler:(void (^)(void))handler;
#endif

- (void)setUploadProgressBlock:(void (^)(NSUInteger bytesWritten, long long totalBytesWritten, long long totalBytesExpectedToWrite))block;

- (void)setDownloadProgressBlock:(void (^)(NSUInteger bytesRead, long long totalBytesRead, long long totalBytesExpectedToRead))block;

/**
 * `NSURLConnectionDelegate` method `connection:willSendRequestForAuthenticationChallenge:`.
 */
- (void)setWillSendRequestForAuthenticationChallengeBlock:(void (^)(NSURLConnection *connection, NSURLAuthenticationChallenge *challenge))block;

/**
 * `NSURLConnectionDelegate` method `connection:willSendRequest:redirectResponse:`
 */
- (void)setRedirectResponseBlock:(NSURLRequest * (^)(NSURLConnection *connection, NSURLRequest *request, NSURLResponse *redirectResponse))block;

/**
 * `NSURLConnectionDelegate` method `connection:willCacheResponse:`
 */
- (void)setCacheResponseBlock:(NSCachedURLResponse * (^)(NSURLConnection *connection, NSCachedURLResponse *cachedResponse))block;

@end

/**
 * `AFNetworkingErrorDomain`
 */
extern NSString *const AFNetworkingErrorDomain;
extern NSString *const AFNetworkingOperationFailingURLRequestErrorKey;
extern NSString *const AFNetworkingOperationFailingURLResponseErrorKey;

/**
 * Notifications
 */
extern NSString *const AFNetworkingOperationDidStartNotification;
extern NSString *const AFNetworkingOperationDidFinishNotification;
