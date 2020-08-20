package com.example.gilstagram.navigation

import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.bumptech.glide.Glide
import com.example.gilstagram.R
import com.example.gilstagram.navigation.model.ContentDTO
import com.google.firebase.auth.FirebaseAuth
import com.google.firebase.firestore.FirebaseFirestore
import kotlinx.android.synthetic.main.fragment_detail.view.*
import kotlinx.android.synthetic.main.item_detail.view.*

class DetailViewFragment : Fragment() {
    var firestore: FirebaseFirestore? = null
    var uid : String? = null
    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        firestore = FirebaseFirestore.getInstance()
        var view = LayoutInflater.from(activity).inflate(R.layout.fragment_detail,container,false)
        uid = FirebaseAuth.getInstance().currentUser?.uid
        view.fragment_detail_recyclerview.adapter = DetailViewRecyclerViewAdapter()
        view.fragment_detail_recyclerview.layoutManager = LinearLayoutManager(activity)
        return view
    }

    inner class DetailViewRecyclerViewAdapter: RecyclerView.Adapter<RecyclerView.ViewHolder>() {
        var contentDTO : ArrayList<ContentDTO> = arrayListOf()
        var contentUidList : ArrayList<String> = arrayListOf()

        init {
            firestore?.collection("images")?.orderBy("timestamp")?.addSnapshotListener { value, error ->
                if (value == null) return@addSnapshotListener

                contentDTO.clear()
                contentUidList.clear()
                for (snapshot in value!!.documents) {
                    var item = snapshot.toObject(ContentDTO::class.java)
                    contentDTO.add(item!!)
                    contentUidList.add(snapshot.id)
                }
                notifyDataSetChanged()
            }
        }

        override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecyclerView.ViewHolder {
            var view = LayoutInflater.from(parent.context).inflate(R.layout.item_detail,parent,false)
            return CustomViewHolder(view)
        }

        //memory를 적게 사용하기 위한 기법?
        inner class CustomViewHolder(view: View) : RecyclerView.ViewHolder(view)

        override fun getItemCount(): Int {
            return contentDTO.size
        }

        override fun onBindViewHolder(holder: RecyclerView.ViewHolder, position: Int) {
            var viewHolder = (holder as CustomViewHolder).itemView

            viewHolder.detailviewitem_profile_textview.text = contentDTO[position].userId

            Glide.with(holder.itemView.context).load(contentDTO[position].imageUri).into(viewHolder.detailviewitem_imageview_content)

            viewHolder.detailviewitem_explain_textview.text = contentDTO[position].explain

            viewHolder.detailviewitem_favoritecounter_textview.text = "Likes = " + contentDTO[position].favoriteCount

            Glide.with(holder.itemView.context).load(contentDTO[position].imageUri).into(viewHolder.detailviewitem_imageview_content)

            viewHolder.detailviewitem_imageview_favorite.setOnClickListener {
                favoriteEvent(position)
            }

            if (contentDTO[position].favorites.contains(uid)) {
                //Log.d("heo","${contentDTO[position].favorites.containsKey(uid)}, $uid")
                viewHolder.detailviewitem_imageview_favorite.setImageResource(R.drawable.ic_favorite)
            } else {
                viewHolder.detailviewitem_imageview_favorite.setImageResource(R.drawable.ic_favorite_border)
            }

            viewHolder.detailviewitem_profile_image.setOnClickListener {
                Log.d("heo","profile image clicked!!")
                var fragment = UserFragment().apply {
                    arguments = Bundle().apply {
                        putString("destinationUid",contentDTO[position].uid)
                        putString("userId",contentDTO[position].userId)
                    }
                }
                activity?.supportFragmentManager?.beginTransaction()?.replace(R.id.main_content, fragment)?.commit()
            }
        }

        fun favoriteEvent(position:Int) {
            var tsDoc = firestore?.collection("images")?.document(contentUidList[position])
            firestore?.runTransaction {
                var content = it.get(tsDoc!!).toObject(ContentDTO::class.java)

                if(content?.favorites?.contains(uid)!!) {
                    //when the button is clicked
                    content.favoriteCount--;
                    content.favorites.remove(uid)
                } else {
                    //when the button is not clicked
                    content.favoriteCount++;
                    uid?.let { uid1 ->
                        content.favorites.put(uid1,true)
                    }
                    Log.d("heo","favorite Event : $uid")
                }
                it.set(tsDoc,content)
            }
        }
    }
}