using UnityEngine;

public static class GJKAlgorithm
{
    public static bool Intersects(IConvexRegion regionOne, Transform oneTrans, IConvexRegion regionTwo, Transform twoTrans, GJKState state)
    {
        // Get an initial point on the Minkowski difference.
        Vector3 s = Support(regionOne, regionTwo, twoTrans.position - oneTrans.position, state);

        // Create our initial simplex.
        Simplex simplex = new Simplex(s);

        // TODO: Choose an initial direction.
        Vector3 d = -simplex.vertices[0];

        state.simplices.Add(new Simplex(simplex.vertices.ToArray()));

        // Choose a maximim number of iterations to avoid an 
        // infinite loop during a non-convergent search.
        int maxIterations = 32;

        for (int i = 0; i < maxIterations; i++)
        {
            // Get our next simplex point toward the origin.
            Vector3 a = Support(regionOne, regionTwo, d, state);

            // If we move toward the origin and didn't pass it 
            // then we never will and there's no intersection.
            if (a.IsInOppositeDirection(d))
            {
                return false;
            }

            // otherwise we add the new point to the simplex and process it.
            simplex.Add(a);
            state.simplices.Add(new Simplex(simplex.vertices.ToArray()));
            // Here we either find a collision or we find the closest feature of
            // the simplex to the origin, make that the new simplex and update the direction
            // to move toward the origin from that feature.
            if (ProcessSimplex(simplex, ref d))
            {
                return true;
            }
        }
        // If we still couldn't find a simplex 
        // that contains the origin then we
        // "probably" have an intersection.
        return true;
    }

    /// <summary>
    /// Finds a collision or the closest feature of the simplex to the origin, 
    /// and updates the simplex and direction.
    /// </summary>
    static bool ProcessSimplex(Simplex simplex, ref Vector3 direction)
    {
        if (simplex.Count == 2)
        {
            return ProcessLine(simplex, ref direction);
        }
        else if (simplex.Count == 3)
        {
            return ProcessTriangle(simplex, ref direction);
        }
        else
        {
            return ProcessTetrehedron(simplex, ref direction);
        }
    }

    /// <summary>
    /// Determines which Veronoi region of a line segment 
    /// the origin is in, utilizing the preserved winding
    /// of the simplex to eliminate certain regions.
    /// </summary>
    static bool ProcessLine(Simplex simplex, ref Vector3 direction)
    {
        // TODO: Process Line
        // 0 = A and 1 = B;
        //triple cross products
        // AB = B-A
        Vector3 AB = simplex.vertices[1] - simplex.vertices[0];
        Vector3 AO = -simplex.vertices[0];

        // Triple Cross product
        Vector3 crossProduct = (Vector3.Cross(Vector3.Cross(AB, AO), AB));
        direction = crossProduct;
     

        return false;
    }

    /// <summary>
    /// Determines which Veronoi region of a triangle 
    /// the origin is in, utilizing the preserved winding
    /// of the simplex to eliminate certain regions.
    /// </summary>
    static bool ProcessTriangle(Simplex simplex, ref Vector3 direction)
    {
        // TODO: Process Triangle
        //face check decided where the terahedron is pointing
        // 2 = A , 1 = B, 0 = C;
        Vector3 AB = simplex.vertices[1] - simplex.vertices[2];
        Vector3 AC = simplex.vertices[0] - simplex.vertices[2];
        Vector3 ABC = Vector3.Cross(AB, AC);
        Vector3 AO = -simplex.vertices[2];
        if(Vector3.Dot(ABC,AO) < 0)
        {
            // D = (ABC X AO) X ABC)
            direction = Vector3.Cross(Vector3.Cross(ABC, AO), -ABC);
        }
        else
        {
            // D = (-ABC X AO) X -ABC 
            direction = Vector3.Cross(Vector3.Cross(-ABC, AO), -ABC);

        }


        return false;
    }

    /// <summary>
    /// Determines which Veronoi region of a tetrahedron
    /// the origin is in, utilizing the preserved winding
    /// of the simplex to eliminate certain regions.
    /// </summary>
    static bool ProcessTetrehedron(Simplex simplex, ref Vector3 direction)
    {
        //Debug.Log("hit");

        // TODO: Process Tetrahedron
        // A = 3 , B = 2, C = 1, D = 0;
        Vector3 AB = simplex.vertices[2] - simplex.vertices[3];
        Vector3 AC = simplex.vertices[1] - simplex.vertices[3];
        Vector3 AD = simplex.vertices[0] - simplex.vertices[3];

        Vector3 ABC = Vector3.Cross(AB, AC);
        Vector3 ABD = Vector3.Cross(AB, AD);
        Vector3 ACD = Vector3.Cross(AD, AC);
        Vector3 AO  = -simplex.vertices[3];

        if(0 < Vector3.Dot(ABC, AO))
        {
            simplex.vertices.RemoveAt(0);
        }
        else if(0 < Vector3.Dot(ABD , AO))
        {
            simplex.vertices.RemoveAt(1);
        }
        else if(0< Vector3.Dot(ACD, AO))
        {
            simplex.vertices.RemoveAt(2);
        }
        else
        {
            return true;
        }
        return false;
    }

    /// <summary>
    /// Calculates the furthest point on the Minkowski 
    /// Sum along a given direction.
    /// </summary>
    static Vector3 Support(IConvexRegion regionOne, IConvexRegion regionTwo, Vector3 direction, GJKState state)
    {
        // TODO: Get support point
        Vector3 somepoint = regionOne.GetFurthestPoint(direction) + (-regionTwo.GetFurthestPoint(-direction)); 
        state.searchedSum.Add(somepoint);
        return somepoint;
    }
}