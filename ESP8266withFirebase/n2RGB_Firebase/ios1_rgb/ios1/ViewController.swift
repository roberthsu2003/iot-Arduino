//
//  ViewController.swift
//  ios1
//
//  Created by mac on 2017/7/3.
//  Copyright © 2017年 gjun. All rights reserved.
//

import UIKit
import Firebase

class ViewController: UIViewController {
    var ref: DatabaseReference!
    var rgbSwitchRef:DatabaseReference!
    
    @IBOutlet weak var seg: UISegmentedControl!
    override func viewDidLoad() {
        super.viewDidLoad()
        ref = Database.database().reference();
        rgbSwitchRef = ref.child("RGBSwitch");
        rgbSwitchRef.observeSingleEvent(of: .value) { (dataSnapshot:DataSnapshot) in
            if let values = dataSnapshot.value as? [String:Bool]{
                let rState = values["R"]!;
                let gState = values["G"]!;
                let bState = values["B"]!;
                switch (rState,gState,bState){
                case (_,_,true):
                    self.seg.selectedSegmentIndex = 2;
                case (_,true,_):
                    self.seg.selectedSegmentIndex = 1;
                case (true,_,_):
                    self.seg.selectedSegmentIndex = 0;
                default:break;
                }
            }
        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    @IBAction func userChange(_ sender: UISegmentedControl) {
        switch sender.selectedSegmentIndex{
        case 0:
            print("red");
            /*
            rgbSwitchRef.updateChildValues(["R":true]);
            rgbSwitchRef.updateChildValues(["G":false]);
            rgbSwitchRef.updateChildValues(["B":false]);
 */
            rgbSwitchRef.child("R").setValue(true);
            rgbSwitchRef.child("G").setValue(false);
            rgbSwitchRef.child("B").setValue(false);
        case 1:
            rgbSwitchRef.updateChildValues(["R":false]);
            rgbSwitchRef.updateChildValues(["G":true]);
            rgbSwitchRef.updateChildValues(["B":false]);
        case 2:
            rgbSwitchRef.updateChildValues(["R":false]);
            rgbSwitchRef.updateChildValues(["G":false]);
            rgbSwitchRef.updateChildValues(["B":true]);
        default:break;
        }
    }

}

