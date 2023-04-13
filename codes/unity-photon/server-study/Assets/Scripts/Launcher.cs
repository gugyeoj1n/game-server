using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;

public class Launcher : MonoBehaviour
{
    // -----------------------------------------
    #region Private Serializable Fields

    #endregion
    // -----------------------------------------

    // -----------------------------------------
    #region Private Fields
    string gameVersion = "0.0.0";
    #endregion
    // -----------------------------------------

    // -----------------------------------------
    #region MonoBehaviour CallBacks

    void Awake()
    {
        PhotonNetwork.AutomaticallySyncScene = true;
    }

    void Start()
    {
        Connect();
    }

    #endregion
    // -----------------------------------------

    // -----------------------------------------
    #region Public Methods

    public void Connect()
    {
        if (!PhotonNetwork.IsConnected)
        {
            PhotonNetwork.GameVersion = gameVersion;
            PhotonNetwork.ConnectUsingSettings();
        }
        else
        {
            PhotonNetwork.JoinRandomRoom();
        }
    }

    #endregion
    // -----------------------------------------
}
