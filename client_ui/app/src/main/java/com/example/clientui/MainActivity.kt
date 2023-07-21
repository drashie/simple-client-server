package com.example.clientui

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch

class MainActivity : AppCompatActivity() {
    private val servCom = ServerCommunication()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        createListeners()
    }

    /**
     * @brief create listeners for ADD and GET button
     *        which executes the server communication
     *        when pressed
     */
    private fun createListeners() {
        val getButton = findViewById<Button>(R.id.GET_BUTTON)
        val addButton = findViewById<Button>(R.id.ADD_BUTTON)

        getButton.setOnClickListener{
            GlobalScope.launch (Dispatchers.IO) {
                var resp = "Not connected"
                try {
                    resp = servCom.getData()
                } catch (e : Exception) {
                    resp = "ERROR: could not connect to server!"
                }
                updateTextView(resp)
            }
        }

        addButton.setOnClickListener{
            updateTextView(servCom.sendData("Test"))
        }
    }

    /**
     * @brief: Thread to update the textview after server communication is done
     * @param resp String that is shown on textview
     */
    private fun updateTextView(resp: String){
        val recvText = findViewById<TextView>(R.id.RECV_TEXT)
        runOnUiThread{
            recvText.text = resp
        }
    }
}