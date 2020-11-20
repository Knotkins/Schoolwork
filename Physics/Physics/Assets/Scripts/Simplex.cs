using System;
using System.Collections.Generic;
using UnityEngine;

[Serializable]
public class Simplex
{
    public List<Vector3> vertices = new List<Vector3>();

    public int Count
    {
        get { return vertices.Count; }
    }

    public Simplex Clone()
    {
        return new Simplex() { vertices = new List<Vector3>(this.vertices.ToArray()) };
    }
    public Vector3 this[int i]
    {
        get { return vertices[i]; }
    }

    public Simplex(params Vector3[] vertices)
    {
        for (int i = 0; i < vertices.Length; i++)
        {
            this.vertices.Add(vertices[i]);
        }
    }
    public void Add(Vector3 vertex)
    {
        vertices.Add(vertex);
    }

    public void Remove(Vector3 vertex)
    {
        vertices.Remove(vertex);
    }
}
