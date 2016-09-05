//
//  AppDelegate.swift
//  SampleSwift
//
//  Created by Sven Röder on 2016-09-05.
//  Copyright © 2016 Glimr AB. All rights reserved.
//

import UIKit
import KatalysatorSDK

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {
    
    var window: UIWindow?
    
    static let GLIMR_API_TOKEN = UUID(uuidString: "B3945743-D258-49D0-AFBF-1E409AE59501")

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [NSObject: AnyObject]?) -> Bool {
        
        // START COLLECTING
        let config = KATConfiguration()
        config.apiToken = AppDelegate.GLIMR_API_TOKEN
        config.suppressBluetoothAccuracyAlert = true
        config.askForLocationPermission = true
        
        let glimrManager = KATBeaconManager(configuration: config)!
        glimrManager.startCollecting()
        
        glimrManager.debug(handler: { (result) in
            print("DEBUG", result)
        })

        return true
    }
    
    
    func applicationDidBecomeActive(_ application: UIApplication) {
        
        // RECEIVE TAGS
        let audienceManager = KATAudienceManager(apiToken: AppDelegate.GLIMR_API_TOKEN)
        audienceManager?.audiences(completion: { (audiences, error) in
            print("AUDIENCES \(audiences)")
        })
    }

}

