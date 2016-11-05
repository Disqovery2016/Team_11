package com.example.gps3;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.sqlite.SQLiteDatabase;
import android.location.Location;
import android.location.LocationManager;
import android.os.Bundle;
import android.provider.Settings;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;
//import android.net.Uri;
import android.widget.TextView;
public class MainActivity extends Activity {

SQLiteDatabase sq;
Button btnGPSShowLocation;
Button btnNWShowLocation;
TextView txt1;
TextView txt2;
AppLocationService appLocationService;

@Override
protected void onCreate(Bundle savedInstanceState) {
super.onCreate(savedInstanceState);
setContentView(R.layout.activity_main);
/* store the latitude and longitude values in database */
sq=MainActivity.this.openOrCreateDatabase("Curser",MODE_PRIVATE,null);
sq.execSQL("create table if not exists border_location(latitude1 double(20),longitude1" +" double(20));");
//sq.execSQL("insert into border_location values('+13.11987281 +','+80.20543895+');");
Toast.makeText(getApplicationContext(),"Database created",Toast.LENGTH_LONG).show();
appLocationService = new AppLocationService(
        MainActivity.this);

btnGPSShowLocation = (Button) findViewById(R.id.btnGPSShowLocation);
btnGPSShowLocation.setOnClickListener(new View.OnClickListener() {
    @Override
    public void onClick(View arg0) {

        Location gpsLocation = appLocationService.getLocation(LocationManager.GPS_PROVIDER);

        if (gpsLocation != null) {
            double latitude = gpsLocation.getLatitude();
            double longitude = gpsLocation.getLongitude();
           txt1.setText(Double.toString(latitude));
           txt2.setText(Double.toString(longitude));
            Toast.makeText(
                    getApplicationContext(),
                    "Mobile Location (GPS): \nLatitude: " + latitude
                            + "\nLongitude: " + longitude,
                    Toast.LENGTH_LONG).show();
            }
        else 
            {
            showSettingsAlert("GPS");
        }
    }
    });


btnNWShowLocation = (Button) findViewById(R.id.btnNWShowLocation);
btnNWShowLocation.setOnClickListener(new View.OnClickListener() {
    @Override
    public void onClick(View arg0) {

        Location nwLocation = appLocationService
                .getLocation(LocationManager.NETWORK_PROVIDER);

        if (nwLocation != null) {
            double latitude = nwLocation.getLatitude();
            double longitude = nwLocation.getLongitude();
            Toast.makeText(
                    getApplicationContext(),
                    "Mobile Location (NW): \nLatitude: " + latitude
                            + "\nLongitude: " + longitude,
                    Toast.LENGTH_LONG).show();
        } else {
            showSettingsAlert("NETWORK");
        }

    }
});


}

public void showSettingsAlert(String provider) {
AlertDialog.Builder alertDialog = new AlertDialog.Builder(
        MainActivity.this);

alertDialog.setTitle(provider + " SETTINGS");

alertDialog.setMessage(provider + " is not enabled! Want to go to settings menu?");

alertDialog.setPositiveButton("Settings",
        new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int which) {
                Intent intent = new Intent(
                        Settings.ACTION_LOCATION_SOURCE_SETTINGS);
                MainActivity.this.startActivity(intent);
            }
        });

alertDialog.setNegativeButton("Cancel",
        new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int which) {
                dialog.cancel();
            }
        });

alertDialog.show();
}


//  @Override
// public boolean onCreateOptionsMenu(Menu menu) {
//   getMenuInflater().inflate(R.menu.menu_activity_main, menu);
// return true;
//}

}
