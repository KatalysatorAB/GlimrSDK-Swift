//
//  KATBeaconManager.h
//  Example
//
//  Created by Sven Roeder on 10/17/13.
//  Copyright (c) 2013 Katalysator AB. All rights reserved.
//

#import <CoreLocation/CoreLocation.h>
#import "KATConfiguration.h"


/**
 * KATTrackingEvent gives predefined options for tracking events in the app
 * Event tracking is optional and enriches analytics data on the backend.
 * - KATTrackingEventPresent will be called automatically for each `startWithHandler` call
 *
 */
typedef NS_OPTIONS(NSUInteger, KATTrackingEvent) {
    /** The KATTrackingEventPresent flag indicates that something is visually presented upon a beacon trigger.
     * @since v1.0.1
     */
    KATTrackingEventPresent,
    /** The KATTrackingEventAction allows to track actions such es button taps etc..
     * @since v1.0.1
     */
    KATTrackingEventAction,
    /** The KATTrackingEventError allows to track errors.
     * @since v1.0.1
     */
    KATTrackingEventError
};


/**
 * KATTriggerHandler defines the callback for trigger calls.
 *
 * @since v1.1.8
 */
typedef void(^KATTriggerHandler)(NSDictionary * _Nonnull requestDict);


/**
 * KATDebugHandler defines the callback for debug calls.
 *
 * @since v1.0
 */
typedef void(^KATDebugHandler)(id _Nonnull result);


/**
 
 A KATBeaconManager is responsible for the beacon interaction and callbacks to the app that integrates the SDK. In general it should be used as a shared object.
 
 The manager object needs a KATConfiguration object to initialize the beacon monitoring and ranging with the custom needs. Once the device enters or exits a region a callback to the startWithHandler: block might happen depending on the beacon configuration on the Katalysator Beacon backend. The same goes for entering and existing a individual beacon. Several beacons can be set up in one region and configured on the backend.
 
 The SDK makes use of the CoreLocation framework, specifically the monitoring and ranging of beacons in background and foreground mode.
 
 */
@interface KATBeaconManager : NSObject


////////////////////////////////////////////////////////////////////////////////
/// @name KATBeaconManager init
////////////////////////////////////////////////////////////////////////////////


/**
 * A shared version of the KATBeaconManager
 *
 * @return an previous instantiated instance of the KATBeaconManager
 * @since v1.0
 */
+ (instancetype _Nullable)shared;


/**
 * Inits the KATBeaconManager
 *
 * @param configuration trigger configuration
 *
 * @return instancetype a KATBeaconManager instance with configuration settings
 * @since v1.0
 */
- (instancetype _Nullable)initWithConfiguration:(KATConfiguration * _Nullable)configuration;


////////////////////////////////////////////////////////////////////////////////
/// @name Start on stop of beacon monitoring/ranging
////////////////////////////////////////////////////////////////////////////////


/**
 * Starts monitoring/ranging for beacons and makes calls to the block callback.
 * This also depends on the beacon configuration on the backend.
 *
 * @return void
 * @since v1.7.8
 */
- (void)startCollecting;


/**
 * The trgger callback get called when the sdk sends requests to the backend
 *
 * @param handler the callback function when triggered
 *
 * @return void
 * @since v1.1.8
 */
- (void)triggerWithHandler:(KATTriggerHandler _Nonnull)handler;


/**
 * The handler gets called at different locations to help debugging.
 * This also depends on the beacon configuration on the backend.
 *
 * @param handler the callback for various debug calls
 *
 * @return void
 * @since v1.0
 */
- (void)debugWithHandler:(KATDebugHandler _Nonnull)handler;


/**
 * Enables single event tracking for more backend analytics data
 *
 * @param event type
 * @param data usually key-value pairs of additional data
 *
 * @return void
 * @since v1.1.4
 */
- (void)trackEvent:(KATTrackingEvent)event payload:(id _Nullable)data;


/**
 * Get the current known region state.
 * This is available once the state was determined during init.
 *
 * @return CLRegionState
 * @since v1.0.7
 */
- (CLRegionState)regionState;


/**
 * Stops monitoring and ranging beacons, it does not destroy the object.
 * Calling the startWithHandler: will activate the monitoring/ranging again.
 *
 * @return void
 * @since v1.7.8
 */
- (void)stopCollecting;


@end
