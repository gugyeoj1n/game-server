using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using Photon.Pun;

public class PlayerManager : MonoBehaviourPunCallbacks
{
    // -----------------------------------------
    #region Public Fields

    [Tooltip("The current Health of our player")]
    public float Health = 1f;

    #endregion
    // -----------------------------------------

    // -----------------------------------------
    #region Private Fields

    [Tooltip("The beams GameObjec to control")]
    [SerializeField]
    private GameObject beams;
    bool isFiring;

    #endregion
    // -----------------------------------------

    // -----------------------------------------
    #region MonoBehaviour Callbacks
    
    void Awake()
    {
        if(beams == null)
        {
            Debug.LogError("<Color=Red><a>Missing</a></Color> Beams Reference.", this);
        } else
        {
            beams.SetActive(false);
        }


    }

    void Update()
    {
        ProcessInputs();
        if(beams != null && isFiring != beams.activeInHierarchy)
        {
            beams.SetActive(isFiring);
        }
        if(Health <= 0f) 
        {
            GameManager.Instance.LeaveRoom();
        }
    }

    void OnTriggerEnter(Collider other)
    {
        if(!photonView.IsMine)
        {
            return;
        }

        if(!other.name.Contains("Beam"))
        {
            return;
        }

        Health -= 0.1f;
    }

    void OnTriggerStay(Collider other)
    {
        if(!photonView.IsMine)
        {
            return;
        }

        if (!other.name.Contains("Beam"))
        {
            return;
        }

        Health -= 0.1f * Time.deltaTime;
    }

    #endregion
    // -----------------------------------------

    // -----------------------------------------
    #region Custom

    void ProcessInputs()
    {
        if(Input.GetButtonDown("Fire1"))
        {
            if(!isFiring)
            {
                isFiring = true;
            }
        }

        if(Input.GetButtonUp("Fire1"))
        {
            if(isFiring) 
            {
                isFiring = false;
            }
        }
    }

    #endregion
    // -----------------------------------------
}
