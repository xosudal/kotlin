package com.example.flashlight

import android.app.Service
import android.content.Intent
import android.os.IBinder

class TorchService : Service() {
    private val torch: Torch by lazy {
        Torch(this)
    }

    private var isRunning = false
    override fun onStartCommand(intent: Intent?, flags: Int, startId: Int): Int {
        when (intent?.action) {
            "on" -> torch.flash(true)
            "off" -> torch.flash(false)
            else -> {
                isRunning = !isRunning
                if (isRunning) torch.flash(true)
                else torch.flash(false)
            }
        }
        return super.onStartCommand(intent, flags, startId)
    }

    override fun onBind(intent: Intent): IBinder {
        TODO("Return the communication channel to the service.")
    }
}
