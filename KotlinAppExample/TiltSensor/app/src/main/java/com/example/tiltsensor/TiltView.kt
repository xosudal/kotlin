package com.example.tiltsensor

import android.content.Context
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Paint
import android.hardware.SensorEvent
import android.view.View

class TiltView(context: Context?) : View(context) {
    private val greenPaint : Paint = Paint()
    private val blackPaint : Paint = Paint()
    private var cX : Float = 0f
    private var cY : Float = 0f
    private var xCoord : Float = 0f
    private var yCoord : Float = 0f
    init {
        greenPaint.color = Color.GREEN
        blackPaint.style = Paint.Style.STROKE // 외곽선만 그린다
    }

    override fun onDraw(canvas: Canvas?) {
        canvas?.drawCircle(cX, cY, 100f, blackPaint)
        canvas?.drawLine(cX-20, cY, cX+20, cY, blackPaint)
        canvas?.drawLine(cX, cY-20, cX, cY+20, blackPaint)
        canvas?.drawCircle(cX + xCoord, cY + yCoord, 100f, greenPaint)
    }

    override fun onSizeChanged(w: Int, h: Int, oldw: Int, oldh: Int) {
        cX = w/2f
        cY = h/2f
    }

    fun onSensorChanged(sensor: SensorEvent?) {
        sensor?.let {
            xCoord = it.values[1] * 20
            yCoord = it.values[0] * 20
        }
        invalidate() // onDraw를 다시 함
    }
}