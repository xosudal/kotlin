package com.example.dust

import android.app.Service
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import com.google.gson.Gson
import com.google.gson.GsonBuilder
import io.reactivex.android.schedulers.AndroidSchedulers
import io.reactivex.disposables.CompositeDisposable
import io.reactivex.schedulers.Schedulers
import okhttp3.OkHttpClient
import okhttp3.logging.HttpLoggingInterceptor
import retrofit2.Retrofit
import retrofit2.adapter.rxjava2.RxJava2CallAdapterFactory
import retrofit2.converter.gson.GsonConverterFactory
import retrofit2.http.HTTP

class MainActivity : AppCompatActivity() {
    val disposables = CompositeDisposable()
    val ServiceKey = "%2BB4mEuYXgI2Oh7shu6mo3fX%2BzLK2OeJ20rJgUb3QQxpOmBOx8gAzH5yqCyalQRDtifOX00mNzP7iBudjvdWqwg%3D%3D"
    val stationName = "강서구"
    val PageNo = "1"
    val numOfRows = "1"
    val dataTerm = "DAILY"

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        Log.d("heo","oncreate...")
        getDust()
    }

    private fun getDust() {
        val dust:DustApi = provideDustApi()
        Log.d("heo","asdf")
        disposables.add(dust.getWeather(stationName,dataTerm,PageNo,numOfRows,"json")

            .observeOn(Schedulers.io())

            .subscribe ({
                Log.d("heo","return : ${it.list[0].pm10Value}")
            }) {
                Log.e("heo","error !!!!! ${it.message}")
            }

        )
    }
    private fun provideDustApi(): DustApi {
        val gson:Gson = GsonBuilder()
            .setLenient()
            .create()

        val interceptor = HttpLoggingInterceptor()
        interceptor.setLevel(HttpLoggingInterceptor.Level.BODY);

        val okHttpClient = OkHttpClient.Builder()
            .addInterceptor(interceptor)
            .build()

        val dust = Retrofit.Builder()
            .baseUrl("http://openapi.airkorea.or.kr/openapi/services/rest/ArpltnInforInqireSvc/")
            .addCallAdapterFactory(RxJava2CallAdapterFactory.createAsync())
            .addConverterFactory(GsonConverterFactory.create(gson))
            .client(okHttpClient)
            .build()
            .create(DustApi::class.java)

        return dust
    }
}