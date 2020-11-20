using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GJKManager : MonoBehaviour
{
    [Serializable]
    public struct BoxHelper
    {
        public GJKMesh meshGJK;
        public Transform transform;
        public Mesh meshReference;
    }

    public BoxHelper a;
    public BoxHelper b;

    public GJKState state;
    
    void GJK()
    {
        a.meshGJK = new GJKMesh() { transform = a.transform, mesh = a.meshReference };
        b.meshGJK = new GJKMesh() { transform = b.transform, mesh = b.meshReference };
        // stuff I added
        a.meshGJK.vertices = new List<Vector3>(a.meshReference.vertices);
        a.meshGJK.vertices = new List<Vector3>(b.meshReference.vertices);

        state = new GJKState();
        state.isColliding = GJKAlgorithm.Intersects(a.meshGJK, a.meshGJK.transform, b.meshGJK, b.meshGJK.transform, state);
    }

    // Use this for initialization
    void Start()
    {

    }
    Vector3 direction;
    // Update is called once per frame
    void Update()
    {
        bool colliding = state.isColliding;
        GJK();
        GizmosDraw();
        Debug.Log(a.meshGJK.vertices.Count);
        if (Input.GetKey(KeyCode.D))
        {
            direction = Vector3.right;
        }
    }

    public Simplex simplex;
    void GizmosDraw()
    {
       // Gizmos.Clear();
        // minkowsiki sum
        // draw all the points in state.points sum
        // iterate accross mesh A, for each point on Mesh 
        for (int i =0; i < a.meshGJK.vertices.Count; i++)
        {
            for ( int j = 0; j < b.meshGJK.vertices.Count; j++)
            {
                Gizmos.DrawSphere(a.meshGJK.vertices[i] + -b.meshGJK.vertices[j], 0.02f);
            }
        }
        for(int i = 0; i < state.searchedSum.Count; i++)
        {
            Gizmos.DrawSphere(state.searchedSum[i], 0.05f); 
        }
 
        // drawing slimplices 
        if (state.simplices.Count < 1)
            return;

        for (int o = state.simplices.Count - 1; o > state.simplices.Count - 1; o--)
        {
            simplex = state.simplices[o];
            Vector3 a = simplex.vertices[0];

            // Point Drawer
            if (state.isColliding)
                Gizmos.color = Color.green;
            else
                Gizmos.color = Color.yellow;

            Gizmos.DrawSphere(a, 0.05f);

            // Line Drawer
            if (simplex.vertices.Count > 1)
            {
                for (int i = 1; i < simplex.vertices.Count; i++)
                {
                    Vector3 b = simplex.vertices[i];

                    Gizmos.DrawSphere(b, 0.05f);
                    Gizmos.DrawLine(a, b);

                    for (int j = i + 1; j < simplex.vertices.Count; j++)
                    {
                        Vector3 c = simplex.vertices[j];

                        Gizmos.DrawSphere(c, 0.05f);
                        Gizmos.DrawLine(b, c);
                    }
                }
            }
        }

        Gizmos.color = Color.white;
        Gizmos.DrawSphere(Vector3.zero, 0.05f);
    }
}
