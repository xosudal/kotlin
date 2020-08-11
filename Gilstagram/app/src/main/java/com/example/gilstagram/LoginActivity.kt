package com.example.gilstagram

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Toast
import com.google.firebase.auth.FirebaseAuth
import com.google.firebase.auth.FirebaseUser
import kotlinx.android.synthetic.main.activity_login.*

class LoginActivity : AppCompatActivity() {
    var auth:FirebaseAuth? = null
    val TAG = "LoginActivity"
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_login)
        auth = FirebaseAuth.getInstance()
        email_loginButton.setOnClickListener {
            signInAndsignUp()
        }
    }

    fun signInAndsignUp() {
        auth?.createUserWithEmailAndPassword(email_edittext.text.toString(),password_edittext.text.toString())
            ?.addOnCompleteListener {
            if (it.isSuccessful) {
                //Createing a user account
                Log.d(TAG,"[signInAndsignUp] create success")
                moveMainPage(it.result?.user)
            } else if (!(it.exception?.message.isNullOrEmpty())) {
                // login error
                Log.d(TAG,"[signInAndsignUp] create error?")
                Toast.makeText(this,it.exception?.message,Toast.LENGTH_LONG).show()
            } else {
                // Login if you have account
                Log.d(TAG,"[signInAndsignUp] have account..")
                signInEmail()
            }
        }
    }

    fun signInEmail() {
        auth?.signInWithEmailAndPassword(email_edittext.text.toString(),password_edittext.text.toString())
            ?.addOnCompleteListener {
                if (it.isSuccessful) {
                    // Login Success
                    Log.d(TAG,"[signInEmail] login success")
                    moveMainPage(it.result?.user)
                } else {
                    // Login Fail
                    Log.d(TAG,"[signInEmail] login fail")
                    Toast.makeText(this,it.exception?.message,Toast.LENGTH_LONG).show()
                }
            }
    }

    fun moveMainPage(user: FirebaseUser?) {
        if (user!=null) {
            Log.d(TAG,"[moveMainPage] Move to MainActivity")
            startActivity(Intent(this,MainActivity::class.java))
        }
    }
}