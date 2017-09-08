package ru.my_rabbit.max.bttrack;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.Set;

public class MainActivity extends AppCompatActivity {

    Button btnScan;
    Button btnJoystick;
    ListView lstDevices;
    TextView txtInfo;
    private BluetoothAdapter bt = null;
    private Set<BluetoothDevice> devices;
    public static String EXTRA_ADDRESS = "device_address";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        lstDevices = (ListView) findViewById(R.id.lstDevices);
        btnScan = (Button) findViewById(R.id.btnScan);
        btnJoystick = (Button) findViewById(R.id.btnJoystick);
        txtInfo = (TextView) findViewById(R.id.txtInfo);
        checkBt();
        btnScan.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                txtInfo.setText("Clicked!");
                searchDevices();
                Toast.makeText(getApplicationContext(), "Clicked.", Toast.LENGTH_LONG).show();
            }
        });

        btnJoystick.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(MainActivity.this, TrackActivity.class);

                i.putExtra(EXTRA_ADDRESS, "test");
                startActivity(i);
            }
        });

    }

    private void checkBt() {
        bt = BluetoothAdapter.getDefaultAdapter();
        if (bt == null) {
            Toast.makeText(getApplicationContext(), "Bluetooth device is not availale.", Toast.LENGTH_LONG).show();
        } else if (!bt.isEnabled()) {
            Intent turnBTon = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(turnBTon, 1);

        }
    }


    private void searchDevices() {
        if (bt == null) {
            Toast.makeText(getApplicationContext(), "Bluetooth is not available", Toast.LENGTH_LONG).show();
            return;
        }

        devices = bt.getBondedDevices();
        boolean empty = devices.isEmpty();
        if (empty) {
            Toast.makeText(getApplicationContext(), "No devices found", Toast.LENGTH_LONG).show();
        }

        ArrayList list = new ArrayList();

        if (!empty) {
            for (BluetoothDevice bt : devices) {
                list.add(bt.getName() + "\n" + bt.getAddress()); //Get the device's name and the address
            }
            Toast.makeText(getApplicationContext(), "Filled.", Toast.LENGTH_LONG).show();
        }
        final ArrayAdapter adapter = new ArrayAdapter(this, android.R.layout.simple_list_item_1, list);
        lstDevices.setAdapter(adapter);
        lstDevices.setOnItemClickListener(myListClickListener);

    }

    private AdapterView.OnItemClickListener myListClickListener = new AdapterView.OnItemClickListener() {
        public void onItemClick(AdapterView av, View v, int arg2, long arg3) {

            // Get the device MAC address, the last 17 chars in the View
            String info = ((TextView) v).getText().toString();
            String address = info.substring(info.length() - 17);
            // Make an intent to start next activity.
            Toast.makeText(getApplicationContext(), info + " - " + address, Toast.LENGTH_LONG).show();

            Intent i = new Intent(MainActivity.this, TrackActivity.class);

            i.putExtra(EXTRA_ADDRESS, address);
            startActivity(i);
        }
    };


}
