package com.robert.bluno.blunoTemperature;

import android.os.Bundle;
import android.content.Intent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;


public class MainActivity  extends BlunoLibrary {
	private Button buttonScan;
	private TextView valueTextView;

	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
        onCreateProcess();														//onCreate Process by BlunoLibrary


        serialBegin(115200);													//set the Uart Baudrate on BLE chip to 115200

        		//initial the button for sending the data


        buttonScan = (Button) findViewById(R.id.buttonScan);
		valueTextView = (TextView) findViewById(R.id.valueTextView);



        buttonScan.setOnClickListener(new OnClickListener() {               //initial the button for scanning the BLE device

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub

				buttonScanOnClickProcess();										//Alert Dialog for selecting the BLE device
			}
		});
	/*
		buttonOpen.setOnClickListener(new View.OnClickListener(){

			@Override
			public void onClick(View view) {
				//android代碼98
				char action = 98;
				serialSend(Character.toString(action));

				//功能識別
				action = 2;
				serialSend(Character.toString(action));

				//送出功能值
				action = 1;
				serialSend(Character.toString(action));

				//送出結束值
				action = 100;
				serialSend(Character.toString(action));
			}
		});
		*/
		/*

		buttonClose.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View view) {
				char action = 98;
				serialSend(Character.toString(action));

				//功能識別
				action = 2;
				serialSend(Character.toString(action));

				//送出功能值
				action = 0;
				serialSend(Character.toString(action));

				//送出結束值
				action = 100;
				serialSend(Character.toString(action));
			}
		});
		*/
	}

	protected void onResume(){
		super.onResume();
		System.out.println("BlUNOActivity onResume");
		onResumeProcess();														//onResume Process by BlunoLibrary
	}
	
	
	
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		onActivityResultProcess(requestCode, resultCode, data);					//onActivityResult Process by BlunoLibrary
		super.onActivityResult(requestCode, resultCode, data);
	}
	
    @Override
    protected void onPause() {
        super.onPause();
        onPauseProcess();														//onPause Process by BlunoLibrary
    }
	
	protected void onStop() {
		super.onStop();
		onStopProcess();														//onStop Process by BlunoLibrary
	}
    
	@Override
    protected void onDestroy() {
        super.onDestroy();	
        onDestroyProcess();														//onDestroy Process by BlunoLibrary
    }

	@Override
	public void onConectionStateChange(connectionStateEnum theConnectionState) {//Once connection state changes, this function will be called
		switch (theConnectionState) {											//Four connection state
		case isConnected:
			buttonScan.setText("Connected");
			//android代碼98
			char action = 98;
			serialSend(Character.toString(action));

			//功能識別
			action = 2;
			serialSend(Character.toString(action));

			//送出功能值
			action = 1;
			serialSend(Character.toString(action));

			//送出結束值
			action = 100;
			serialSend(Character.toString(action));
			break;
		case isConnecting:
			buttonScan.setText("Connecting");
			break;
		case isToScan:
			buttonScan.setText("Scan");
			break;
		case isScanning:
			buttonScan.setText("Scanning");
			break;
		case isDisconnecting:
			buttonScan.setText("isDisconnecting");
			break;
		default:
			break;
		}
	}

	@Override
	public void onSerialReceived(String theString) {							//Once connection data received, this function will be called
		// TODO Auto-generated method stub
		//serialReceivedText.append(theString);							//append the text into the EditText
		//The Serial data from the BLUNO may be sub-packaged, so using a buffer to hold the String is a good choice.
		//((ScrollView)serialReceivedText.getParent()).fullScroll(View.FOCUS_DOWN);
		//char action = theString.charAt(0);
		System.out.println(theString);
		valueTextView.setText(theString);
	}








}