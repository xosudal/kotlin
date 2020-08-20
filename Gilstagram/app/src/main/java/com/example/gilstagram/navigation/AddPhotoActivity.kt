package com.example.gilstagram.navigation

import android.app.Activity
import android.content.Intent
import android.net.Uri
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Toast
import com.example.gilstagram.R
import com.example.gilstagram.navigation.model.ContentDTO
import com.google.firebase.auth.FirebaseAuth
import com.google.firebase.firestore.FirebaseFirestore
import com.google.firebase.storage.FirebaseStorage
import kotlinx.android.synthetic.main.activity_add_photo.*
import java.util.Date
import java.text.SimpleDateFormat

class AddPhotoActivity : AppCompatActivity() {
    val TAG = "AddPhotoActivity"
    var PICK_IMAGE_FROM_ALBUM = 0
    var storage:FirebaseStorage? = null
    var photoUri: Uri? = null

    var auth : FirebaseAuth? = null
    var firestore : FirebaseFirestore? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_add_photo)

        storage = FirebaseStorage.getInstance()

        auth = FirebaseAuth.getInstance()
        firestore = FirebaseFirestore.getInstance()

        var photoPickerIntent = Intent(Intent.ACTION_PICK)
        photoPickerIntent.type = "image/*"
        startActivityForResult(photoPickerIntent, PICK_IMAGE_FROM_ALBUM)

        addPhotoUploadButton.setOnClickListener {
            contentUpload()
        }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if (requestCode == PICK_IMAGE_FROM_ALBUM) {
            if (resultCode == Activity.RESULT_OK) {
                photoUri = data?.data
                add_photo_id.setImageURI(photoUri)
            } else {
                finish()
            }
        }
    }

    fun contentUpload() {
        // make file name
        var timeStamp = SimpleDateFormat("yyyyMMDD_HHmmss").format(Date())
        var imageFileName = "IMAGE_{$timeStamp}_.png"

        var storageRef = storage?.reference?.child("images")?.child(imageFileName)

        //promise method

        photoUri?.let {
            storageRef?.putFile(it)?.continueWithTask {
                return@continueWithTask storageRef.downloadUrl
            }
        }?.addOnSuccessListener {
            var content = ContentDTO()
            //insert downloaduri of image
            content.imageUri = it.toString()

            //insert uid of user
            content.uid = auth?.currentUser?.uid
            content.userId = auth?.currentUser?.email

            //insert explain of content
            content.explain = addPhotoEditExplain.text.toString()

            //insert timestamp
            content.timestamp = System.currentTimeMillis()

            Log.d(TAG,"[contentUpload] uid : ${content.uid}, userId : ${content.userId}, timestamp : ${content.timestamp}")

            firestore?.collection("images")?.document()?.set(content)

            setResult(Activity.RESULT_OK)

            finish()
        }


/*        //callback method
        photoUri?.let {
            storageRef?.putFile(it)?.addOnSuccessListener {
                storageRef.downloadUrl.addOnSuccessListener {
                    var content = ContentDTO()
                    //insert downloaduri of image
                    content.imageUri = it.toString()

                    //insert uid of user
                    content.uid = auth?.currentUser?.uid
                    content.userId = auth?.currentUser?.email

                    //insert explain of content
                    content.explain = addPhotoEditExplain.text.toString()

                    //insert timestamp
                    content.timestamp = System.currentTimeMillis()

                    Log.d(TAG,"[contentUpload] uid : ${content.uid}, userId : ${content.userId}, timestamp : ${content.timestamp}")

                    firestore?.collection("images")?.document()?.set(content)

                    setResult(Activity.RESULT_OK)

                    finish()
                }
            }
        }*/
    }
}