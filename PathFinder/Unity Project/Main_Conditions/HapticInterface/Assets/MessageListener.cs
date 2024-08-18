using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MyMessageListener : MonoBehaviour {
    
    public AudioSource audioSource;
    public SerialController serialController;

    void Update(){
        if (Input.GetKeyDown(KeyCode.Alpha1)){
            Debug.Log("Sending 1");
            serialController.SendSerialMessage("1");
        }

        if (Input.GetKeyDown(KeyCode.Alpha2)){
            Debug.Log("Sending 2");
            serialController.SendSerialMessage("2");
        }

        if (Input.GetKeyDown(KeyCode.Alpha3)){
            Debug.Log("Sending 3");
            serialController.SendSerialMessage("3");
        }

        if (Input.GetKeyDown(KeyCode.Alpha4)){
            Debug.Log("Sending 4");
            serialController.SendSerialMessage("4");
        }

        if (Input.GetKeyDown(KeyCode.Alpha5)){
            Debug.Log("Sending 5");
            serialController.SendSerialMessage("5");
        }

        if (Input.GetKeyDown(KeyCode.D)){
            Debug.Log("Sending D");
            serialController.SendSerialMessage("D");
        }
    }

    // Invoked when a line of data is received from the serial device.
    void OnMessageArrived(string msg)
    {
        Debug.Log("Arrived: " + msg);
        msg = msg.Trim();

        //See which button was pressed
        switch(msg){
            case "B1":
                audioSource.Play();
                break;
            case "B2":
                audioSource.Play();
                break;
            case "B3":
                audioSource.Play();
                break;
            case "B4":
                audioSource.Play();
                break;
            case "B5":
                audioSource.Play();
                break;
            case "CB":
                audioSource.Play();
                break;
        }
    }

    void OnConnectionEvent(bool success)
    {
        Debug.Log(success ? "Device connected" : "Device disconnected");
    }
}
