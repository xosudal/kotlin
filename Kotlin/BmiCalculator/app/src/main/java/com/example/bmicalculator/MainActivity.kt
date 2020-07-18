package com.example.bmicalculator

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.preference.PreferenceManager
import kotlinx.android.synthetic.main.activity_main.*
import org.jetbrains.anko.*

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        loadData()

        resultButton.setOnClickListener {
            var weightStr = weightEditText.text.toString()
            var heightStr = heightEditText.text.toString()
            saveData(heightStr.toInt(),weightStr.toInt())
            startActivity<ResultActivity>(
                "weight" to weightStr,
                "height" to heightStr
            )
        }
    }
    private fun saveData(height:Int, weight:Int) {
        val pref = PreferenceManager.getDefaultSharedPreferences(this)
        val editor = pref.edit()
        editor.putInt("WEIGHT", weight)
            .putInt("HEIGHT",height)
            .apply()
    }
    private fun loadData() {
        val pref = PreferenceManager.getDefaultSharedPreferences(this)
        val weight = pref.getInt("WEIGHT", 0)
        val height = pref.getInt("HEIGHT", 0)
        if (height!=0 && weight !=0) {
            weightEditText.setText(weight.toString())
            heightEditText.setText(height.toString())
        }
    }
}