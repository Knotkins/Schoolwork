using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotationalMotion : MonoBehaviour {
    // Determines the angular rotation and the previous rotation of the cube
    public float angularRotation;
    public Quaternion prevRotation;

    void Start() {
        prevRotation = this.transform.rotation;
    }
    
    void Update() {
        // q += q * w * dt / 2
        prevRotation = Quaternion.AngleAxis(angularRotation *(Time.deltaTime/2), Vector3.up);
        this.transform.rotation *= prevRotation;
    }
}