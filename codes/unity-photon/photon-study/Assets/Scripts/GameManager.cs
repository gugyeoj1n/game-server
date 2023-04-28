using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using Photon.Pun;
using Photon.Realtime;

public class GameManager : MonoBehaviourPunCallbacks
{
    // -----------------------------------------
    #region Public Fields

    public static GameManager Instance;

    #endregion

    // -----------------------------------------

    // -----------------------------------------
    #region MonoBehaviour Callbacks

    void Start()
    {
        Instance = this;
    }

    #endregion
    // -----------------------------------------

    // -----------------------------------------
    #region Private Methods

    void LoadArena()
    {
        if(!PhotonNetwork.IsMasterClient)
        {
            Debug.LogError("PhotonNetwork : Trying to Load a level but we are not the master Client");
            return;
        }
        Debug.LogFormat("PhotonNetwork : Loading Level {0}", PhotonNetwork.CurrentRoom.PlayerCount);
        PhotonNetwork.LoadLevel("Room for " + PhotonNetwork.CurrentRoom.PlayerCount);
    }

    #endregion

    // -----------------------------------------

    // -----------------------------------------
    #region Photon Callbacks

    public override void OnLeftRoom()
    {
        SceneManager.LoadScene(0);
    }

    public override void OnPlayerEnteredRoom(Player other)
    {
        Debug.LogFormat("OnPlayerEnteredRoom() {0}", other.NickName);
        if(PhotonNetwork.IsMasterClient)
        {
            Debug.LogFormat("OnPlayerEnteredRoom() !! Master Client {0} !!", PhotonNetwork.IsMasterClient);
            LoadArena();
        }
    }

    public override void OnPlayerLeftRoom(Player other)
    {
        Debug.LogFormat("OnPlayerLeftRoom() {0}", other.NickName);
        if (PhotonNetwork.IsMasterClient)
        {
            Debug.LogFormat("OnPlayerLeftRoom() !! Master Client {0} !!", PhotonNetwork.IsMasterClient);
            LoadArena();
        }
    }

    #endregion
    // -----------------------------------------

    // -----------------------------------------
    #region

    public void LeaveRoom()
    {
        PhotonNetwork.LeaveRoom();
    }

    #endregion
    // -----------------------------------------
}