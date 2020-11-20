using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CustomRigidBody : MonoBehaviour
{
    [SerializeField]
    Vector3 startingPos;
    // Linear properties
    [SerializeField]
    Vector3 linearDisplacement, linearVelocity, linearAccelration;

    // Rotational properites
    [SerializeField]
    Vector3 rotationalDisplacment, rotationalVelocity, rotationalAccelration;
    // Start is called before the first frame update
    void Start()
    {
        startingPos = transform.position;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        transform.SetPositionAndRotation(startingPos + Move(), Rotate());
    }

    Vector3 Move()
    {
        linearVelocity += linearAccelration * Time.fixedDeltaTime;
        linearDisplacement += linearVelocity * Time.fixedDeltaTime;
        return linearDisplacement;
    }
    Quaternion Rotate()
    {
        rotationalVelocity += rotationalAccelration * Time.fixedDeltaTime;
        rotationalDisplacment += rotationalVelocity * Time.fixedDeltaTime;
        float cosY, sinY, cosP, sinP, cosR, sinR;
        // yaw
        cosY = Mathf.Cos(rotationalDisplacment.x * 0.5f);
        sinY = Mathf.Sin(rotationalDisplacment.x * 0.5f);
        // pitch 
        cosP = Mathf.Cos(rotationalDisplacment.y * 0.5f);
        sinP = Mathf.Sin(rotationalDisplacment.y * 0.5f);
        // roll
        cosR = Mathf.Cos(rotationalDisplacment.z * 0.5f);
        sinR = Mathf.Sin(rotationalDisplacment.z * 0.5f);

        float qx, qy, qz, qw;
        qw = cosY * cosP * cosR + sinY * sinP * sinR;
        qx = cosY * cosP * sinR - sinY * sinP * cosR;
        qy = sinY * cosP * sinR + cosY * sinP * cosR;
        qz = sinY * cosP * cosR - cosY * sinP * sinR;
        Quaternion q = new Quaternion(qx, qy, qz, qw);
        return q;
    }
}
