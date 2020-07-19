package com.example.todo

import android.annotation.SuppressLint
import android.app.AlertDialog
import android.content.DialogInterface
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import io.realm.Realm
import io.realm.kotlin.*
import kotlinx.android.synthetic.main.activity_edit.*
import java.util.*

class EditActivity : AppCompatActivity() {
    val realm = Realm.getDefaultInstance()
    val calendar: Calendar = Calendar.getInstance()
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_edit)


        val id = intent.getLongExtra("id", -1L)
        if (id==-1L) {
            insertMode()
        } else {
            updateMode(id)
        }

        calendarView.setOnDateChangeListener { view, year, month, dayOfMonth ->
            calendar.set(Calendar.YEAR, year)
            calendar.set(Calendar.MONTH, month)
            calendar.set(Calendar.DAY_OF_MONTH, dayOfMonth)
        }
    }

    private fun insertTodo() {
        realm.beginTransaction()
        val newItem = realm.createObject<Todo>(nextId())
        newItem.title = todoEditText.text.toString()
        newItem.date = calendar.timeInMillis
        realm.commitTransaction()

        var dialog = AlertDialog.Builder(this)
        dialog.setMessage("내용이 추가되었음")
        var dialogListener = DialogInterface.OnClickListener {
            p0, p1 -> when(p1) {
                DialogInterface.BUTTON_POSITIVE -> finish()
            }
        }
        dialog.setPositiveButton("Yes",dialogListener)
        dialog.show()
    }

    private fun nextId(): Int {
        val maxId = realm.where<Todo>().max("id")
        if (maxId != null) {
            return maxId.toInt() + 1
        }
        return 0
    }

    private fun updateTodo(id: Long) {
        realm.beginTransaction()

        val updateItem = realm.where<Todo>().equalTo("id", id).findFirst()!!
        updateItem.title = todoEditText.text.toString()
        updateItem.date = calendar.timeInMillis
        realm.commitTransaction()

        var dialog = AlertDialog.Builder(this)
        dialog.setMessage("내용이 수정되었음")
        var dialogListener = DialogInterface.OnClickListener {
                p0, p1 -> when(p1) {
            DialogInterface.BUTTON_POSITIVE -> finish()
        }
        }
        dialog.setPositiveButton("Yes",dialogListener)
        dialog.show()
    }

    private fun deleteTodo(id: Long) {
        realm.beginTransaction()

        val deleteItem = realm.where<Todo>().equalTo("id", id).findFirst()!!
        deleteItem.deleteFromRealm()
        realm.commitTransaction()

        var dialog = AlertDialog.Builder(this)
        dialog.setMessage("내용이 삭제되었음")
        var dialogListener = DialogInterface.OnClickListener {
                p0, p1 -> when(p1) {
            DialogInterface.BUTTON_POSITIVE -> finish()
        }
        }
        dialog.setPositiveButton("Yes",dialogListener)
        dialog.show()
    }

    @SuppressLint("RestrictedApi")
    private fun insertMode() {
        deleteFab.visibility = View.GONE
        doneFab.setOnClickListener {
            insertTodo()
        }
    }

    private fun updateMode(id: Long) {
        val todo = realm.where<Todo>().equalTo("id", id).findFirst()!!
        todoEditText.setText(todo.title)
        calendarView.date = todo.date

        doneFab.setOnClickListener {
            updateTodo(id)
        }

        deleteFab.setOnClickListener {
            deleteTodo(id)
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        realm.close()
    }
}