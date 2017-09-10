package ru.my_rabbit.max.bttrack;

import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.content.Intent;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.AttributeSet;
import android.util.StringBuilderPrinter;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.util.Dictionary;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.UUID;

import static android.R.attr.left;
import static android.R.attr.right;


public class TrackActivity extends AppCompatActivity implements JoystickListener {
    Button btnToggle, btnDisconnect;
    String address = null;
    BluetoothAdapter bt = null;
    BluetoothSocket btSocket = null;
    TextView txtInfo;
    private boolean isBtConnected = false;
    static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    private ProgressDialog progress;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_track);
        txtInfo = (TextView) findViewById(R.id.txtInfo);
        btnDisconnect = (Button) findViewById(R.id.btnDisconnect);
        btnToggle = (Button) findViewById(R.id.btnToggle);


        //receive the address of the bluetooth device
        Intent newint = getIntent();
        address = newint.getStringExtra(MainActivity.EXTRA_ADDRESS);

        btnDisconnect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Disconnect();
            }
        });

        new ConnectBT().execute();

    }

    private void msg(String s) {
        Toast.makeText(getApplicationContext(), s, Toast.LENGTH_LONG).show();
    }

    private void Disconnect() {
        if (btSocket != null) //If the btSocket is busy
        {
            try {
                btSocket.close(); //close connection
            } catch (IOException e) {
                msg("Error");
            }
        }
        finish(); //return to the first layout
    }

    @Override
    public void onJoystickMoved(float xPercent, float yPercent, RobustDirection direction, int source) {
        txtInfo.setText("X: " + xPercent + " Y: " + yPercent + "\n direction: " + direction.toString());

        if(directionCommands.containsKey(direction))
            sendCommand(directionCommands.get(direction));
    }

    HashMap<RobustDirection, String> directionCommands = new HashMap<RobustDirection, String>(){
        {
            put(RobustDirection.FORWARD, CommandDictionary.CMD_FORWARD);
            put(RobustDirection.BACK, CommandDictionary.CMD_BACK);
            put(RobustDirection.LEFT, CommandDictionary.CMD_LEFT);
            put(RobustDirection.RIGHT, CommandDictionary.CMD_RIGHT);
            put(RobustDirection.STOP, CommandDictionary.CMD_STOP);
        }
    };

    private void sendCommand(String command){
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write(command.getBytes());
            }
            catch (IOException e)
            {
                msg("Error: " + e.getMessage());
            }
        }
    }

    private class ConnectBT extends AsyncTask<Void, Void, Void>  // UI thread
    {
        private boolean ConnectSuccess = true; //if it's here, it's almost connected

        @Override
        protected void onPreExecute() {
            progress = ProgressDialog.show(TrackActivity.this, "Connecting...", "Please wait!!!");  //show a progress dialog
        }

        @Override
        protected Void doInBackground(Void... devices) //while the progress dialog is shown, the connection is done in background
        {
            try {
                if (btSocket == null || !isBtConnected) {
                    bt = BluetoothAdapter.getDefaultAdapter();//get the mobile bluetooth device
                    BluetoothDevice dispositivo = bt.getRemoteDevice(address);//connects to the device's address and checks if it's available
                    btSocket = dispositivo.createInsecureRfcommSocketToServiceRecord(myUUID);//create a RFCOMM (SPP) connection
                    BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                    btSocket.connect();//start connection
                }
            } catch (IOException e) {
                ConnectSuccess = false;//if the try failed, you can check the exception here
            }
            return null;
        }

        @Override
        protected void onPostExecute(Void result) //after the doInBackground, it checks if everything went fine
        {
            super.onPostExecute(result);

            if (!ConnectSuccess) {
                msg("Connection Failed. Is it a SPP Bluetooth? Try again.");
                finish();
            } else {
                msg("Connected.");
                isBtConnected = true;
            }
            progress.dismiss();
        }
    }
}
