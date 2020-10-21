using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Vetices : MonoBehaviour
{
    Mesh mesh;
    Vector3[] vertices;

    void Start()
    {
        mesh = GetComponent<MeshFilter>().mesh;
        vertices = mesh.vertices;

        for (var i = 0; i < vertices.Length; i++)
        {
            vertices[i] = transform.TransformPoint(vertices[i]);

        }

    }

    void Update()
    {
        for (var i = 0; i < vertices.Length; i++)
        {
            Debug.Log(vertices[i]);

        }
        
    }
}