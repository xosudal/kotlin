package com.example.galley

import android.Manifest
import android.app.AlertDialog
import android.app.Dialog
import androidx.fragment.app.Fragment
import android.content.DialogInterface
import android.content.Intent
import android.content.pm.PackageManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.provider.MediaStore
import android.util.Log
import android.widget.Toast
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import androidx.fragment.app.DialogFragment
import androidx.fragment.app.FragmentActivity
import androidx.viewpager2.widget.ViewPager2
import kotlinx.android.synthetic.main.activity_main.*
import kotlin.concurrent.timer
import kotlin.system.exitProcess

class MainActivity : FragmentActivity() {
    private val REQUEST_READ_EXTERNAL_STORAGE = 1000
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        checkPermission()
    }

    private fun getAllPicture() {
        val cursor = contentResolver.query(MediaStore.Images.Media.EXTERNAL_CONTENT_URI,
            null,
            null,
            null,MediaStore.Images.Media.DATE_TAKEN + " DESC")

        val fragments = ArrayList<Fragment>()
        if (cursor!=null) {
            while (cursor.moveToNext()) {
                val uri = cursor.getString(cursor.getColumnIndexOrThrow(MediaStore.Images.Media.DATA))
                Log.d("heo",uri)
                fragments.add(PhotoFragment.newInstance(uri))
            }
            cursor.close()
        } else {
            Log.e("heo","there is no picture!")
        }

        val adapter = MyPagerAdapter(this)
        adapter.updateFragments(fragments)
        viewPager2.adapter = adapter

        timer(period = 2000) {
            runOnUiThread {
                if (viewPager2.currentItem < adapter.itemCount - 1) {
                    viewPager2.currentItem += 1
                } else {
                    viewPager2.currentItem = 0
                }
            }
        }
    }

    private fun checkPermission() {
        // 권한 부여 확인
        if (ContextCompat.checkSelfPermission(this,Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
            Log.d("heo","permission false")
            // 이미 해당 권한에 관한 요청을 거절한 경우.. 설명 제공을 위해 아래 method 사용
            if (ActivityCompat.shouldShowRequestPermissionRationale(this,Manifest.permission.READ_EXTERNAL_STORAGE)) {
                // 사용자가 이전에 요청을 거부한 경우, alert dialog를 통해 권한 요청하기 (yes or no)
                showDialog()
            } else {
                // 사용자가 권한을 거부하고 권한 요청 대화상자에서 다시 묻지 않음 옵션 선택 혹은 기기 정책상 권한 금지 경우
                ActivityCompat.requestPermissions(this, arrayOf(Manifest.permission.READ_EXTERNAL_STORAGE), REQUEST_READ_EXTERNAL_STORAGE)
            }
        } else { // 이미 권한 부여됨. 시작
            Log.d("heo","permission true")
            getAllPicture()
        }
    }

    private fun showDialog() {
        var dialog = AlertDialog.Builder(this)
        dialog.setTitle("권한 요청")
        dialog.setMessage("yes를 누르시는게 신상에 좋습니다.")
        var dialogListener = DialogInterface.OnClickListener { p0, p1 ->
            when(p1) {
                DialogInterface.BUTTON_POSITIVE ->
                    ActivityCompat.requestPermissions(this@MainActivity, arrayOf(Manifest.permission.READ_EXTERNAL_STORAGE), REQUEST_READ_EXTERNAL_STORAGE)
                DialogInterface.BUTTON_NEGATIVE ->
                    Toast.makeText(this@MainActivity,"유감",Toast.LENGTH_SHORT).show()
                DialogInterface.BUTTON_NEUTRAL -> {
                    finishAffinity()
                    System.runFinalization()
                    exitProcess(0)
                }
            }
        }
        dialog.setPositiveButton("Yes",dialogListener)
        dialog.setNegativeButton("No",dialogListener)
        dialog.setNeutralButton("Cancel", dialogListener)
        dialog.show()
    }

    // 권한 요청 결과를 알 수 있음
    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>,
        grantResults: IntArray // 요청한 권한들의 결과 값 GRANTED or DENIED를 return함
    ) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        when (requestCode) {
            REQUEST_READ_EXTERNAL_STORAGE -> {
                if (grantResults.isNotEmpty() && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    getAllPicture()
                } else {
                    Toast.makeText(this@MainActivity, "유감... 권한 거부됨", Toast.LENGTH_SHORT).show()
                }
                return
            }
        }
    }
}