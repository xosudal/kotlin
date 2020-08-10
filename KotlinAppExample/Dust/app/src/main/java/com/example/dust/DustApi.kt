package com.example.dust
import io.reactivex.Observable
import io.reactivex.Single
import retrofit2.http.GET
import retrofit2.http.Headers
import retrofit2.http.Path
import retrofit2.http.Query

interface DustApi {
    @Headers("Accept: application/json")

    @GET("getMsrstnAcctoRltmMesureDnsty?ServiceKey=%2BB4mEuYXgI2Oh7shu6mo3fX%2BzLK2OeJ20rJgUb3QQxpOmBOx8gAzH5yqCyalQRDtifOX00mNzP7iBudjvdWqwg%3D%3D")
    fun getWeather(@Query("stationName") stationName:String,
                   @Query("dataTerm") dataTerm:String,
                   //@Query("ServiceKey") ServiceKey:String,
                   @Query("pageNo") PageNo:String,
                   @Query("numOfRows") numOfRows:String,
                   @Query("_returnType") returnType:String
    ): Single<DustApiClass>
}