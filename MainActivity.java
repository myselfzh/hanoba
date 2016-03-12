package com.example.timer;

import java.util.Timer;
import java.util.TimerTask;

import android.os.Bundle;
import android.R.integer;
import android.app.Activity;
import android.content.Loader.ForceLoadContentObserver;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends Activity implements OnClickListener {

	Button btGetTime,btStart,btEnd;
	EditText mEditText;
	TextView mTextView;
	Timer mTimer;
	int time;
	long startTime;
	long endTime;
	int flag=1;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		initview();
	}
	private void initview() {
		// TODO Auto-generated method stub
		btGetTime=(Button)findViewById(R.id.button1);
		btStart=(Button) findViewById(R.id.button2);
		btEnd=(Button) findViewById(R.id.button3);
		mEditText=(EditText) findViewById(R.id.editText1);
		mTextView=(TextView) findViewById(R.id.textView1);
		btGetTime.setOnClickListener(this);
		btStart.setOnClickListener(this);
		btEnd.setOnClickListener(this);
		
	}
	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		switch (v.getId()) {
		case R.id.button1:
			mTextView.setText(mEditText.getText().toString());
			time=Integer.parseInt(mEditText.getText().toString());
			break;
		case R.id.button2:
			if(flag==1)
			{
				mTimer=new Timer();
				startTime=System.currentTimeMillis();
				endTime=startTime+time*1000;
				flag=0;
				mTimer.schedule(new TimerTask() {
					
					@Override
					public void run() {
						// TODO Auto-generated method stub
					
						runOnUiThread(new Runnable() {
							
							
							public void run() {
								int a=Integer.parseInt(mTextView.getText().toString())-1;
								if(a!=0)
								{
									String t=a+"";
								mTextView.setText(t);
								}
								else {
									mTimer.cancel();
									mTextView.setText("");
								}
								
								
							}
						});
						
					}
				},0,1000);
			}else {
				mTimer.cancel();
				flag=1;
			}
			
			break;
		case R.id.button3:
			mTimer.cancel();
			mTextView.setText("");
			flag=1;
	break;

		default:
			break;
		}
	}



}
