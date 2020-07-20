package com.example.todo

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import io.realm.OrderedRealmCollection
import io.realm.RealmBaseAdapter
import android.text.format.DateFormat

class TodoListAdatper(realmResult: OrderedRealmCollection<Todo>): RealmBaseAdapter<Todo>(realmResult) {
    //get view method는 아이템이 화면에 보일 때 마다 호출됨
    // convertView : 처음은 null이고 한 번 작성되면 이전에 작성했던 뷰를 전달한다

    override fun getView(position: Int, convertView: View?, parent: ViewGroup?): View {
        // list view 에서는 리스트를 표시할 때 성능 향상을 목적으로 view holder 패턴을 적용
        // view holder : 한 번 만들어둔 뷰를 최대한 재활용하여 성능을 높여주는 방법
        val vh: ViewHolder
        val view: View

        if (convertView == null) {
            view = LayoutInflater.from(parent?.context).inflate(R.layout.item_todo, parent, false)
            vh = ViewHolder(view)
            view.tag = vh
        } else {
            view = convertView
            vh = view.tag as ViewHolder
        }

        if (adapterData != null) {
            val item = adapterData!![position]
            vh.textTextView.text = item.title
            vh.dateTextView.text = DateFormat.format("yyyy/MM/dd", item.date)
        }
        return view
    }

    override fun getItemId(position: Int): Long {
        if (adapterData != null) {
            return adapterData!![position].id
        }
        return super.getItemId(position)
    }
}

class ViewHolder(view: View) {
    val dateTextView: TextView = view.findViewById(R.id.text1)
    val textTextView: TextView = view.findViewById(R.id.text2)
}