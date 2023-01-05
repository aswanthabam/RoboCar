package com.gct.deptofcs.robocar;

import android.app.*;
import android.os.*;
import android.view.*;
import android.widget.*;
import android.support.v7.app.*;
import android.content.*;
import android.bluetooth.*;

public class MainActivity extends AppCompatActivity
{
	private Button right,left,front,back;
	private RadioGroup mode;
	private CheckBox gear,voice;
	private Bluetooth bluetooth;
	private Spinner selector;
	private LinearLayout status;
	private AppCompatActivity activity;
	private TextView textStatus;
	private ImageView textImg;
	private int state = 1;
	
	public static final int BLUETOOTH_OFF = 1;
	public static final  int BLUETOOTH_ON = 2;
	public static final  int BLUETOOTH_CONNECTED = 3;
	public static final  int BLUETOOTH_NOT_CONNECTED = 4;
	
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.main);
		bluetooth = new Bluetooth(this);
		activity = this;
		right = findViewById(R.id.btn_right);
		left = findViewById(R.id.btn_left);
		front = findViewById(R.id.btn_forward);
		back = findViewById(R.id.btn_backward);
		gear = findViewById(R.id.check_gear);
		voice = findViewById(R.id.btn_voice);
		status = findViewById(R.id.linear_status);
		textStatus = findViewById(R.id.text_status);
		textImg = findViewById(R.id.text_statusImg);
		selector = findViewById(R.id.spinner_selector);
		if(!bluetooth.getAdapter().isEnabled()){
			textStatus.setText("Turn on bluetooth");
			state = BLUETOOTH_OFF;
		}
		else{
			state = BLUETOOTH_ON;
			textStatus.setText("Not connected");
		}
		status.setOnClickListener(new View.OnClickListener(){
			public void onClick(View v)
			{
				switch(state){
					case BLUETOOTH_OFF:
						bluetooth.on();
						break;
					case BLUETOOTH_ON:
						DeviceDialog dia = new DeviceDialog(activity,bluetooth);
						dia.show();
						break;
					case BLUETOOTH_CONNECTED:
						textStatus.setText("Connected");
						break;
					
				}
				
			}
		});
		/*ArrayAdapter<String> dataAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, bluetooth.list().toArray(new String[]{}));

		// Drop down layout style - list view with radio button
		dataAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

		// attaching data adapter to spinner
		
		selector.setAdapter(dataAdapter);*/
		
		
		
    }
}
