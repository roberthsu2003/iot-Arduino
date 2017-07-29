//
//  ViewController.swift
//  ios1
//
//  Created by mac on 2017/6/20.
//  Copyright © 2017年 led_DataBase. All rights reserved.
//

import UIKit
import Firebase

class ViewController: UIViewController {
   
    var ledRef:DatabaseReference!
    var isOn = false;
    
    @IBOutlet weak var ligthBtn: UIButton!
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        ledRef =  Database.database().reference().child("led");
        ledRef.observe(.value) { (snapshot:DataSnapshot) in
            let ledNode = snapshot.value as? [String:Bool] ?? [:];
            //print(ledNode["D2"]!);
            self.isOn = ledNode["D2"]!;
            let imageName = self.isOn ? "light_on" : "light_off";
            let image = UIImage(named: imageName);
            self.ligthBtn.setImage(image, for: UIControlState.normal);
            
        }
 
 
        
    }

    @IBAction func userClick(_ sender: UIButton) {
       
        isOn = !isOn;
        ledRef.child("D2").setValue(isOn);
 
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

