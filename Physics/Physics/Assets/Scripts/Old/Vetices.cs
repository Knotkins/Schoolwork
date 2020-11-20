using System.Collections;
using System.Collections.Generic;
using UnityEditor.Experimental.GraphView;
using UnityEngine;

public class Vetices : MonoBehaviour
{
    Mesh mesh1;
    Mesh mesh2;

    Vector3[] vertices1;
    Vector3[] vertices2;

    public GameObject cube1;
    public GameObject cube2;

    Vector3 direction;

    void Start()
    {
        cube1 = GameObject.Find("CubeRed");
        cube2 = GameObject.Find("CubeBlue");

        mesh1 = cube1.GetComponent<MeshFilter>().mesh;
        vertices1 = mesh1.vertices;

        mesh2 = cube2.GetComponent<MeshFilter>().mesh;
        vertices2 = mesh2.vertices;
    }

    void Update()
    {
        for (var i = 0; i < vertices1.Length; i++)
        {
            vertices1[i] = cube1.transform.TransformPoint(vertices1[i]);
            //Debug.Log(vertices1[i] + "CubeRed");
        }

        for (var i = 0; i < vertices2.Length; i++)
        {
            vertices1[i] = cube2.transform.TransformPoint(vertices2[i]);
            //Debug.Log(vertices2[i] + "CubeBlue");
        }

        ////Find the centre of each shape
        Vector3 cube1Center = (vertices1[0] + vertices1[1] + vertices1[2] + vertices1[3] + vertices1[4] + vertices1[5] + vertices1[6] + vertices1[7]) / 8;

        Vector3 cube2Center = (vertices2[0] + vertices2[1] + vertices2[2] + vertices2[3] + vertices2[4] + vertices2[5] + vertices2[6] + vertices2[7]) / 8;

        ////Find vector from one center to another
        direction = cube1Center - cube2Center;

        ////Find the biggest number : greatest along d
        Vector3 Ad = vertices1[0] * direction.magnitude;
        Debug.Log(Ad);

    }
}