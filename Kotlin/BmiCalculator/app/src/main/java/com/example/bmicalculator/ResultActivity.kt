package com.example.bmicalculator

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_result.*
import org.jetbrains.anko.toast
import kotlin.math.pow

class ResultActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_result)

        val weight = intent.getStringExtra("weight")!!.toInt()
        val height = intent.getStringExtra("height")!!.toInt()

        val bmi = weight / (height / 100.0).pow(2.0)

        resultTextView.text = when {
            bmi >= 35 -> "고도 비만"
            bmi >= 30 -> "2단계 비만"
            bmi >= 25 -> "1단계 비만"
            bmi >= 23 -> "과체중"
            bmi >= 18.5 -> "정상"
            else -> "저체중"
        }
        var draw = when {
            bmi >= 23 -> R.drawable.ic_baseline_sentiment_very_dissatisfied_24
            bmi >= 18.5 -> R.drawable.ic_baseline_sentiment_very_satisfied_24
            else -> R.drawable.ic_baseline_sentiment_very_dissatisfied_24
        }

        imageView.setImageResource(draw)

        toast("$bmi")
    }
}