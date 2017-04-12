package com.example.t.velengestest;

import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.opengl.GLSurfaceView;
import android.opengl.GLSurfaceView.Renderer;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.util.Log;
import android.widget.Button;
import android.widget.TextView;
import android.widget.EditText;
import android.content.Intent;
import android.support.v4.app.Fragment;


public class MainActivity extends AppCompatActivity {
    static
    {
        System.loadLibrary("NativeLib");
    }

    public static final String EXTRA_MESSAGE = "com.example.t.velengestest.MESSAGE";
    TextView totalTextView;
    EditText percentageText;
    EditText numberText;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.d("TKT", "OnCreate");
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        totalTextView = (TextView) findViewById(R.id.totalTextView);
        percentageText = (EditText) findViewById(R.id.percentageText);
        numberText = (EditText) findViewById(R.id.numberText);

        Button calcButton = (Button) findViewById(R.id.calculateButton);
        calcButton.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                float percentage = Float.parseFloat(percentageText.getText().toString());
                percentage = percentage / 100;
                float num = Float.parseFloat(numberText.getText().toString());
                float total = percentage * num;
                totalTextView.setText(Float.toString((total)));
            }
        });
    }



    public void MakeSecondActivity(View view)
    {
        Intent in = new Intent(this, SecondActivity.class);
        EditText edTxt = (EditText) findViewById(R.id.messangeEditText);
        String message = edTxt.getText().toString();
        in.putExtra(EXTRA_MESSAGE, message);
        startActivity(in);
    }

    public void MakeOpenGLActivity(View view)
    {
        Intent in = new Intent(this, OpenGLActivity.class);
        startActivity(in);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

}
