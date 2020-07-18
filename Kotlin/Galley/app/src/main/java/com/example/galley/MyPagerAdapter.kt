package com.example.galley

import androidx.fragment.app.FragmentActivity
import androidx.fragment.app.Fragment
import androidx.viewpager2.adapter.FragmentStateAdapter

class MyPagerAdapter(fa : FragmentActivity) : FragmentStateAdapter(fa){
    // 뷰페이저가 표시할 fragment 목록
    private val items = ArrayList<Fragment>()

    fun updateFragments(items : List<Fragment>) {
        this.items.addAll(items)
    }

    override fun getItemCount(): Int {
        return items.size
    }

    override fun createFragment(position: Int): Fragment {
        return items[position]
    }
}