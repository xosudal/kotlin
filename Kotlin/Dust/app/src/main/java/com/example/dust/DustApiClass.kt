package com.example.dust

import com.google.gson.annotations.SerializedName

class DustApiClass {
    @SerializedName("list") var list = ArrayList<List>()
}

class List {
    @SerializedName("pm10Value") var pm10Value: Float = 0.toFloat()
}