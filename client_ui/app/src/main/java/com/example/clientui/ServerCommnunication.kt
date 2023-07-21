package com.example.clientui

/* Here the communication with our server happens */
class ServerCommnunication {
    /* get the data from the server */
    fun getData(): String {
        return "GET BUTTON PRESSED";
    }

    /* send given data to the server */
    fun sendData(content: String): String {
        return "ADD BUTTON PRESSED"
    }

}