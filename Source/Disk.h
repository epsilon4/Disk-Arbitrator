//
//  Disk.h
//  DiskArbitrator
//
//  Created by Aaron Burghardt on 1/10/10.
//  Copyright 2010 Aaron Burghardt. All rights reserved.
//

#import <Cocoa/Cocoa.h>

extern NSString * const DADiskDidAppearNotification;
extern NSString * const DADiskDidDisappearNotification;
extern NSString * const DADiskDidChangeNotification;
extern NSString * const DADiskDidAttemptMountNotification;
extern NSString * const DADiskDidAttemptUnmountNotification;
extern NSString * const DADiskDidAttemptEjectNotification;

extern NSString * const DAStatusErrorKey;

enum { 
    kDiskUnmountOptionDefault = 0x00000000, 
    kDiskUnmountOptionForce = 0x00080000, 
    kDiskUnmountOptionWhole = 0x00000001 
};

/* The mounting attribute exists because of a quirk when attaching a volume using "hdiutil attach".  Even if "-nomount"
 * is specified, the mount approval callback is called. This confuses the situation when attempting to initiate
 * a mount when Disk Arbitrator is in read-only mode.  "mounting" distinguishes between a callback that is triggered by hdiutil
 * and the one that results from calling DADiskMount().
 *
 * Even if the extra callback issue didn't exist, "mounting" (or some other means) is needed to know when to allow a mount
 * in the mount approval callback.
 */

@interface Disk : NSObject 
{
	CFTypeRef disk;
	NSString *BSDName;
	CFDictionaryRef diskDescription;
	BOOL isMounting;
	BOOL rejectedMount;
	NSImage *icon;
	Disk *parent;
	NSMutableSet *children;
	NSArray *mountArgs;
	NSString *mountPath;
}

@property (copy) NSString *BSDName;
@property (readonly) int BSDNameNumber;
@property CFDictionaryRef diskDescription;
@property (readonly) BOOL isMountable;
@property (readonly) BOOL isMounted;
@property (readwrite) BOOL isMounting;
@property (readwrite) BOOL rejectedMount;
@property (readonly) BOOL isWritable;
@property (readonly) BOOL isFileSystemWritable;
@property (readonly) BOOL isEjectable;
@property (readonly) BOOL isRemovable;
@property (readonly) BOOL isWholeDisk;
@property (readonly) BOOL isLeaf;
@property (readonly) BOOL isNetworkVolume;
@property (readonly, retain) NSImage *icon;
@property (assign) Disk *parent;
@property (retain) NSMutableSet *children;
@property (readwrite, retain) NSArray *mountArgs;
@property (readwrite, retain) NSString *mountPath;
@property (readonly) BOOL isHFS;

- (void)mount;
- (void)mountAtPath:(NSString *)path withArguments:(NSArray *)args;
- (void)unmountWithOptions:(NSUInteger)options;
- (void)eject;

@end
