package com.example.dust

import com.google.gson.annotations.SerializedName

class DustApiClass(
    @SerializedName("pm10Value") val pmValue: String

)