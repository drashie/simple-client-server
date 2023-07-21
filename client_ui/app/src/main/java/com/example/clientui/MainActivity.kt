package com.example.clientui

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.TextView

class MainActivity : AppCompatActivity() {
    private val servCom = ServerCommnunication()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        createListeners()
    }

    private fun createListeners() {
        val recvText = findViewById<TextView>(R.id.RECV_TEXT)
        val getButton = findViewById<Button>(R.id.GET_BUTTON)
        val addButton = findViewById<Button>(R.id.ADD_BUTTON)

        getButton.setOnClickListener{
            recvText.text = servCom.getData()
        }

        addButton.setOnClickListener{
            recvText.text = "ADD BUTTON PRESSED"
        }
    }
}