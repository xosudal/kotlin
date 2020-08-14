package com.example.gilstagram

import android.app.ProgressDialog
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Toast
import com.google.android.gms.auth.api.Auth
import com.google.android.gms.auth.api.Auth.*
import com.google.android.gms.auth.api.signin.GoogleSignIn
import com.google.android.gms.auth.api.signin.GoogleSignInAccount
import com.google.android.gms.auth.api.signin.GoogleSignInClient
import com.google.android.gms.auth.api.signin.GoogleSignInOptions
import com.google.firebase.auth.FirebaseAuth
import com.google.firebase.auth.FirebaseUser
import com.google.firebase.auth.GoogleAuthProvider
import kotlinx.android.synthetic.main.activity_login.*

class LoginActivity : AppCompatActivity() {
    var auth:FirebaseAuth? = null
    val TAG = "LoginActivity"
    lateinit var p:LoadingDialog
    var googleSignInClient:GoogleSignInClient? = null
    var GOOGLE_LOGIN_CODE = 9001
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_login)
        p = LoadingDialog(this@LoginActivity)
        auth = FirebaseAuth.getInstance()
        email_loginButton.setOnClickListener {
            p.show()
            signInAndsignUp()
        }
        google_sign_in_button.setOnClickListener {
            p.show()
            googleLogin()
        }
        var gso = GoogleSignInOptions.Builder(GoogleSignInOptions.DEFAULT_SIGN_IN)
            .requestIdToken(getString(R.string.default_web_client_id))
            .requestEmail()
            .build()
        googleSignInClient = GoogleSignIn.getClient(this,gso)
    }

    fun googleLogin() {
        val signInIntent = googleSignInClient?.signInIntent
        startActivityForResult(signInIntent,GOOGLE_LOGIN_CODE)
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if (requestCode == GOOGLE_LOGIN_CODE) {
            val result = Auth.GoogleSignInApi.getSignInResultFromIntent(data)
            Log.d(TAG, "[onActivityResult] result : $result")

            if (result != null) {
                if (result.isSuccess) {
                    Log.d(TAG, "[onActivityResult] result success")
                    var account = result.signInAccount
                    firebaseAuthWithGoogle(account)
                } else {
                    Log.d(TAG,"fail?" + result.status)
                }
            }
        }
    }

    fun firebaseAuthWithGoogle(account: GoogleSignInAccount?) {
        var credential = GoogleAuthProvider.getCredential(account?.idToken,null)
        auth?.signInWithCredential(credential)
            ?.addOnCompleteListener {
                if (it.isSuccessful) {
                    // Login Success
                    Log.d(TAG,"[firebaseAuthWithGoogle] login success")
                    p.dismiss()
                    moveMainPage(it.result?.user)
                } else {
                    // Login Fail
                    Log.d(TAG,"[firebaseAuthWithGoogle] login fail")
                    p.dismiss()
                    Toast.makeText(this,it.exception?.message,Toast.LENGTH_LONG).show()
                }
            }
    }

    fun signInAndsignUp() {
        auth?.createUserWithEmailAndPassword(email_edittext.text.toString(),password_edittext.text.toString())
            ?.addOnCompleteListener {
            if (it.isSuccessful) {
                //Createing a user account
                Log.d(TAG,"[signInAndsignUp] create success")
                p.dismiss()
                moveMainPage(it.result?.user)
            } else{
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
                    p.dismiss()
                    moveMainPage(it.result?.user)
                } else {
                    // Login Fail
                    Log.d(TAG,"[signInEmail] login fail")
                    p.dismiss()
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