package com.example.lufa_aoa_test;

import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

import android.os.Bundle;
import android.os.ParcelFileDescriptor;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.View;
import android.widget.*;
import com.android.future.usb.*;

public class MainActivity extends Activity {
	private UsbManager mUSBManager;
	private UsbAccessory mAccessoryDevice;
	private ParcelFileDescriptor mFileDescriptor;
	private FileInputStream mInputStream;
	private FileOutputStream mOutputStream;
	
	public void changeLEDState(View v) {
		boolean newButtonState = ((ToggleButton)v).isChecked();
		
		if (mOutputStream != null) {
			try {
				mOutputStream.write(newButtonState ? 0x01 : 0x00);
			}
			catch (IOException e)
			{
				
			}
		}
	}

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        Intent intent = getIntent();
        
        if ((intent != null) && (intent.getAction() == com.android.future.usb.UsbManager.ACTION_USB_ACCESSORY_ATTACHED))
        {
            mUSBManager = UsbManager.getInstance(this);
            if (mUSBManager != null)
            {            
	        	mAccessoryDevice = UsbManager.getAccessory(intent);
	        	mFileDescriptor = mUSBManager.openAccessory(mAccessoryDevice);

	        	FileDescriptor fd = mFileDescriptor.getFileDescriptor();
	            mInputStream = new FileInputStream(fd);
	            mOutputStream = new FileOutputStream(fd);
            }
        }
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
}
