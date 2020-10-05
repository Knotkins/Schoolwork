using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LinearMotion : MonoBehaviour {
    //movement speed in units per second
    public float movementSpeed = 1f;

    void Update() {

        //update the position
        transform.position = transform.position + new Vector3(movementSpeed * Time.deltaTime, 0, 0);

        //output to log the position change
        Debug.Log(transform.position);
    }
}