package com.example.dust
import io.reactivex.Observable
import retrofit2.http.GET
import retrofit2.http.Headers
import retrofit2.http.Path
import retrofit2.http.Query

interface DustApi {
    @Headers("Accept: application/json")
    //@GET("?ServiceKey={ServiceKey}&numOfRows={numOfRows}&pageNo={pageNo}&stationName={stationName}&dataTerm={dataTerm}&ver={ver}")
    @GET("getCtprvnMesureSidoLIst?ServiceKey=%2BB4mEuYXgI2Oh7shu6mo3fX%2BzLK2OeJ20rJgUb3QQxpOmBOx8gAzH5yqCyalQRDtifOX00mNzP7iBudjvdWqwg%3D%3D&_returnType=json")
    fun getPmGrade(@Query("StationName") stationName:String
    ):Observable<DustApiClass>
}