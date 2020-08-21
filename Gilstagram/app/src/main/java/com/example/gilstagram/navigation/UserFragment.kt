package com.example.gilstagram.navigation

import android.content.Intent
import android.graphics.PorterDuff
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import androidx.appcompat.widget.LinearLayoutCompat
import androidx.core.content.ContextCompat
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.GridLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.bumptech.glide.Glide
import com.bumptech.glide.request.RequestOptions
import com.example.gilstagram.LoginActivity
import com.example.gilstagram.MainActivity
import com.example.gilstagram.R
import com.example.gilstagram.navigation.model.ContentDTO
import com.example.gilstagram.navigation.model.FollowDTO
import com.google.firebase.auth.FirebaseAuth
import com.google.firebase.firestore.DocumentSnapshot
import com.google.firebase.firestore.FirebaseFirestore
import com.google.firebase.firestore.FirebaseFirestoreException
import com.google.firebase.firestore.QuerySnapshot
import kotlinx.android.synthetic.main.activity_main.*
import kotlinx.android.synthetic.main.fragment_user.view.*

class UserFragment : Fragment() {
    var fragmentView : View? = null
    var firestore : FirebaseFirestore? = null
    var auth : FirebaseAuth? = null
    var uid : String? = null
    var currentUid : String? = null
    companion object {
        const val PICK_PROFILE_FROM_ALBUM = 11
    }
    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        fragmentView = LayoutInflater.from(activity).inflate(R.layout.fragment_user,container,false)
        uid = arguments?.getString("destinationUid")
        firestore = FirebaseFirestore.getInstance()
        auth = FirebaseAuth.getInstance()

        currentUid = auth?.currentUser?.uid

        if (uid == currentUid) {
            // my page
            fragmentView?.account_btn_follow_signout?.text = getString(R.string.signout)
            fragmentView?.account_btn_follow_signout?.setOnClickListener {
                activity?.finish()
                startActivity(Intent(activity, LoginActivity::class.java))
                auth?.signOut()
            }
        } else {
            // other person's page
            fragmentView?.account_btn_follow_signout?.text = getString(R.string.follow)
            val mainActivity = (activity as MainActivity)
            mainActivity.toolbar_username?.text = arguments?.getString("userId")
            mainActivity.toolbar_btn_back.setOnClickListener {
                mainActivity.bottom_navigation.selectedItemId = R.id.action_home
            }
            mainActivity.toolbar_title.visibility = View.GONE
            mainActivity.toolbar_btn_back.visibility = View.VISIBLE
            mainActivity.toolbar_username.visibility = View.VISIBLE
            fragmentView?.account_btn_follow_signout?.setOnClickListener {
                requestFollow()
            }
        }

        fragmentView?.account_recyclerview?.adapter = UserFragmentRecyclerViewAdapter()
        fragmentView?.account_recyclerview?.layoutManager = GridLayoutManager(activity!!,3)

        fragmentView?.account_iv_profile?.setOnClickListener {
            var photoPickerIntent = Intent(Intent.ACTION_PICK).apply {
                type = "image/*"
            }
            activity?.startActivityForResult(photoPickerIntent, PICK_PROFILE_FROM_ALBUM)
        }
        getProfileImages()
        getFollowerAndFollowing()
        return fragmentView
    }

    inner class UserFragmentRecyclerViewAdapter : RecyclerView.Adapter<RecyclerView.ViewHolder>() {
        var content : ArrayList<ContentDTO> = arrayListOf()
        init {
            firestore?.collection("images")?.whereEqualTo("uid",uid)?.addSnapshotListener { querySnapshot: QuerySnapshot?, firebaseFirestoreException: FirebaseFirestoreException? ->
                if (querySnapshot == null) return@addSnapshotListener

                //get data
                for(snapshot in querySnapshot.documents) {
                    content.add(snapshot.toObject(ContentDTO::class.java)!!)
                }
                fragmentView?.account_tv_post_count?.text = content.size.toString()
                notifyDataSetChanged()
            }
        }

        override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecyclerView.ViewHolder {
            var width = resources.displayMetrics.widthPixels / 3

            var imageView = ImageView(parent.context)
            imageView.layoutParams = LinearLayoutCompat.LayoutParams(width,width)
            return CustomViewHolder(imageView)
        }

        inner class CustomViewHolder(var imageView:ImageView) : RecyclerView.ViewHolder(imageView) {

        }

        override fun onBindViewHolder(holder: RecyclerView.ViewHolder, position: Int) {
            var imageView = (holder as CustomViewHolder).imageView
            Glide.with(holder.itemView.context).load(content[position].imageUri).apply(
                RequestOptions().centerCrop()).into(imageView)
        }

        override fun getItemCount(): Int {
            return content.size
        }
    }

    fun getProfileImages() {
        firestore?.collection("profileImages")?.document(uid!!)?.addSnapshotListener { documentSnapshot: DocumentSnapshot?, firebaseFirestoreException: FirebaseFirestoreException? ->
            if (documentSnapshot == null) return@addSnapshotListener

            if (documentSnapshot.data != null) {
                var url = documentSnapshot.data!!["images"]
                Glide.with(activity!!).load(url).apply(RequestOptions().circleCrop()).into(fragmentView?.account_iv_profile!!)
            }
        }
    }

    fun requestFollow() {
        //Save data to my account
        var tsDocFollowing = firestore?.collection("users")?.document(currentUid!!)
        firestore?.runTransaction {
            var followDTO = it.get(tsDocFollowing!!).toObject(FollowDTO::class.java)
            if (followDTO == null) {
                followDTO = FollowDTO().apply {
                    followingCount = 1
                    followers.set(uid!!, true)
                }
                it.set(tsDocFollowing, followDTO)
                return@runTransaction
            }

            if(followDTO.followings.contains(uid)) {
                followDTO.apply {
                    followingCount--
                    followers.remove(uid)
                }
            } else {
                followDTO.apply {
                    followingCount++
                    followers[uid!!] = true
                }
            }

            it.set(tsDocFollowing, followDTO)
            return@runTransaction
        }

        //Save data to third person
        var tsDocFollower = firestore?.collection("users")?.document(currentUid!!)
        firestore?.runTransaction {
            var followerDTO = it.get(tsDocFollower!!).toObject(FollowDTO::class.java)
            if (followerDTO == null) {
                followerDTO = FollowDTO().apply {
                    followerCount = 1
                    followers.set(uid!!, true)
                }
                it.set(tsDocFollower, followerDTO)
                return@runTransaction
            }

            if(followerDTO.followings.contains(uid)) {
                followerDTO.apply {
                    followerCount--
                    followers.remove(uid)
                }
            } else {
                followerDTO.apply {
                    followerCount++
                    followers[uid!!] = true
                }
            }

            it.set(tsDocFollower, followerDTO)
            return@runTransaction
        }
    }

    fun getFollowerAndFollowing() {
        firestore?.collection("users")?.document(currentUid!!)?.addSnapshotListener { documentSnapshot: DocumentSnapshot?, firebaseFirestoreException: FirebaseFirestoreException? ->
            if(documentSnapshot == null) return@addSnapshotListener
            var followDTO = documentSnapshot.toObject(FollowDTO::class.java)
            if (followDTO?.followingCount != null)   fragmentView?.account_tv_following_count?.text = followDTO.followingCount.toString()
            if (followDTO?.followerCount != null) {
                fragmentView?.account_tv_follower_count?.text = followDTO.followerCount.toString()
                if (followDTO.followers.contains(currentUid!!)) {
                    fragmentView?.account_btn_follow_signout?.text = getString(R.string.follow_cancel)
                    fragmentView?.account_btn_follow_signout?.background?.setColorFilter(ContextCompat.getColor(activity!!,R.color.colorLightGray),
                        PorterDuff.Mode.MULTIPLY)
                } else {
                    if (uid != currentUid) {
                        fragmentView?.account_btn_follow_signout?.text = getString(R.string.follow)
                        fragmentView?.account_btn_follow_signout?.background?.colorFilter = null
                    }
                }
            }
        }
    }
}