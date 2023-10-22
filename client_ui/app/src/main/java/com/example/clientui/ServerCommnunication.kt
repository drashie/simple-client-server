package com.example.clientui

// import kotlinx.coroutines.*
import android.util.Log
import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.OutputStreamWriter
import java.lang.Exception
import java.lang.IllegalArgumentException
import java.net.HttpURLConnection
import java.net.Socket
import java.net.URL

/* Here the communication with our server happens */
class ServerCommunication {
    val RASPI_IP = "192.168.178.34"
    val PORT = 5555

    /**
     * @brief get the data from the server
     * @return The data received from the server as string
     */
    fun getData(): String {
        var response = ""
        try {
            // create socket to raspi with port 5555
            val socket = Socket(RASPI_IP, PORT)

            // send data to the server
            val outputStreamWriter = OutputStreamWriter(socket.getOutputStream(), "UTF-8")
            outputStreamWriter.write("GET")
            outputStreamWriter.flush()
            Log.d("TAG", "GET MSG SEND!")

            Log.d("TAG", "Now wait 1 secs")
            Thread.sleep(1000)

            Log.d("TAG", "Now Read input from server")
            val inputStreamReader = InputStreamReader(socket.getInputStream(), "UTF-8")
            val bufferReader = BufferedReader(inputStreamReader)
            var line: String? = bufferReader.readLine()
            while (line != null) {
                response += line + "\n"
                Log.d("TAG", "response value: $response")
                line = bufferReader.readLine()
            }
            socket.close()
        } catch (e : Exception){
            e.printStackTrace()
            response = "ERROR CAN NOT CONNECT TO SERVER"
        }
        return response;
    }

    /**
     * @brief send given data to server in the following format:
     *        "ADD content" max 256 bytes are accepted
     * @param content String that is send to the server max 256 bytes
     * @return server response
     */
    fun sendData(content: String): String {
        if (content.length > 256) {
            throw IllegalArgumentException("ERROR: Max length is 256!")
        }
        /* Add null character so the c server does not complain */
        val newContent = "ADD $content\u0000"
        var resp = ""

        try {
            // create socket to raspi with port 5555
            val socket = Socket(RASPI_IP, PORT)
            // send data to the server
            val outputStreamWriter = OutputStreamWriter(socket.getOutputStream(), "UTF-8")
            outputStreamWriter.write(newContent)
            outputStreamWriter.flush()

            Thread.sleep(1000)

            val inputStreamReader = InputStreamReader(socket.getInputStream(), "UTF-8")
            val bufferReader = BufferedReader(inputStreamReader)
            var line: String? = bufferReader.readLine()
            while (line != null) {
                resp += line + "\n"
                Log.d("TAG", "response value: $resp")
                line = bufferReader.readLine()
            }
            socket.close()
        } catch (e : Exception){
            e.printStackTrace()
            resp = "ERROR CAN NOT CONNECT TO SERVER"
        }

        return resp
    }

}