using System.Collections.Generic;
using UnityEngine;

public class GJKMesh : IConvexRegion
{
    public Transform transform;
    public Mesh mesh;
    public List<Vector3> vertices;

    public Vector3 GetFurthestPoint(Vector3 direction)
    {
        // TODO: Implement support point function for mesh
        // furthest point in direction 
        if (vertices == null)
        {
            vertices = new List<Vector3>(mesh.vertices);
        }
        vertices[0] = transform.TransformPoint(vertices[0]);
        Vector3 point = vertices[0];
        float distance = Vector3.Dot(point, direction);
        
        for(int i = 1; i <vertices.Count; i++)
        {
            transform.TransformPoint(vertices[i]);
            float newDistance = Vector3.Dot(vertices[i], direction);
            if(newDistance > distance)
            {
                distance = newDistance;
                point = vertices[i];
            }
        }
        return point;
    }
}