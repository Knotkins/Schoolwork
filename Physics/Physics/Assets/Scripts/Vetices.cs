using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Vetices : MonoBehaviour{
    Mesh mesh;
    Vector3[] vertices;
    public string ObjectName;

    void Start() {
        mesh = GetComponent<MeshFilter>().mesh;
        vertices = mesh.vertices;
    }

    void Update() {
        for (var i = 0; i < vertices.Length; i++) {
            Debug.Log(vertices[i]);
        }
    }
}