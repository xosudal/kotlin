package com.example.tiltsensor


import android.content.Context
import android.content.pm.ActivityInfo
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.WindowManager

class MainActivity : AppCompatActivity(), SensorEventListener {
    private val TAG = "tiltSensorMain"
    private lateinit var tiltView : TiltView

    private val sensorManager by lazy {
        // in java (SensorManager)getSystemService(Context.SENSOR_SERVICE)
        getSystemService(Context.SENSOR_SERVICE) as SensorManager // casting through as SensorManager
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        window.addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON) // 화면이 꺼지지 않게 하기
        requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE // 가로로 고정하기
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        tiltView = TiltView(this)
        setContentView(tiltView)
    }

    override fun onStart() {
        super.onStart()
        Log.d(TAG,"onStart()")
    }

    override fun onResume() {
        super.onResume()
        sensorManager.registerListener(this, sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_NORMAL)
    }

    override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) {
        Log.d(TAG,"[onAccuracyChanged] $sensor, $accuracy")
    }

    override fun onSensorChanged(p: SensorEvent?) {
        p?.let {
            Log.d(TAG,"[onSensorChanged] X : ${it.values[0]}, Y : ${it.values[1]}, Z : ${it.values[2]}")
        }
        tiltView.onSensorChanged(p)
        //Log.d(TAG,"[onSensorChanged] X : ${p?.values?.get(0)}, Y : ${p?.values?.get(1)}, Z : ${p?.values?.get(2)}")
    }

    override fun onPause() {
        super.onPause()
        Log.d(TAG,"[onPause] unregister sensor listener")
        sensorManager.unregisterListener(this)
    }


}