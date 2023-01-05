package com.gct.deptofcs.robocar;
import android.app.*;
import android.os.*;
import android.support.v7.app.*;
import android.bluetooth.*;
import java.util.*;
import android.widget.*;

public class DeviceDialog extends Dialog
{
	private AppCompatActivity activity;
	private List<BluetoothDevice> devices = new ArrayList<BluetoothDevice>();
	private List<String> deviceString = new ArrayList<String>();
	private ArrayAdapter adapter;
	private ListView listView;
	private Button close,connect;
	private Bluetooth blue;
	DeviceDialog(AppCompatActivity a,Bluetooth b){
		super(a);
		activity = a;
		//devices = de;
		blue = b;
	}
	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		// TODO: Implement this method
		super.onCreate(savedInstanceState);
		setContentView(R.layout.device_selector);
		
		close = findViewById(R.id.device_selectorClose);
		connect = findViewById(R.id.device_selectorConnect);
		listView = findViewById(R.id.device_selectorListView);
		
		blue.scan();
		blue.setOnDeviceDiscoverListener(new Bluetooth.OnDeviceDiscoveredListener(){
			public void onDiscover(BluetoothDevice device){
				devices.add(device);
				deviceString.add(device.getName());
				listView.setAdapter(adapter);
			}
		});
		
		//for(BluetoothDevice dt : devices) deviceString.add(dt.getName());
		adapter = new ArrayAdapter(activity,android.R.layout.simple_list_item_1,deviceString);
		
		listView.setAdapter(adapter);
	}
	
}
