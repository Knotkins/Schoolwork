using System;
using System.Collections.Generic;
using UnityEngine;

[Serializable]
public class GJKState
{
    public List<Vector3> searchedSum;
    public List<Simplex> simplices;
    public bool isColliding;

    public GJKState()
    {
        searchedSum = new List<Vector3>();
        simplices = new List<Simplex>();
        isColliding = false;
    }
}