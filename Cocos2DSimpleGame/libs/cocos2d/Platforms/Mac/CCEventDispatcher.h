/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2010 Ricardo Quesada
 * Copyright (c) 2011 Zynga Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// Only compile this code on Mac. These files should not be included on your iOS project.
// But in case they are included, it won't be compiled.
#import "../../ccMacros.h"
#ifdef __CC_PLATFORM_MAC

#import <Cocoa/Cocoa.h>

#import "CCGLView.h"
#import "../../Support/uthash.h"	// hack: uthash needs to be imported before utlist to prevent warning
#import "../../Support/utlist.h"
#import "../../ccConfig.h"

#pragma mark -
#pragma mark CCMouseEventDelegate

/** CCMouseEventDelegate protocol.
 Implement it in your node to receive any of mouse events
 */
@protocol CCMouseEventDelegate <NSObject>
@optional

//
// left
//
/** called when the "mouseDown" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccMouseDown:(NSEvent*)event;

/** called when the "mouseDragged" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccMouseDragged:(NSEvent*)event;

/** called when the "mouseMoved" event is received.
 Return YES to avoid propagating the event to other delegates.
 By default, "mouseMoved" is disabled. To enable it, send the "setAcceptsMouseMovedEvents:YES" message to the main window.
 */
-(BOOL) ccMouseMoved:(NSEvent*)event;

/** called when the "mouseUp" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccMouseUp:(NSEvent*)event;


//
// right
//

/** called when the "rightMouseDown" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccRightMouseDown:(NSEvent*)event;

/** called when the "rightMouseDragged" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccRightMouseDragged:(NSEvent*)event;

/** called when the "rightMouseUp" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccRightMouseUp:(NSEvent*)event;

//
// other
//

/** called when the "otherMouseDown" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccOtherMouseDown:(NSEvent*)event;

/** called when the "otherMouseDragged" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccOtherMouseDragged:(NSEvent*)event;

/** called when the "otherMouseUp" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccOtherMouseUp:(NSEvent*)event;

//
// scroll wheel
//

/** called when the "scrollWheel" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
- (BOOL)ccScrollWheel:(NSEvent *)theEvent;


//
// enter / exit
//

/** called when the "mouseEntered" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
- (void)ccMouseEntered:(NSEvent *)theEvent;

/** called when the "mouseExited" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
- (void)ccMouseExited:(NSEvent *)theEvent;

@end

#pragma mark -
#pragma mark CCKeyboardEventDelegate

/** CCKeyboardEventDelegate protocol.
 Implement it in your node to receive any of keyboard events
 */
@protocol CCKeyboardEventDelegate <NSObject>
@optional
/** called when the "keyUp" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccKeyUp:(NSEvent*)event;

/** called when the "keyDown" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccKeyDown:(NSEvent*)event;
/** called when the "flagsChanged" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccFlagsChanged:(NSEvent*)event;
@end

#pragma mark -
#pragma mark CCTouchEventDelegate

/** CCTouchEventDelegate protocol.
 Implement it in your node to receive any of touch events
 */
@protocol CCTouchEventDelegate <NSObject>
@optional
/** called when the "touchesBegan" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
- (BOOL)ccTouchesBeganWithEvent:(NSEvent *)event;

/** called when the "touchesMoved" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
- (BOOL)ccTouchesMovedWithEvent:(NSEvent *)event;

/** called when the "touchesEnded" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
- (BOOL)ccTouchesEndedWithEvent:(NSEvent *)event;

/** called when the "touchesCancelled" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
- (BOOL)ccTouchesCancelledWithEvent:(NSEvent *)event;

@end

#pragma mark -
#pragma mark CCGestureEventDelegate

/** CCGestureEventDelegate protocol.
 Implement it in your node to receive any of gesture events
 */
@protocol CCGestureEventDelegate <NSObject>
@optional

/** called when the "beginGesture" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
- (BOOL)ccBeginGestureWithEvent:(NSEvent *)event;

/** called when the "magnify" gesture event is received.
 Return YES to avoid propagating the event to other delegates.
 */
- (BOOL)ccMagnifyWithEvent:(NSEvent *)event;

/** called when the "smartMagnify" gesture event is received.
 Return YES to avoid propagating the event to other delegates.
 */
- (BOOL)ccSmartMagnifyWithEvent:(NSEvent *)event;

/** called when the "rotate" gesture event is received.
 Return YES to avoid propagating the event to other delegates.
 */
- (BOOL)ccRotateWithEvent:(NSEvent *)event;

/** called when the "swipe" gesture event is received.
 Return YES to avoid propagating the event to other delegates.
 */
- (BOOL)ccSwipeWithEvent:(NSEvent *)event;

/** called when the "endGesture" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
- (BOOL)ccEndGestureWithEvent:(NSEvent *)event;

@end

#pragma mark - CCEventObject

@interface CCEventObject : NSObject
{
@public
	NSEvent		*event;
	SEL			selector;
}
@end

#pragma mark - CCEventDispatcher

struct _listEntry;
struct _listDeletedEntry;
struct _listAddedEntry;

/** CCEventDispatcher

 This is object is responsible for dispatching the events:
	- Mouse events
	- Keyboard events
	- Touch events

 Only available on Mac
 */
@interface CCEventDispatcher : NSObject <CCEventDelegate> {

	BOOL					dispatchEvents_;
	BOOL					locked_;

	struct	_listEntry		*keyboardDelegates_;
	struct	_listEntry		*mouseDelegates_;
	struct	_listEntry		*touchDelegates_;
	struct	_listEntry		*gestureDelegates_;
	
	struct	_listDeletedEntry	*delegatesToBeRemoved_;
	struct	_listAddedEntry		*delegatesToBeAdded_;
	
}

@property (nonatomic, readwrite) BOOL dispatchEvents;

#pragma mark CCEventDispatcher - Mouse

/** Adds a mouse delegate to the dispatcher's list.
 Delegates with a lower priority value will be called before higher priority values.
 All the events will be propagated to all the delegates, unless the one delegate returns YES.

 IMPORTANT: The delegate will be retained.
 */
-(void) addMouseDelegate:(id<CCMouseEventDelegate>) delegate priority:(NSInteger)priority;

/** removes a mouse delegate */
-(void) removeMouseDelegate:(id) delegate;

/** Removes all mouse delegates, releasing all the delegates */
-(void) removeAllMouseDelegates;

#pragma mark CCEventDispatcher - Keyboard

/** Adds a Keyboard delegate to the dispatcher's list.
 Delegates with a lower priority value will be called before higher priority values.
 All the events will be propagated to all the delegates, unless the one delegate returns YES.

 IMPORTANT: The delegate will be retained.
 */
-(void) addKeyboardDelegate:(id<CCKeyboardEventDelegate>) delegate priority:(NSInteger)priority;

/** removes a mouse delegate */
-(void) removeKeyboardDelegate:(id) delegate;

/** Removes all mouse delegates, releasing all the delegates */
-(void) removeAllKeyboardDelegates;

#pragma mark CCEventDispatcher - Touches

/** Adds a Touch delegate to the dispatcher's list.
 Delegates with a lower priority value will be called before higher priority values.
 All the events will be propagated to all the delegates, unless the one delegate returns YES.

 IMPORTANT: The delegate will be retained.
 */
- (void)addTouchDelegate:(id<CCTouchEventDelegate>)delegate priority:(NSInteger)priority;

/** Removes a touch delegate */
- (void)removeTouchDelegate:(id) delegate;

/** Removes all touch delegates, releasing all the delegates */
- (void)removeAllTouchDelegates;

#pragma mark CCEventDispatcher - Gesture

/** Adds a gesture delegate to the dispatcher's list.
 Delegates with a lower priority value will be called before higher priority values.
 All the events will be propagated to all the delegates, unless the one delegate returns YES.
 
 IMPORTANT: The delegate will be retained.
 */
- (void)addGestureDelegate:(id<CCGestureEventDelegate>)delegate priority:(NSInteger)priority;

/** Removes a gesture delegate */
- (void)removeGestureDelegate:(id) delegate;

/** Removes all gesture delegates, releasing all the delegates */
- (void)removeAllGestureDelegates;

#pragma mark CCEventDispatcher - Dispatch

-(void) dispatchEvent:(CCEventObject*)event;

@end


#endif // __CC_PLATFORM_MAC
