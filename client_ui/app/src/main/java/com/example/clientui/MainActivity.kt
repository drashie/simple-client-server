package com.example.clientui

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.TextView
import androidx.lifecycle.lifecycleScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch
import java.io.BufferedReader
import java.io.InputStreamReader
import java.lang.StringBuilder

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
        val pingButton = findViewById<Button>(R.id.PING_BUTTON)

        getButton.setOnClickListener{

            lifecycleScope.launch (Dispatchers.IO) {
                var resp = "Not connected"
                resp = try {
                    servCom.getData()
                } catch (e : Exception) {
                    "ERROR: could not connect to server!"
                }
                updateTextView(resp);
            }
        }

        addButton.setOnClickListener{
            updateTextView(servCom.sendData("Test"))
        }

        pingButton.setOnClickListener{

            try {
                val host = "192.168.178.34"
                // val host = "8.8.8.8"
                val count = 5
                val process = Runtime.getRuntime().exec("ping -c $count $host")
                val reader = BufferedReader(InputStreamReader(process.inputStream))
                val stringBuilder = StringBuilder()
                var line: String? = reader.readLine()
                Log.d("TAG", "Line1: $line")
                while (line != null) {
                    stringBuilder.append(line).append("\n")
                    line = reader.readLine()
                    Log.d("TAG", "LINE IN WHILE: $line")
                }

                Log.d("TAG", "PING OUTPUT: $line")

                reader.close()
            } catch (e: Exception){
                Log.d("TAG", "ERROR while PING")
            }
        }
    }

    /**
     * @brief: Thread to update the textview after server communication is done
     * @param resp String that is shown on textview
     */
    private fun updateTextView(resp: String){
        val recvText = findViewById<TextView>(R.id.RECV_SCROLL)
        
        runOnUiThread{
            recvText.text = resp
        }
    }
}