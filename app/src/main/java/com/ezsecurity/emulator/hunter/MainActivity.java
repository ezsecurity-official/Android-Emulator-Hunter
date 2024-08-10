package com.ezsecurity.emulator.hunter;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("ezsecurity");
    }

    // Natives
    private native void initiateEmulatorScan();

    // UI elements
    private LinearLayout scanResultsContainer;
    private Button scanButton;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Initialize UI elements
        scanResultsContainer = findViewById(R.id.container_scanned);
        scanButton = findViewById(R.id.button_scan);

        // Set up the button click listener
        scanButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                initiateEmulatorScan();
            }
        });
    }

    // Method to display logs in the UI
    public void displayLogMessage(String message, int status)
    {
        TextView logTextView = new TextView(getApplicationContext());
        logTextView.setText(message);
        logTextView.setTextSize(14);

        // Set text color based on status
        switch (status)
        {
            case 0:
                logTextView.setTextColor(0xFF9DCD5A); // Green for success
                break;
            case 1:
                logTextView.setTextColor(0xFFEADC1E); // Yellow for warning
                break;
            case 2:
                logTextView.setTextColor(0xFFFF0000); // Red for error
                break;
            default:
                logTextView.setTextColor(0xFF000000); // Default color
                break;
        }

        // Add the log message to the container
        scanResultsContainer.addView(logTextView);
    }
}