package com.example.flashlight

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val torch = Torch(this)

        flashSwitch.setOnCheckedChangeListener {
            _, isChecked ->
            val intent = Intent(this, TorchService::class.java)
            if (isChecked) {
                intent.action = "on"
            } else {
                intent.action = "off"
            }
            startService(intent)
        }
    }
}